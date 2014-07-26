#ifndef LMAN_AI_AI_H_
#define LMAN_AI_AI_H_

#include <map>
#include <memory>
#include <string>

class LambdaManFactory;

namespace lman {

void RegisterAi(
    map<string, std::unique_ptr<LambdaManFactory>>* lambda_man_factories);

}  // namespace lman

#endif  // LMAN_AI_AI_H_
