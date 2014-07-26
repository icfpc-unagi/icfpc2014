#include <fstream>

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "sim/sim.h"
#include "ghost/sample/fickle.h"

DEFINE_string(maze, "example_maze.txt", "Text file that contains maze map");

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  Game game;
  game.AddGhostFactory(new ghost::FickleGhostFactory);
  game.SetLambdaMan(nullptr);
  std::ifstream mazefile(FLAGS_maze);
  game.ParseMaze(mazefile);

  int score = game.Start();
  LOG(INFO) << "Final Score: " << score;

  return 0;
}
