#include "ghost/ghost-ai-manager.h"

namespace ghost {

GhostAiManager* GetGhostAiManager() {
  static GhostAiManager* ghost_ai_manager = nullptr;
  if (ghost_ai_manager == nullptr) {
    ghost_ai_manager = new GhostAiManager;
  }
  return ghost_ai_manager;
}

}  // namespace ghost
