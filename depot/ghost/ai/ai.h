#ifndef GHOST_AI_AI_H_
#define GHOST_AI_AI_H_

#include <map>
#include <memory>
#include <string>

class GhostFactory;

namespace ghost {

void RegisterAi(map<string, std::unique_ptr<GhostFactory>>* ghost_factories);

}  // namespace ghost

#endif  // GHOST_AI_AI_H_
