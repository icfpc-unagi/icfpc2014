#include "ghost/ghost-ai-manager.h"

#include <gflags/gflags.h>

#include "base/split.h"
#include "util/flags.h"

namespace ghost {

vector<::GhostFactory*> GhostAiManager::GetGhosts() {
  vector<::GhostFactory*> ghosts;
  for (const string& ghost_name : Split(FLAGS_ghosts, ",")) {
    auto ghost_factory = ghost_factory_.find(ghost_name);
    CHECK(ghost_factory != ghost_factory_.end())
        << "no such ghost: " << ghost_name;
    ghosts.push_back(ghost_factory->second.get());
  }
  return ghosts;
}

GhostAiManager* GetGhostAiManager() {
  static GhostAiManager* ghost_ai_manager = nullptr;
  if (ghost_ai_manager == nullptr) {
    ghost_ai_manager = new GhostAiManager;
  }
  return ghost_ai_manager;
}

}  // namespace ghost
