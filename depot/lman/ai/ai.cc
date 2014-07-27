#include "lman/ai/ai.h"
#include "lman/ai/chokudai-10.h"
#include "lman/ai/chokudai-12.h"
#include "lman/ai/chokudai-13.h"
#include "lman/ai/chokudai-14.h"
#include "lman/ai/chokudai-4.h"
#include "lman/ai/chokudai-8.h"
#include "lman/ai/migi.h"
#include "lman/ai/orz.h"
#include "lman/ai/piyo.h"
#include "lman/ai/rounding.h"
#include "lman/ai/tos-hungry.h"
#include "lman/ai/tos-sokushi-kaihi.h"
#include "lman/ai/tos-yowaki.h"
#include "lman/ai/wata-10.h"
#include "lman/ai/wata_cpp.h"

namespace lman {

void RegisterAi(
    map<string, std::unique_ptr<LambdaManFactory>>* lambda_man_factories) {

  (*lambda_man_factories)["chokudai-10"].reset(
      new chokudai_10LambdaManFactory);
  (*lambda_man_factories)["chokudai-12"].reset(
      new chokudai_12LambdaManFactory);
  (*lambda_man_factories)["chokudai-13"].reset(
      new chokudai_13LambdaManFactory);
  (*lambda_man_factories)["chokudai-14"].reset(
      new chokudai_14LambdaManFactory);
  (*lambda_man_factories)["chokudai-4"].reset(
      new chokudai_4LambdaManFactory);
  (*lambda_man_factories)["chokudai-8"].reset(
      new chokudai_8LambdaManFactory);
  (*lambda_man_factories)["migi"].reset(
      new migiLambdaManFactory);
  (*lambda_man_factories)["orz"].reset(
      new orzLambdaManFactory);
  (*lambda_man_factories)["piyo"].reset(
      new piyoLambdaManFactory);
  (*lambda_man_factories)["rounding"].reset(
      new roundingLambdaManFactory);
  (*lambda_man_factories)["tos-hungry"].reset(
      new tos_hungryLambdaManFactory);
  (*lambda_man_factories)["tos-sokushi-kaihi"].reset(
      new tos_sokushi_kaihiLambdaManFactory);
  (*lambda_man_factories)["tos-yowaki"].reset(
      new tos_yowakiLambdaManFactory);
  (*lambda_man_factories)["wata-10"].reset(
      new wata_10LambdaManFactory);
  (*lambda_man_factories)["wata_cpp"].reset(
      new wata_cppLambdaManFactory);
}

}  // namespace lman
