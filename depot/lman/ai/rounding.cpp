#include "translator/lib.h"

int d;

// step
P step_(P ai, P game) {
	// int d;
	// d = toi(fst(ai));
	if (d == 3) {
		d = 0;
	} else {
		d = d + 1;
	}
	return P(top(0), d);
}

P step(P ai, P game) {
  return step_(ai, game);
}

P init(P game, P nazo) {
	d = 0;
	return top(0);
}
