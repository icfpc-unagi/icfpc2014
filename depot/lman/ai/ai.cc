#include "lman/ai/ai.h"
#include "lman/ai/chokudai-10.h"
#include "lman/ai/chokudai-4.h"
#include "lman/ai/chokudai-8.h"
#include "lman/ai/rounding.h"

namespace lman {

void RegisterAi(
    map<string, std::unique_ptr<LambdaManFactory>>* lambda_man_factories) {

  (*lambda_man_factories)["chokudai-10"].reset(
      new chokudai_10LambdaManFactory);
  (*lambda_man_factories)["chokudai-4"].reset(
      new chokudai_4LambdaManFactory);
  (*lambda_man_factories)["chokudai-8"].reset(
      new chokudai_8LambdaManFactory);
  (*lambda_man_factories)["rounding"].reset(
      new roundingLambdaManFactory);
}

}  // namespace lman
