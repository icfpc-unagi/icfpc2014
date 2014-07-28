#include "lman/ai/ai.h"
#include "lman/ai/chokudai-10.h"
#include "lman/ai/chokudai-12.h"
#include "lman/ai/chokudai-13.h"
#include "lman/ai/chokudai-14.h"
#include "lman/ai/chokudai-28.h"
#include "lman/ai/chokudai-29.h"
#include "lman/ai/chokudai-30.h"
#include "lman/ai/chokudai-32.h"
#include "lman/ai/chokudai-33.h"
#include "lman/ai/chokudai-34.h"
#include "lman/ai/chokudai-35.h"
#include "lman/ai/chokudai-36.h"
#include "lman/ai/chokudai-4.h"
#include "lman/ai/chokudai-8.h"
#include "lman/ai/migi.h"
#include "lman/ai/orz.h"
#include "lman/ai/piyo.h"
#include "lman/ai/rounding.h"
#include "lman/ai/tos-hungry.h"
#include "lman/ai/tos-sokushi-kaihi.h"
#include "lman/ai/tos-yowaki.h"
#include "lman/ai/wata-07.h"
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
  (*lambda_man_factories)["chokudai-28"].reset(
      new chokudai_28LambdaManFactory);
  (*lambda_man_factories)["chokudai-29"].reset(
      new chokudai_29LambdaManFactory);
  (*lambda_man_factories)["chokudai-30"].reset(
      new chokudai_30LambdaManFactory);
  (*lambda_man_factories)["chokudai-32"].reset(
      new chokudai_32LambdaManFactory);
  (*lambda_man_factories)["chokudai-33"].reset(
      new chokudai_33LambdaManFactory);
  (*lambda_man_factories)["chokudai-34"].reset(
      new chokudai_34LambdaManFactory);
  (*lambda_man_factories)["chokudai-35"].reset(
      new chokudai_35LambdaManFactory);
  (*lambda_man_factories)["chokudai-36"].reset(
      new chokudai_36LambdaManFactory);
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
  (*lambda_man_factories)["wata-07"].reset(
      new wata_07LambdaManFactory);
  (*lambda_man_factories)["wata-10"].reset(
      new wata_10LambdaManFactory);
  (*lambda_man_factories)["wata_cpp"].reset(
      new wata_cppLambdaManFactory);
}

}  // namespace lman
