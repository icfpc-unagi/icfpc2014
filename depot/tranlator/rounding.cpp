#include"lib.cpp"
#include "list.b"

// step
P step(P ai, P game) {
	int d;
	d = toi(fst(ai));
	if (d == 3) {
		d = 0;
	} else {
		d = d + 1;
	}
	return P(P(d, 0), d);
}

P init(P game, P nazo) {
	return P(0, 0);
}
