#include <fstream>

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "sim/sim.h"
#include "lman/ai/chokudai-10.h"
#include "ghost/ai/fickle.h"

DEFINE_string(maze, "depot/sim/world-classic.txt", "Text file that contains maze map");
DECLARE_bool(logtostderr);

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = true;
  
  if (FLAGS_maze.empty()) {
    std::cerr << "Usage: simulate_foobar --maze=<filename> --ghosts=<ghost>[,<ghost>]" << std::endl;
    return 1;
  }

  Game game;
  std::ifstream mazefile(FLAGS_maze);
  game.ParseMaze(mazefile);

  int score = game.Start();
  LOG(INFO) << "Final Score: " << score;

  return 0;
}
