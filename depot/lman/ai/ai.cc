#include "lman/ai/ai.h"

#include "lman/ai/chokudai-10.h"

namespace lman {

void RegisterAi(
    map<string, std::unique_ptr<LambdaManFactory>>* lambda_man_factories) {
  (*lambda_man_factories)["chokudai-10"].reset(new chokudai_10LambdaManFactory);
}

}  // namespace lman
