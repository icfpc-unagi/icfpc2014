#include "ghost/ghost-ai-manager.h"

#include <gflags/gflags.h>

#include "base/split.h"
#include "sim/sim.h"

DEFINE_string(ghosts, "fickle", "Comma-separated list of ghosts to use.");

namespace ghost {

GhostAiManager::GhostAiManager() {}
GhostAiManager::~GhostAiManager() {}

vector<::GhostFactory*> GhostAiManager::GetGhostFactories() {
  vector<::GhostFactory*> ghost_factories;
  for (const string& ghost_name : Split(FLAGS_ghosts, ",")) {
    auto ghost_factory = ghost_factory_.find(ghost_name);
    CHECK(ghost_factory != ghost_factory_.end())
        << "no such ghost: " << ghost_name;
    ghost_factories.push_back(ghost_factory->second.get());
  }
  return ghost_factories;
}

GhostAiManager* GetGhostAiManager() {
  static GhostAiManager* ghost_ai_manager = nullptr;
  if (ghost_ai_manager == nullptr) {
    ghost_ai_manager = new GhostAiManager;
  }
  return ghost_ai_manager;
}

}  // namespace ghost
