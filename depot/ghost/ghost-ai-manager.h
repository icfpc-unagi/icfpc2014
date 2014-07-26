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
  GhostAiManager() {}
  virtual ~GhostAiManager() {}

  void RegisterGhostFactory(
      const string& name, ::GhostFactory* ghost_factory) {
    ghost_factory_[name].reset(ghost_factory);
  }

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
