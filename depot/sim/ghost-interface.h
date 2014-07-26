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
    index_ = ghost_index;
    vitality_ = 0;
  }
  virtual int Step() = 0;

  int GetIndex() const { return index_; }
  int GetVitality() const { return vitality_; }
  void SetVitality(int vitality) { vitality_ = vitality; }

 protected:
  GameInterface* game_;
  int index_;
  int vitality_;
};

// To create a ghost class above
class GhostFactory {
 public:
  virtual ~GhostFactory() {}
  virtual std::unique_ptr<GhostInterface> Create() = 0;
};

#endif  // SIM_GHOST_INTERFACE_H_
