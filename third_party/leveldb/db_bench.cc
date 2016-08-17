#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include "db.h"

using namespace std;
using namespace db;
using namespace boost;
using namespace cv;

#define STRINGFY(s) #s
#define STRINGAS(s) STRINGFY(s)

static string FLAGS_benchmarks = "";
static int FLAGS_num = 0;
static string FLAGS_image_dir = "";
static string FLAGS_db_file = "/tmp/benchmark";

string IntToStr(int n) {
  ostringstream s;
  s << n;
  return s.str();
}

class Benchmark {
  public:
    Benchmark():
      db_(GetDB("leveldb"))
    {}

    void Run() {
      num_ = FLAGS_num;
      image_dir_ = FLAGS_image_dir;
      db_file_ = FLAGS_db_file;
      
      string benchmarks = FLAGS_benchmarks;

      if (benchmarks == "readseq") {
        ReadSeq();
      } else if (benchmarks == "readrandom") {
        ReadRandom();
      } else if (benchmarks == "writeseq") {
        WriteSeq();
      } else if (benchmarks == "writerandom") {
        WriteRandom();
      } else if (benchmarks == "deleteseq") {
        DeleteSeq();
      } else if (benchmarks == "deleterandom") {
        DeleteRandom();
      } else {
        cerr << "Unknown " << STRINGAS(FLAGS_benchmarks) << endl;
      }
    }

    // 顺序读
    void ReadSeq() {
      db_->Open(db_file_, kRead);

      for (int i = 0; i < num_; i++) {
        string key = IntToStr(i);
        string value;
        db_->Get(key, &value);
      }
    }

    // 随机读
    void ReadRandom() {
      db_->Open(db_file_, kRead);
      vector<int> vec;
      for (int i = 0; i < num_; i++) {
        vec.push_back(i);
      }
      // 洗牌算法
      random_shuffle(vec.begin(), vec.end());

      for (size_t i = 0; i < vec.size(); i++) {
        string key = IntToStr(vec[i]);
        string value;
        db_->Get(key, &value);
      }
    }

    // 顺序写
    void WriteSeq() {
      if (!db_->Open(db_file_, kWrite)) {
        db_->Open(db_file_, kNew);
      }

      filesystem::path root_path(image_dir_);
      vector<string> files;

      filesystem::recursive_directory_iterator iter_end;
      for (filesystem::recursive_directory_iterator iter(root_path); iter != iter_end; ++iter) {
        if (!filesystem::is_directory(*iter)) {
          files.push_back(iter->path().string());
        }
      }

      num_ = 0;
      for (size_t i = 0; i < files.size(); i++) {
        Mat img = imread(files[i]);
        if (!img.data) {
          continue;
        }

        num_++;
        string key = IntToStr(i);
        std::vector<uchar> buf;
        cv::imencode(".jpg", img, buf);
        string value(reinterpret_cast<char*>(&buf[0]), buf.size());
        db_->Put(key, value);
      }
      cout << "num=" << num_ << endl;
    }

    // 随机写
    void WriteRandom() {
    }

    // 顺序删除
    void DeleteSeq() {
      db_->Open(db_file_, kWrite);

      for (int i = 0; i < num_; i++) {
        string key = IntToStr(i);
        db_->Delete(key);
      }
    }

    // 随机删除
    void DeleteRandom() {
      db_->Open(db_file_, kWrite);
      vector<int> vec;
      for (int i = 0; i < num_; i++) {
        vec.push_back(i);
      }
      // 洗牌算法
      random_shuffle(vec.begin(), vec.end());

      for (size_t i = 0; i < vec.size(); i++) {
        string key = IntToStr(vec[i]);
        db_->Delete(key);
      }
    }

  private:
    DB* db_;
    int num_; // <K, V>数目
    string image_dir_;
    string db_file_;
};

int main(int argc, char* argv[]) {

  for (int i = 1; i < argc; i++) {
    if (!strncmp("--benchmarks=", argv[i], 13)) {
      FLAGS_benchmarks = argv[i] + 13;
    } else if (!strncmp("--num=", argv[i], 6)) {
      FLAGS_num = atoi(argv[i] + 6);
    } else if (!strncmp("--image_dir=", argv[i], 12)) {
      FLAGS_image_dir = argv[i] + 12;
    } else if (!strncmp("--db_file=", argv[i], 10)) {
      FLAGS_db_file = argv[i] + 10;
    } else {
      fprintf(stderr, "Invalid flag %s\n", argv[i]);
      return 1;
    }
  }

  Benchmark benchmark;
  benchmark.Run();

  return 0;
}
