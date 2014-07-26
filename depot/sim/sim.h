#ifndef SIM_SIM_H_
#define SIM_SIM_H_

#include <memory>
#include <string>
#include <vector>

#include "ghost/ghost-ai-manager.h"
#include "sim/character.h"
#include "sim/game-interface.h"
#include "sim/ghost-interface.h"
#include "util/coordinate.h"

class Game;

// Lambda-Man interface
class LambdaMan : public Character {
 public:
  void Init(GameInterface* game) {
    game_ = game;
  }
  virtual void Main() = 0;
  virtual int Step() = 0;

 protected:
  GameInterface* game_;
};

// Game Mechanics
class Game : public GameInterface {
 public:
  Game() : ghost_factories_(ghost::GetGhostAiManager()->GetGhosts()) {}
  virtual ~Game() {}

  // Configurations
  void SetGhostFactory(GhostFactory* ghost_factory) {
    ghost_factories_.clear();
    ghost_factories_.push_back(ghost_factory);
  }
  void SetLambdaMan(LambdaMan* lman) { lman_ = lman; }
  void ParseMaze(std::istream& is);
  // Returns the final score
  int Start();
  
  char GetSymbol(const Coordinate& rc) const {
    return maze_[rc.first][rc.second];
  }
  char GetSymbolSafe(const Coordinate& rc, char out_of_area) const override {
    if (rc.first < 0 || maze_.size() <= rc.first || rc.second < 0 ||
        maze_[rc.first].size() <= rc.second) {
      return out_of_area;
    }
    return GetSymbol(rc);
  }

  //////////////////////////////////////////////////////////////////////////////
  // APIs for LambdaMan
  //////////////////////////////////////////////////////////////////////////////
  int GetVitality() override {
    return vitality_;
  }
  int GetLives() const override {
    return life_;
  }
  int GetScore() const override {
    return score_;
  }
  int GetNumberOfGhosts() const override {
    return ghosts_.size();
  }
  const Maze& GetMaze() const override {
    return maze_;
  }

  //////////////////////////////////////////////////////////////////////////////
  // APIs for Ghost
  //////////////////////////////////////////////////////////////////////////////
  Coordinate GetFirstLambdaManRC() const override {
    if (lman_ == nullptr) {
      return CoordinateUtil::Null();
    }
    return lman_->GetRC();
  }

  Coordinate GetSecondLambdaManRC() const override {
    // TODO(imos): Implement second lambda-man.
    return CoordinateUtil::Null();
  }

  Coordinate GetGhostInitialRC(int ghost_index) const override {
    if (ghost_index < 0 || ghosts_.size() <= ghost_index) {
      return CoordinateUtil::Null();
    }
    return ghosts_[ghost_index]->GetInitialRC();
  }

  Coordinate GetGhostRC(int ghost_index) const override {
    if (ghost_index < 0 || ghosts_.size() <= ghost_index) {
      return CoordinateUtil::Null();
    }
    return ghosts_[ghost_index]->GetRC();
  }

  int GetGhostVitality(int ghost_index) const override {
    if (ghost_index < 0 || ghosts_.size() <= ghost_index) {
      return -1;
    }
    return ghosts_[ghost_index]->GetVitality();
  }

  int GetGhostDirection(int ghost_index) const override {
    if (ghost_index < 0 || ghosts_.size() <= ghost_index) {
      return -1;
    }
    return ghosts_[ghost_index]->GetDirection();
  }

 private:
  void Eat(const Coordinate& rc) { maze_[rc.first][rc.second] = ' '; }

  vector<GhostFactory*> ghost_factories_;
  vector<std::unique_ptr<GhostInterface>> ghosts_;
  LambdaMan* lman_;
  // The current state of the world
  // NOTE: Only pills and power pills will be cosumed to be empty.
  //       Fruit and Lambda-Man symbols indicate their locations but not their
  // states.
  Maze maze_;
  Coordinate fruit_location_;
  int total_pills_;
  int life_;
  int vitality_;
  int score_;
  int tick_;
};

#endif  // SIM_SIM_H_
