#include"translator/lib.h"

int INF;

P board2DList;
int X;
int Y;
int manVitality;
int manX;
int manY;
int manDir;
int manLives;
int currentScore;
P ghostStatus;
int ghostN;
int fruitStatus;

int myor(int a, int b) {
	int ret = 1;
	if (a == 0) {
		if (b == 0) {
			ret = 0;
		}
	}
	return ret;
}

int myabs(int a) {
	if (a < 0) {
		a = -a;
	}
	return a;
}

int mymod(int a, int b) {
	return a - b * (a / b);
}

int randx;

int myrand(int m) {
	randx = mymod(randx * 163 + 43751, 1000033);
	return mymod(randx, m);
}

P swap(P p) {
	return P(snd(p), fst(p));
}

int mymax(int a, int b) {
	if (a < b) {
		a = b;
	}
	return a;
}

int mymin(int a, int b) {
	if (a > b) {
		a = b;
	}
	return a;
}

void debugList2D(P list) {
	while (atom(list) == 0) {
		debug(fst(list));
		list = snd(list);
	}
	debug(-1);
}

int lengthList(P list) {
	int res = 0;
	while (atom(list) == 0) {
		res += 1;
		list = snd(list);
	}
	return res;
}

P getList(P list, int i) {
	while (i > 0) {
		list = snd(list);
		i -= 1;
	}
	return fst(list);
}

P getList2D(P list2D, int i, int j) {
	return getList(getList(list2D, i), j);
}

P setList(P list, int i, P v) {
	if (i == 0) {
		list = P(v, snd(list));
	} else {
		list = P(fst(list), setList(snd(list), i - 1, v));
	}
	return list;
}

P setList2D(P list2D, int i, int j, P v) {
	return setList(list2D, i, setList(getList(list2D, i), j, v));
}

P reverseList(P list) {
	P p = top(0);
	while (atom(list) == 0) {
		p = P(fst(list), p);
		list = snd(list);
	}
	return p;
}

P createList(int n, P v) {
	P list = top(0);
	while (n > 0) {
		list = P(v, list);
		n -= 1;
	}
	return list;
}

P createList2D(int n, int m, P v) {
	P list = top(0);
	while (n > 0) {
		list = P(createList(m, v), list);
		n -= 1;
	}
	return list;
}

P getSubList(P list, int s, int t) {
	if (s >= t) {
		list = top(0);
	} else {
		if (s < 0) {
			list = P(0, getSubList(list, s + 1, t));
		} else {
			if (atom(list)) {
				list = P(0, getSubList(list, s + 1, t));
			} else {
				if (s == 0) {
					list = P(fst(list), getSubList(snd(list), 0, t - 1));
				} else {
					list = getSubList(snd(list), s - 1, t - 1);
				}
			}
		}
	}
	return list;
}

P getSubList2D(P list2D, int sy, int ty, int sx, int tx) {
	if (sy >= ty) {
		list2D = top(0);
	} else {
		if (sy < 0) {
			list2D = P(createList(tx - sx, 0), getSubList2D(list2D, sy + 1, ty, sx, tx));
		} else {
			if (atom(list2D)) {
				list2D = P(createList(tx - sx, 0), getSubList2D(list2D, sy + 1, ty, sx, tx));
			} else {
				if (sy == 0) {
					list2D = P(getSubList(fst(list2D), sx, tx), getSubList2D(snd(list2D), 0, ty - 1, sx, tx));
				} else {
					list2D = getSubList2D(snd(list2D), sy - 1, ty - 1, sx, tx);
				}
			}
		}
	}
	return list2D;
}

int dy(int d) {
	int ret = 0;
	if (d == 0) {
		ret = -1;
	} else {
		if (d == 2) {
			ret = 1;
		}
	}
	return ret;
}

int dx(int d) {
	int ret = 0;
	if (d == 1) {
		ret = 1;
	} else {
		if (d == 3) {
			ret = -1;
		}
	}
	return ret;
}

int evalAround(int x, int y) {
	int ret = 0;
	int D = 10;
	int i, j, d, k, t, i2, j2, d2, nearestPowerPill = INF, numSpace = 0;
	P tmp;
	P ghosts = ghostStatus;
	P ghost;
	P subBoard = getSubList2D(board2DList, y - D, y + D, x - D, x + D);
	P canReachLambda = setList2D(createList2D(D * 2, D * 2, -1), D, D, 0); // -1: unreachable, >=0, distance
	P canReachLambda2;
	P canReachGhost = createList2D(D * 2, D * 2, -1); // -1: unreachable, 0-3: one direction, 4: any directions
	P canReachGhost2;
	while (atom(ghosts) == 0) {
		ghost = fst(ghosts);
		ghosts = snd(ghosts);
		tmp = fst(snd(ghost));
		i = toi(fst(tmp)) - x + D;
		j = toi(snd(tmp)) - y + D;
		k = toi(snd(snd(ghost)));
		if (0 <= i) {
			if (i < 2 * D) {
				if (0 <= j) {
					if (j < 2 * D) {
						d = toi(getList2D(canReachGhost, j, i));
						if (d >= 0) {
							if (d == k) {
							} else {
								canReachGhost = setList2D(canReachGhost, j, i, 4);
							}
						} else {
							canReachGhost = setList2D(canReachGhost, j, i, k);
						}
					}
				}
			}
		}
	}
	t = 0;
	while (t < D) {
		canReachGhost2 = createList2D(2 * D, 2 * D, -1);
		i = 0;
//		debug(t);
//		debugList2D(canReachGhost);
		while (i < 2 * D) {
			j = 0;
			while (j < 2 * D) {
				k = toi(getList2D(canReachGhost, j, i));
				if (k >= 0) {
					d = 0;
					while (d < 4) {
						if (mymod(d + 2, 4) == k) {
						} else {
							i2 = i + dx(d);
							j2 = j + dy(d);
							if (0 <= i2) {
								if (i2 < 2 * D) {
									if (0 <= j2) {
										if (j2 < 2 * D) {
											if (toi(getList2D(subBoard, j2, i2)) > 0) {
												d2 = toi(getList2D(canReachGhost2, j2, i2));
												if (d2 >= 0) {
													if (d2 == d) {
													} else {
														canReachGhost2 = setList2D(canReachGhost2, j2, i2, 4);
													}
												} else {
													canReachGhost2 = setList2D(canReachGhost2, j2, i2, d);
												}
											}
										}
									}
								}
							}
						}
						d += 1;
					}
				}
				j += 1;
			}
			i += 1;
		}
		canReachGhost = canReachGhost2;
		i = 0;
		canReachLambda2 = createList2D(2 * D, 2 * D, -1);
		while (i < 2 * D) {
			j = 0;
			while (j < 2 * D) {
				k = toi(getList2D(canReachLambda, j, i));
				if (k >= 0) {
					if (toi(getList2D(canReachGhost, j, i)) < 0) {
						d2 = toi(getList2D(canReachLambda2, j, i));
						if ((d2 < 0) + (d2 > k)) {
							canReachLambda2 = setList2D(canReachLambda2, j, i, k);
						}
						if (t > 0) {
							d = 0;
							while (d < 4) {
								i2 = i + dx(d);
								j2 = j + dy(d);
								if (0 <= i2) {
									if (i2 < 2 * D) {
										if (0 <= j2) {
											if (j2 < 2 * D) {
												if (toi(getList2D(canReachGhost, j2, i2)) < 0) {
													if (toi(getList2D(subBoard, j2, i2)) > 0) {
														d2 = toi(getList2D(canReachLambda2, j2, i2));
														if ((d2 < 0) + (d2 > k + 1)) {
															canReachLambda2 = setList2D(canReachLambda2, j2, i2, k + 1);
														}
													}
												}
											}
										}
									}
								}
								d += 1;
							}
						}
					}
				}
				j += 1;
			}
			i += 1;
		}
		canReachLambda = canReachLambda2;
		t += 1;
	}
	i = 0;
	while (i < 2 * D) {
		j = 0;
		while (j < 2 * D) {
			if ((i == D) * (j == D)) {
			} else {
				d = toi(getList2D(canReachLambda, j, i));
				if (d >= 0) {
					numSpace++;
					k = toi(getList2D(subBoard, j, i));
					if (k == 1) {
						ret += 100 / (d + 1);
					} else {
						if (k == 2) {
							ret += 1000 / (d + 1);
						} else {
							if (k == 3) {
								if (nearestPowerPill > d) {
									nearestPowerPill = d;
								}
							}
						}
					}
				}
			}
			j += 1;
		}
		i += 1;
	}
	if (nearestPowerPill < INF) {
		ret += 40000 / (nearestPowerPill + 1);
	}
	if (numSpace == 0) {
		ret -= 2000000;
	}
	return ret;
}

int eval(int x, int y) {
	int c = toi(getList2D(board2DList, y, x));
	int ret = -1000000000;
	int i, d;
	P tmp;
	if (c > 0) {
		ret = 0; // myrand(10);
		if (c == 2) {
			ret += 1000;
		} else {
			if (c == 3) {
				ret += 40000;
			}
		}
		ret += evalAround(x, y);
		i = 0;
		while (i < ghostN) {
			tmp = fst(snd(getList(ghostStatus, i)));
			d = myabs(toi(fst(tmp)) - x) + myabs(toi(snd(tmp)) - y);
			if (d == 0) {
				if (manVitality > 0) {
					ret += 80000;
				} else {
					ret -= 10000000;
				}
			} else {
				if (d <= 1) {
					if (manVitality > 0) {
						ret += 40000;
					} else {
						ret -= 5000000;
					}
				}
			}
			i += 1;
		}
	}
	return ret;
}

P step_(P ai, P game) {
	P manStatus;
	int ret, dir, maxScore, score, x, y;
	board2DList = fst(game);
	manStatus = fst(snd(game));
	ghostStatus = fst(snd(snd(game)));
	ghostN = lengthList(ghostStatus);
	fruitStatus = toi(snd(snd(snd(game))));
	manVitality = toi(fst(manStatus));
	manX = toi(fst(fst(snd(manStatus))));
	manY = toi(snd(fst(snd(manStatus))));
	manDir = toi(fst(snd(snd(manStatus))));
	manLives = toi(fst(snd(snd(snd(manStatus)))));
	currentScore = toi(snd(snd(snd(snd(manStatus)))));
	ret = -1;
	maxScore = -INF;
	dir = 0;
	while (dir < 4) {
		x = manX + dx(dir);
		y = manY + dy(dir);
		if (toi(getList2D(board2DList, y, x)) == 0) {
			x = manX;
			y = manY;
		}
		score = eval(x, y);
		if (maxScore < score) {
			maxScore = score;
			ret = dir;
		}
		debug(score);
		dir += 1;
	}
//	debugList2D(dist2D);
	return P(ai, ret);
}

// step
P step(P ai, P game) {
	return step_(ai, game);
}

P init(P game, P nazo) {
	INF = 1000000000;
	board2DList = fst(game);
	Y = lengthList(board2DList);
	X = lengthList(fst(board2DList));
	return top(0);
}
