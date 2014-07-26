#include "ghost/ai/ai.h"
#include "ghost/ai/chokudai.h"
#include "ghost/ai/fickle.h"
#include "ghost/ghost-ai-manager.h"

namespace ghost {

void RegisterAi() {
  GetGhostAiManager()->RegisterGhostFactory(
      "chokudai", new chokudaiGhostFactory);
  GetGhostAiManager()->RegisterGhostFactory(
      "fickle", new fickleGhostFactory);
}

}  // namespace ghost
