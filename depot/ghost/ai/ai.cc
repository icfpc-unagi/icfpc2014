#include "ghost/ai/ai.h"
#include "ghost/ai/fickle.h"
#include "ghost/ghost-ai-manager.h"

namespace ghost {

void Register() {
  GetGhostAiManager()->RegisterGhostFactory(
      "fickle", new fickleGhostFactory);
}

}  // namespace ghost
