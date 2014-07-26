#ifndef GHOST_GHOST_AI_MANAGER_H_
#define GHOST_GHOST_AI_MANAGER_H_

#include <stdint.h>
#include <memory>
#include <vector>

#include <glog/logging.h>

#include "ghost/ai/ai.h"
#include "sim/sim.h"

namespace ghost {

class GhostAiManager {
 public:
  GhostAiManager() {
    RegisterAi(&ghost_factory_);
  }
  virtual ~GhostAiManager() {}

  vector<string> GetGhostAiNames() {
    vector<string> names;
    for (const auto& name_and_ghost_factory : ghost_factory_) {
      names.push_back(name_and_ghost_factory.first);
    }
    return names;
  }

  vector<::GhostFactory*> GetGhosts(int num_ghosts);

 private:
  map<string, std::unique_ptr<::GhostFactory>> ghost_factory_;
};

GhostAiManager* GetGhostAiManager();

}  // namespace ghost

#endif  // GHOST_GHOST_AI_MANAGER_H_
