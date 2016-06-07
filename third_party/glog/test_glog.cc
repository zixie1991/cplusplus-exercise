#include <glog/logging.h>

int main(int argc, char* argv[]) {
  //
  // If glog is used to parse the command line   
  // google::ParseCommandLineFlags(&argc, &argv, true);  
  // 可以解析命令行参数, 如 test_glog --log_dir=./log 
  //

  // Initialize Google's logging library.  
  google::InitGoogleLogging(argv[0]);  

  // 设置日志输出目录
  FLAGS_log_dir = "./log";  

  LOG(INFO) << "hello world";  
  
  return 0;
}
