#ifndef SIM_GHOST_INTERFACE_H_
#define SIM_GHOST_INTERFACE_H_

#include "sim/character.h"
#include "sim/game-interface.h"
#include "util/coordinate.h"

// Ghost CPU interface
class GhostInterface : public Character {
 public:
  GhostInterface() : game_(nullptr) {}

  void Init(GameInterface* game, int ghost_index) {
    game_ = game;
    ghost_index_ = ghost_index;
    ghost_vitality_ = 0;
  }
  virtual int Step() = 0;

  int GetGhostIndex() { return ghost_index_; }
  int GetGhostVitality() { return ghost_vitality_; }

 protected:
  GameInterface* game_;
  int ghost_index_;
  int ghost_vitality_;
};

// To create a ghost class above
class GhostFactory {
 public:
  virtual ~GhostFactory() {}
  virtual std::unique_ptr<GhostInterface> Create() = 0;
};

#endif  // SIM_GHOST_INTERFACE_H_
