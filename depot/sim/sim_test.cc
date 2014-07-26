#include "sim/sim.h"
#include <sstream>
#include <glog/logging.h>
#include <gtest/gtest.h>

class MockLambdaMan : public LambdaMan {
public:
  void Init() override {
    LOG(INFO) << "Init";
  }
  int Step() override {
    LOG(INFO) << "Step";
    return 1;
  }
};

class MockGhost : public GhostInterface {
public:
  int Step() override {
    LOG(INFO) << "Step";
    return rotate++;
  }
private:
  int rotate = 0;
};

class MockGhostFactory : public GhostFactory {
public:
  GhostInterface* Create() override {
    created_++;
    return new MockGhost;
  }
  int Count() { return created_; }
private:
  int created_ = 0;
};

TEST(SimulatorTest, ParseMaze) {
  MockGhostFactory ghost_factory;
  MockLambdaMan lman;
  Game game;
  game.SetLambdaMan(&lman);
  game.AddGhostFactory(&ghost_factory);
  std::stringstream maze;
  maze << "#######################\n"
  << "#..........#..........#\n"
  << "#.###.####.#.####.###.#\n"
  << "#o###.####.#.####.###o#\n"
  << "#.....................#\n"
  << "#.###.#.#######.#.###.#\n"
  << "#.....#....#....#.....#\n"
  << "#####.#### # ####.#####\n"
  << "#   #.#    =    #.#   #\n"
  << "#####.# ### ### #.#####\n"
  << "#    .  # === #  .    #\n"
  << "#####.# ####### #.#####\n"
  << "#   #.#    %    #.#   #\n"
  << "#####.# ####### #.#####\n"
  << "#..........#..........#\n"
  << "#.###.####.#.####.###.#\n"
  << "#o..#......\\......#..o#\n"
  << "###.#.#.#######.#.#.###\n"
  << "#.....#....#....#.....#\n"
  << "#.########.#.########.#\n"
  << "#.....................#\n"
  << "#######################\n";
  game.ParseMaze(maze);
  EXPECT_EQ(4, ghost_factory.Count());
}

TEST(SimulatorTest, RunGame) {
  MockGhostFactory ghost_factory;
  MockLambdaMan lman;
  Game game;
  game.SetLambdaMan(&lman);
  game.AddGhostFactory(&ghost_factory);
  std::stringstream maze;
  maze << "#######################\n"
  << "#..........#..........#\n"
  << "#.###.####.#.####.###.#\n"
  << "#o###.####.#.####.###o#\n"
  << "#.....................#\n"
  << "#.###.#.#######.#.###.#\n"
  << "#.....#....#....#.....#\n"
  << "#####.#### # ####.#####\n"
  << "#   #.#    =    #.#   #\n"
  << "#####.# ### ### #.#####\n"
  << "#    .  # === #  .    #\n"
  << "#####.# ####### #.#####\n"
  << "#   #.#    %    #.#   #\n"
  << "#####.# ####### #.#####\n"
  << "#..........#..........#\n"
  << "#.###.####.#.####.###.#\n"
  << "#o..#......\\......#..o#\n"
  << "###.#.#.#######.#.#.###\n"
  << "#.....#....#....#.....#\n"
  << "#.########.#.########.#\n"
  << "#.....................#\n"
  << "#######################\n";
  game.ParseMaze(maze);
  EXPECT_EQ(game.Start(), 60);
}
