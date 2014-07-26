#include "ghost/ai/ai.h"
#include "ghost/ghost-ai-manager.h"
#include "sim/sim.h"

#include <gflags/gflags.h>
#include <glog/logging.h>

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  ghost::RegisterAi();
  ghost::GhostAiManager* ghost_ai_manager = ghost::GetGhostAiManager();

  printf("Registered AIs\n");
  for (const string& name : ghost_ai_manager->GetGhostAiNames()) {
    printf("  AI: %s\n", name.c_str());
  }

  return 0;
}
