#ifndef GHOST_GHOST_AI_MANAGER_H_
#define GHOST_GHOST_AI_MANAGER_H_

#include <stdint.h>
#include <memory>
#include <vector>

#include <glog/logging.h>

#include "sim/sim.h"

namespace ghost {

class GhostAiManager {
 public:
  GhostAiManager();
  void RegisterGhostFactory(
      const string& name, ::GhostFactory* ghost_factory) {
    ghost_factory_.emplace(
        name, std::unique_ptr<::GhostFactory>(ghost_factory));
  }

 private:
  map<string, std::unique_ptr<::GhostFactory>> ghost_factory_;
};

GhostAiManager* GetGhostAiManager();

}  // namespace ghost

#endif  // GHOST_GHOST_AI_MANAGER_H_
