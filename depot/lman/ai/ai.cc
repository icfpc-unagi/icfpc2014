#include "lman/ai/ai.h"
#include "lman/ai/chokudai-10.h"
#include "lman/ai/chokudai-12.h"
#include "lman/ai/chokudai-13.h"
#include "lman/ai/chokudai-14.h"
#include "lman/ai/chokudai-15.h"
#include "lman/ai/chokudai-16.h"
#include "lman/ai/chokudai-17.h"
#include "lman/ai/chokudai-18.h"
#include "lman/ai/chokudai-19.h"
#include "lman/ai/chokudai-20.h"
#include "lman/ai/chokudai-21.h"
#include "lman/ai/chokudai-22.h"
#include "lman/ai/chokudai-23.h"
#include "lman/ai/chokudai-24.h"
#include "lman/ai/chokudai-25.h"
#include "lman/ai/chokudai-26.h"
#include "lman/ai/chokudai-27.h"
#include "lman/ai/chokudai-28.h"
#include "lman/ai/chokudai-29.h"
#include "lman/ai/chokudai-30.h"
#include "lman/ai/chokudai-32.h"
#include "lman/ai/chokudai-4.h"
#include "lman/ai/chokudai-8.h"
#include "lman/ai/migi.h"
#include "lman/ai/orz.h"
#include "lman/ai/piyo.h"
#include "lman/ai/rounding.h"
#include "lman/ai/tos-hungry.h"
#include "lman/ai/tos-sokushi-kaihi.h"
#include "lman/ai/tos-yowaki.h"
#include "lman/ai/tos1.h"
#include "lman/ai/tos2.h"
#include "lman/ai/wata-05.h"
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
  (*lambda_man_factories)["chokudai-15"].reset(
      new chokudai_15LambdaManFactory);
  (*lambda_man_factories)["chokudai-16"].reset(
      new chokudai_16LambdaManFactory);
  (*lambda_man_factories)["chokudai-17"].reset(
      new chokudai_17LambdaManFactory);
  (*lambda_man_factories)["chokudai-18"].reset(
      new chokudai_18LambdaManFactory);
  (*lambda_man_factories)["chokudai-19"].reset(
      new chokudai_19LambdaManFactory);
  (*lambda_man_factories)["chokudai-20"].reset(
      new chokudai_20LambdaManFactory);
  (*lambda_man_factories)["chokudai-21"].reset(
      new chokudai_21LambdaManFactory);
  (*lambda_man_factories)["chokudai-22"].reset(
      new chokudai_22LambdaManFactory);
  (*lambda_man_factories)["chokudai-23"].reset(
      new chokudai_23LambdaManFactory);
  (*lambda_man_factories)["chokudai-24"].reset(
      new chokudai_24LambdaManFactory);
  (*lambda_man_factories)["chokudai-25"].reset(
      new chokudai_25LambdaManFactory);
  (*lambda_man_factories)["chokudai-26"].reset(
      new chokudai_26LambdaManFactory);
  (*lambda_man_factories)["chokudai-27"].reset(
      new chokudai_27LambdaManFactory);
  (*lambda_man_factories)["chokudai-28"].reset(
      new chokudai_28LambdaManFactory);
  (*lambda_man_factories)["chokudai-29"].reset(
      new chokudai_29LambdaManFactory);
  (*lambda_man_factories)["chokudai-30"].reset(
      new chokudai_30LambdaManFactory);
  (*lambda_man_factories)["chokudai-32"].reset(
      new chokudai_32LambdaManFactory);
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
  (*lambda_man_factories)["tos1"].reset(
      new tos1LambdaManFactory);
  (*lambda_man_factories)["tos2"].reset(
      new tos2LambdaManFactory);
  (*lambda_man_factories)["wata-05"].reset(
      new wata_05LambdaManFactory);
  (*lambda_man_factories)["wata-07"].reset(
      new wata_07LambdaManFactory);
  (*lambda_man_factories)["wata-10"].reset(
      new wata_10LambdaManFactory);
  (*lambda_man_factories)["wata_cpp"].reset(
      new wata_cppLambdaManFactory);
}

}  // namespace lman
