#include "sim/sim.h"
#include <sstream>
#include <glog/logging.h>
#include <gtest/gtest.h>

class MockLambdaMan : public LambdaManInterface {
public:
  void Main() override {
    LOG(INFO) << "Main";
  }
  int Step() override {
    LOG(INFO) << "Step";
    return 1;
  }
};

class MockLambdaManFactory : public LambdaManFactory {
public:
  std::unique_ptr<LambdaManInterface> Create() override {
    created_++;
    return std::unique_ptr<LambdaManInterface>(new MockLambdaMan);
  }
  int Count() { return created_; }
private:
  int created_ = 0;
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
  std::unique_ptr<GhostInterface> Create() override {
    created_++;
    return std::unique_ptr<GhostInterface>(new MockGhost);
  }
  int Count() { return created_; }
private:
  int created_ = 0;
};

TEST(SimulatorTest, ParseMaze) {
  MockGhostFactory ghost_factory;
  MockLambdaManFactory lambda_man_factory;
  Game game;
  game.SetLambdaMan(&lambda_man_factory);
  game.SetGhostFactory(&ghost_factory);
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
  MockLambdaManFactory lambda_man_factory;
  Game game;
  game.SetLambdaMan(&lambda_man_factory);
  game.SetGhostFactory(&ghost_factory);
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
