#include <memory>

#include "ghost/ghost.h"
#include "ghost/sample/fickle.h"

#include <gflags/gflags.h>
#include <glog/logging.h>

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  std::unique_ptr<ghost::Ghost> ghost(new ghost::FickleGhost);
  ghost->Run();
  return 0;
}
