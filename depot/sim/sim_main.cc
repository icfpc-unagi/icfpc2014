#include "sim/sim.h"
#include <fstream>
#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_string(maze, "example_maze.txt", "Text file that contains maze map");

int main() {
  Game game;
  game.AddGhostFactory(nullptr);
  game.SetLambdaMan(nullptr);
  ifstream mazefile(FLAGS_maze);
  game.ParseMaze(mazefile);

  int score = game.Start();
  LOG(INFO) << "Final Score: " << score;

  return 0;
}
