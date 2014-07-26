#include <fstream>

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "sim/sim.h"
#include "lman/lman.h"
#include "ghost/ai/fickle.h"

DEFINE_string(maze, "", "Text file that contains maze map");

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  
  if (FLAGS_maze.empty()) {
    std::cerr << "Usage: simulate_foobar --maze=<filename> --ghosts=<ghost>[,<ghost>]" << std::endl;
    return 1;
  }

  Game game;
  game.SetLambdaMan(new LambdaManImpl);
  std::ifstream mazefile(FLAGS_maze);
  game.ParseMaze(mazefile);

  int score = game.Start();
  LOG(INFO) << "Final Score: " << score;

  return 0;
}
