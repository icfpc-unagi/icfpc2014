#include "lman/lambda-man-ai-manager.h"

#include <gflags/gflags.h>

#include "base/split.h"

DEFINE_string(lman, "chokudai-10",
              "Comma-separated list of LambdaMan AIs to use.");

namespace lman {

vector<::LambdaManFactory*> LambdaManAiManager::GetLambdaManAis() {
  vector<::LambdaManFactory*> lambda_man_ais;
  for (const string& lambda_man_name : Split(FLAGS_lman, ",")) {
    auto lambda_man_factory = lambda_man_factory_.find(lambda_man_name);
    CHECK(lambda_man_factory != lambda_man_factory_.end())
        << "no such lambda_man: " << lambda_man_name;
    lambda_man_ais.push_back(lambda_man_factory->second.get());
  }
  return lambda_man_ais;
}

LambdaManAiManager* GetLambdaManAiManager() {
  static LambdaManAiManager* lambda_man_ai_manager = nullptr;
  if (lambda_man_ai_manager == nullptr) {
    lambda_man_ai_manager = new LambdaManAiManager;
  }
  return lambda_man_ai_manager;
}

}  // namespace lman
