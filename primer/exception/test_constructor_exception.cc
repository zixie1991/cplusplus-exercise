#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <stdexcept>

using namespace std;

// 构造函数中的异常的抛出与捕获
// 如何处理C++构造函数中的错误——兼谈不同语言的错误处理: https://www.byvoid.com/zhs/blog/cpp-constructor-exception

// 构造函数出错的解决方法:
// 1. 构造函数出错时抛出异常, 在对象创建时捕获异常
// 2. 仿照stl ifstream, 当构造时传入一个无法访问的文件作为参数，它不会返回任何
//    错误，而是标记的内部状态为不可用，用户需要手工通过is_open()函数来判断是
//    否打开成功了。同时它还有good()、fail()两个函数，同时也重载了bool类型转换
//    运算符用于在if语句中判断。标记状态的方法在实践中相当丑陋，因为在使用前总
//    是需要判断它是否「真的创建成功了」。
// 3. 使用一个额外的初始化函数来初始化, 把出错处理都放在初始化函数中

class FileNotFoundException: public runtime_error {
  public:
    explicit FileNotFoundException(const string& str):
      runtime_error(str) 
    {
    }
};

class FileReaderWithException {
  public:
    FileReaderWithException() {

    }

    FileReaderWithException(const string& filename) {
      fp_ = fopen(filename.c_str(), "r");
      if (NULL == fp_) {
        // 抛出异常后析构函数就不会被调用
        // 资源释放需要自己手动处理
        throw FileNotFoundException("File not found.");
      }
    }

    FileReaderWithException(const FileReaderWithException& file_reader) {
      this->fp_ = file_reader.fp_;
    }

    ~FileReaderWithException() {
      Close();
    }

    void Close() {
      if (NULL != fp_) {
        fclose(fp_);
      }
    }

  private:
    FILE* fp_;
};

class FileReaderWithInit {
  public:
    FileReaderWithInit(const string& filename):
      filename_(filename)
    {

    }

    bool Init() {
      fp_ = fopen(filename_.c_str(), "r");

      return fp_ != NULL;
    }

    ~FileReaderWithInit() {
      Close();
    }

    void Close() {
      if (NULL != fp_) {
        fclose(fp_);
      }
    }

  private:
    FILE* fp_;
    string filename_;
};

class FileReaderWithFlag {
  public:
    FileReaderWithFlag(const string& filename) {
      fp_ = fopen(filename.c_str(), "r");
    }

    bool Good() {
      return fp_ != NULL;
    }

    bool Fail() {
      return fp_ == NULL;
    }

    ~FileReaderWithFlag() {
      Close();
    }

    void Close() {
      if (NULL != fp_) {
        fclose(fp_);
      }
    }

  private:
    FILE* fp_;
};

class FileWithException {
  public:
    FileWithException(const string& filename):
      file_reader_(filename)
    {
    }

    //FileWithException(const string& filename) try: file_reader_(filename) {
    //} catch (FileNotFoundException& file_not_found_error) {
      //cerr << file_not_found_error.what() << endl;
      // catch块里面捕获到的异常不能被忽略，即catch块中必须有一个throw语句重新抛出异常，
      // 如果没有，则默认会将原来捕获到的异常重新抛出，这和一般的行为是不同的。
    //}

  private:
    FileReaderWithException file_reader_;
};

class FileWithException2 {
  public:
    FileWithException2(const string& filename) {
      try {
        file_reader_ = new FileReaderWithException(filename);
      } catch (FileNotFoundException& file_not_found_error) {
        cerr << file_not_found_error.what() << endl;
        // 异常被忽略, 需要手动重新抛出异常
      }
    }

  private:
    FileReaderWithException* file_reader_;
};

void TestFileReaderWithException() {
  try {
    FileReaderWithException file_reader("test.txt");
  } catch (FileNotFoundException& file_not_found_error) {
    cerr << file_not_found_error.what() << endl;
  }

  // 没有捕获异常, 终止当前的程序
  //FileReaderWithException file_reader("test.txt");

  //try {
    //FileWithException file("test.txt");
  //} catch (...) {
  //}

  // 没有捕获异常, 终止当前的程序
  //FileWithException file("test.txt");

  FileWithException2 file2("test.txt");
}

void TestFileReaderWithInit() {
  FileReaderWithInit file_reader("test.txt");
  if (!file_reader.Init()) {
    cerr << "File not found." << endl;
  }
}

void TestFileReaderWithFlag() {
  FileReaderWithFlag file_reader("test.txt");
  if (!file_reader.Good()) {
    cerr << "File not found." << endl;
  }
}

int main() {
  cout << "TestFileNotFoundException:" << endl;
  TestFileReaderWithException();
  cout << "TestFileReaderWithInit:" << endl;
  TestFileReaderWithInit();
  cout << "TestFileReaderWithFlag:" << endl;
  TestFileReaderWithFlag();
  cout << "MainEnd" << endl;
  return 0;
}
