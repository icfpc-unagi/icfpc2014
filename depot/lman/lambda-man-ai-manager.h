#ifndef LMAN_LAMBDA_MAN_AI_MANAGER_H_
#define LMAN_LAMBDA_MAN_AI_MANAGER_H_

#include <stdint.h>
#include <memory>
#include <vector>

#include <glog/logging.h>

#include "lman/ai/ai.h"
#include "sim/lambda-man-interface.h"

namespace lman {

class LambdaManAiManager {
 public:
  LambdaManAiManager() {
    RegisterAi(&lambda_man_factory_);
  }
  virtual ~LambdaManAiManager() {}

  vector<string> GetLambdaManAiNames() {
    vector<string> names;
    for (const auto& name_and_lambda_man_factory : lambda_man_factory_) {
      names.push_back(name_and_lambda_man_factory.first);
    }
    return names;
  }

  vector<::LambdaManFactory*> GetLambdaManAis();

 private:
  map<string, std::unique_ptr<::LambdaManFactory>> lambda_man_factory_;
};

LambdaManAiManager* GetLambdaManAiManager();

}  // namespace lman

#endif  // LMAN_LAMBDA_MAN_AI_MANAGER_H_
