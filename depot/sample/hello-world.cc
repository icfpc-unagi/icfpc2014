#include "sample/hello-world.h"

#include <stdio.h>
#include <string>

#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_string(name, "world", "Name to output");

bool HelloWorld() {
  printf("%s\n", ("Hello, " + FLAGS_name + "!").c_str());
  return true;
}
