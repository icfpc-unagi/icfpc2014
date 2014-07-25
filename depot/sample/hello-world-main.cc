#include "sample/hello-world.h"

#include <gflags/gflags.h>
#include <glog/logging.h>

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  LOG(INFO) << "Starting hello-world-main...";
  HelloWorld();
  return 0;
}
