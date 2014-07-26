#include "ghost/ai/ai.h"
#include "ghost/ai/chokudai.h"
#include "ghost/ai/fickle.h"

namespace ghost {

void RegisterAi(map<string, std::unique_ptr<GhostFactory>>* ghost_factories) {
  (*ghost_factories)["chokudai"].reset(new chokudaiGhostFactory);
  (*ghost_factories)["fickle"].reset(new fickleGhostFactory);
}

}  // namespace ghost
