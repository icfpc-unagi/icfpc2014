#include "ghost/ghost-ai-manager.h"

#include <gflags/gflags.h>

#include "base/split.h"

DEFINE_string(ghosts, "fickle", "Comma-separated list of ghosts to use.");

namespace ghost {

vector<::GhostFactory*> GhostAiManager::GetGhosts(int num_ghosts) {
  vector<::GhostFactory*> ghosts;
  vector<string> ghost_names = Split(FLAGS_ghosts, ",");
  for (int i = 0; i < num_ghosts; i++) {
    const string& ghost_name = ghost_names[i % ghost_names.size()];
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
