#include "translator/lib.h"

int main() {
  P game, nazo;
  P state = init(game, nazo);
  while(true){
    std::cout << "state: " << state.to_string() << std::endl;
    P ret = step(state, game);
    state = fst(ret);
    std::cout << "move: " << toi(snd(ret)) << std::endl;
  }
  return 0;
}
