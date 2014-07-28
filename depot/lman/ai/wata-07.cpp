#include"translator/lib.h"
#include"sbl/array32.h"
#include"sbl/queue.h"
#include"sbl/array256.h"

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
int fruitBonus;
int lastPointUp;

P board2DArray;
P powerPills;
P topKPowerPills;

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

P getSubList_(P list, int s, int t) {
	if (s >= t) {
		list = P(0, 0);
	} else {
		if (s < 0) {
			list = P(0, getSubList_(list, s + 1, t));
		} else {
			if (atom(list)) {
				list = P(0, getSubList_(list, s + 1, t));
			} else {
				if (s == 0) {
					list = P(fst(list), getSubList_(snd(list), 0, t - 1));
				} else {
					list = getSubList_(snd(list), s - 1, t - 1);
				}
			}
		}
	}
	return list;
}

P getSubList2D_(P list2D, int sy, int ty, int sx, int tx) {
	if (sy >= ty) {
		list2D = P(createList(tx - sx + 2, 0), 0);
	} else {
		if (sy < 0) {
			list2D = P(createList(tx - sx + 2, 0), getSubList2D_(list2D, sy + 1, ty, sx, tx));
		} else {
			if (atom(list2D)) {
				list2D = P(createList(tx - sx + 2, 0), getSubList2D_(list2D, sy + 1, ty, sx, tx));
			} else {
				if (sy == 0) {
					list2D = P(P(0, getSubList_(fst(list2D), sx, tx)), getSubList2D_(snd(list2D), 0, ty - 1, sx, tx));
				} else {
					list2D = getSubList2D_(snd(list2D), sy - 1, ty - 1, sx, tx);
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

int getFruitBonus() {
	int level = (X * Y - 1) / 100 + 1;
	int ret = 0;
	if (level == 1) {
		ret = 100;
	} else {
		if (level == 2) {
			ret = 300;
		} else {
			if (level <= 4) {
				ret = 500;
			} else {
				if (level <= 6) {
					ret = 700;
				} else {
					if (level <= 8) {
						ret = 1000;
					} else {
						if (level <= 10) {
							ret = 2000;
						} else {
							if (level <= 12) {
								ret = 3000;
							} else {
								ret = 5000;
							}
						}
					}
				}
			}
		}
	}
	return ret;
}

P insert(P list, int key, P val) {
	if (atom(list)) {
		list = P(P(key, val), 0);
	} else {
		if (toi(fst(fst(list))) < key) {
			list = P(P(key, val), list);
		} else {
			list = P(fst(list), insert(snd(list), key, val));
		}
	}
	return list;
}

P getTopKPowerPills(int x, int y, int k) {
	P list = top(0);
	int num = 0;
	P pills = powerPills;
	P p;
	while (atom(pills) == 0) {
		p = fst(pills);
		pills = snd(pills);
		if (toi(get_array2d256(board2DArray, toi(snd(p)), toi(fst(p)))) == 1) {
		} else {
			list = insert(list, myabs(toi(fst(p)) - x) + myabs(toi(snd(p)) - y), p);
			if (lengthList(list) > k) {
				list = snd(list);
			}
		}
	}
	return list;
}

P getPowerPills() {
	P list = top(0);
	P board2D = board2DList;
	P board1D;
	int y = 0, x;
	while (atom(board2D) == 0) {
		board1D = fst(board2D);
		board2D = snd(board2D);
		x = 0;
		while (atom(board1D) == 0) {
			if (toi(fst(board1D)) == 3) {
				list = P(P(x, y), list);
			}
			board1D = snd(board1D);
			x += 1;
		}
		y += 1;
	}
	return list;
}

int evalAround(int x, int y, int near) {
	int ret = 0;
	int D = 7, D2 = D * 2;
	int i, j, c, d, k, t, i2, j2, d2, nearestPowerPill = INF, numSpace = 0, death = 0, takePowerPill = 0, live, newSpace, score2 = 0;
	P tmp, p;
	P ghosts = ghostStatus;
	P ghost;
	P subBoard = list2d_to_array2d32(P(createList(2 * D + 3, 0), getSubList2D_(board2DList, y - D, y + D + 1, x - D, x + D + 1)));
	P canReachLambda = set_array2d32(list2d_to_array2d32(createList2D(D2 + 1, D2 + 1, -1)), D, D, 0); // -1: unreachable, >=0, distance
	P canReachLambda2;
	P canReachGhost = list2d_to_array2d32(createList2D(D2 + 1, D2 + 1, -1)); // -1: unreachable, 0-3: one direction, 4: any directions
	P canReachGhost2;
	while (atom(ghosts) == 0) {
		ghost = fst(ghosts);
		ghosts = snd(ghosts);
		tmp = fst(snd(ghost));
		i = toi(fst(tmp)) - x + D;
		j = toi(snd(tmp)) - y + D;
		k = toi(snd(snd(ghost)));
		if (0 <= i) {
			if (i <= D2) {
				if (0 <= j) {
					if (j <= D2) {
						d = toi(get_array2d32(canReachGhost, j, i));
						if (d >= 0) {
							if (d == k) {
							} else {
								canReachGhost = set_array2d32(canReachGhost, j, i, 4);
							}
						} else {
							canReachGhost = set_array2d32(canReachGhost, j, i, k);
						}
					}
				}
			}
		}
	}
	t = 0;
	while (t < D2) {
		canReachGhost2 = list2d_to_array2d32(createList2D(D2 + 1, D2 + 1, -1));
		i = 0;
		while (i <= D2) {
			j = 0;
			while (j <= D2) {
				k = toi(get_array2d32(canReachGhost, j, i));
				if (k >= 0) {
					d = 0;
					while (d < 4) {
						if (mymod(d + 2, 4) == k) {
						} else {
							i2 = i + dx(d);
							j2 = j + dy(d);
							if (toi(get_array2d32(subBoard, j2 + 1, i2 + 1)) > 0) {
								d2 = toi(get_array2d32(canReachGhost2, j2, i2));
								if (d2 >= 0) {
									if (d2 == d) {
									} else {
										canReachGhost2 = set_array2d32(canReachGhost2, j2, i2, 4);
									}
								} else {
									canReachGhost2 = set_array2d32(canReachGhost2, j2, i2, d);
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
		canReachLambda2 = list2d_to_array2d32(createList2D(D2 + 1, D2 + 1, -1));
		live = 0;
		while (i <= D2) {
			j = 0;
			while (j <= D2) {
				k = toi(get_array2d32(canReachLambda, j, i));
				if (k >= 0) {
					if (toi(get_array2d32(canReachGhost, j, i)) < 0) {
						d2 = toi(get_array2d32(canReachLambda2, j, i));
						if ((d2 < 0) + (d2 > k)) {
							if (d2 < 0) {
								live += 1;
							}
							canReachLambda2 = set_array2d32(canReachLambda2, j, i, k);
						}
						if ((t > 0) + near) {
							d = 0;
							while (d < 4) {
								i2 = i + dx(d);
								j2 = j + dy(d);
								c = toi(get_array2d32(subBoard, j2 + 1, i2 + 1));
								if (c > 0) {
									if (toi(get_array2d32(canReachGhost, j2, i2)) < 0) {
										if (c == 3) {
											takePowerPill = 1;
											if (nearestPowerPill > k + 1) {
												nearestPowerPill = k + 1;
											}
										}
										d2 = toi(get_array2d32(canReachLambda2, j2, i2));
										if ((d2 < 0) + (d2 > k + 1)) {
											if (d2 < 0) {
												live += 1;
											}
											canReachLambda2 = set_array2d32(canReachLambda2, j2, i2, k + 1);
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
		if (live == 0) {
			if (death == 0) {
				death = t + 1;
			}
		}
		canReachLambda = canReachLambda2;
		t += 1;
	}
	newSpace = 0;
	i = 0;
	while (i <= D2) {
		j = 0;
		while (j <= D2) {
			if ((i == D) * (j == D)) {
			} else {
				d = toi(get_array2d32(canReachLambda, j, i));
				if (d >= 0) {
					numSpace += 1;
					if (d == D - 1 + near) {
						newSpace += 1;
					}
					k = toi(get_array2d32(subBoard, j + 1, i + 1));
					if (k == 2) {
						ret += 1000 / (d + 1);
					} else {
						if (k == 3) {
						} else {
							if (k == 4) {
								if (fruitStatus > 0) {
									ret += fruitBonus * 100 / (d + 1);
								}
							}
						}
					}
					d2 = INF;
					tmp = topKPowerPills;
					while (atom(tmp) == 0) {
						p = snd(fst(tmp));
						tmp = snd(tmp);
						d2 = mymin(d2, myabs(i - D + x - toi(fst(p))) + myabs(j - D + y - toi(snd(p))));
					}
					score2 += 10000 / (d2 + 1) / (d + 1);
				}
			}
			j += 1;
		}
		i += 1;
	}
	if (nearestPowerPill < INF) {
		if ((lastPointUp > 50) + near) {
			ret += 200000 / (nearestPowerPill + 1);
		} else {
			ret += 20000;// / (nearestPowerPill + 1);
		}
	} else {
		ret += score2 / (D * D);
	}
	if (death > 0) {
		if (takePowerPill == 0) {
			ret -= 1000000000 / death;
		}
	} else {
		if (newSpace == 0) {
			if (takePowerPill == 0) {
				ret -= 1000000000 / D2;
			}
		}
	}
	return ret;
}

int evalAround_(int x, int y, int near) {
	int ret = 0;
	int D = 10;
	int i, j, c, d, k, t, i2, j2, d2, nearestPowerPill = INF, numSpace = 0, death = 0, takePowerPill = 0, live, newSpace, score2 = 0;
	P tmp, p;
	P ghosts = ghostStatus;
	P ghost;
	P subBoard = getSubList2D(board2DList, y - D, y + D + 1, x - D, x + D + 1);
	P canReachLambda = setList2D(createList2D(D * 2 + 1, D * 2 + 1, -1), D, D, 0); // -1: unreachable, >=0, distance
	P canReachLambda2;
	P canReachGhost = createList2D(D * 2 + 1, D * 2 + 1, -1); // -1: unreachable, 0-3: one direction, 4: any directions
	P canReachGhost2;
	while (atom(ghosts) == 0) {
		ghost = fst(ghosts);
		ghosts = snd(ghosts);
		tmp = fst(snd(ghost));
		i = toi(fst(tmp)) - x + D;
		j = toi(snd(tmp)) - y + D;
		k = toi(snd(snd(ghost)));
		if (0 <= i) {
			if (i <= 2 * D) {
				if (0 <= j) {
					if (j <= 2 * D) {
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
		canReachGhost2 = createList2D(2 * D + 1, 2 * D + 1, -1);
		i = 0;
		while (i <= 2 * D) {
			j = 0;
			while (j <= 2 * D) {
				k = toi(getList2D(canReachGhost, j, i));
				if (k >= 0) {
					d = 0;
					while (d < 4) {
						if (mymod(d + 2, 4) == k) {
						} else {
							i2 = i + dx(d);
							j2 = j + dy(d);
							if (0 <= i2) {
								if (i2 <= 2 * D) {
									if (0 <= j2) {
										if (j2 <= 2 * D) {
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
		canReachLambda2 = createList2D(2 * D + 1, 2 * D + 1, -1);
		live = 0;
		while (i <= 2 * D) {
			j = 0;
			while (j <= 2 * D) {
				k = toi(getList2D(canReachLambda, j, i));
				if (k >= 0) {
					if (toi(getList2D(canReachGhost, j, i)) < 0) {
						d2 = toi(getList2D(canReachLambda2, j, i));
						if ((d2 < 0) + (d2 > k)) {
							if (d2 < 0) {
								live += 1;
							}
							canReachLambda2 = setList2D(canReachLambda2, j, i, k);
						}
						if ((t > 0) + near) {
							d = 0;
							while (d < 4) {
								i2 = i + dx(d);
								j2 = j + dy(d);
								if (0 <= i2) {
									if (i2 <= 2 * D) {
										if (0 <= j2) {
											if (j2 <= 2 * D) {
												if (toi(getList2D(canReachGhost, j2, i2)) < 0) {
													c = toi(getList2D(subBoard, j2, i2));
													if (c > 0) {
														if (c == 3) {
															takePowerPill = 1;
															if (nearestPowerPill > k + 1) {
																nearestPowerPill = k + 1;
															}
														}
														d2 = toi(getList2D(canReachLambda2, j2, i2));
														if ((d2 < 0) + (d2 > k + 1)) {
															if (d2 < 0) {
																live += 1;
															}
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
		if (live == 0) {
			if (death == 0) {
				death = t + 1;
			}
		}
		canReachLambda = canReachLambda2;
		t += 1;
	}
	newSpace = 0;
	i = 0;
	while (i <= 2 * D) {
		j = 0;
		while (j <= 2 * D) {
			if ((i == D) * (j == D)) {
			} else {
				d = toi(getList2D(canReachLambda, j, i));
				if (d >= 0) {
					numSpace += 1;
					if (d == D - 1 + near) {
						newSpace += 1;
					}
					k = toi(getList2D(subBoard, j, i));
					if (k == 2) {
						ret += 1000 / (d + 1);
					} else {
						if (k == 3) {
						} else {
							if (k == 4) {
								if (fruitStatus > 0) {
									ret += fruitBonus * 100 / (d + 1);
								}
							}
						}
					}
					d2 = INF;
					tmp = topKPowerPills;
					while (atom(tmp) == 0) {
						p = snd(fst(tmp));
						tmp = snd(tmp);
						d2 = mymin(d2, myabs(i - D + x - toi(fst(p))) + myabs(j - D + y - toi(snd(p))));
					}
					score2 += 10000 / (d2 + 1) / (d + 1);
				}
			}
			j += 1;
		}
		i += 1;
	}
	if (nearestPowerPill < INF) {
		if ((lastPointUp > 50) + near) {
			ret += 200000 / (nearestPowerPill + 1);
		} else {
			ret += 20000;// / (nearestPowerPill + 1);
		}
	} else {
		ret += score2 / (D * D);
	}
	if (death > 0) {
		if (takePowerPill == 0) {
			ret -= 1000000000 / death;
		}
	} else {
		if (newSpace == 0) {
			if (takePowerPill == 0) {
				ret -= 1000000000 / (D * 2);
			}
		}
	}
	return ret;
}

// dist+1
P bfs32(int x, int y, int D) {
	P subBoard = list2d_to_array2d32(getSubList2D(board2DList, y - D, y + D + 1, x - D, x + D + 1));
	P dist = create_array2d32();
	P que = create_queue();
	P p;
	int d, dir, x2, y2;
	que = push_queue(que, P(P(D, D), 1));
	dist = set_array2d32(dist, D, D, 1);
	while (is_empty_queue(que) == 0) {
		p = front_queue(que);
		que = pop_queue(que);
		d = toi(snd(p));
		x = toi(fst(fst(p)));
		y = toi(snd(fst(p)));
		if (d <= D) {
			dir = 0;
			while (dir < 4) {
				x2 = x + dx(dir);
				y2 = y + dy(dir);
				if (toi(get_array2d32(subBoard, y2, x2)) > 0) {
					if (toi(get_array2d32(dist, y2, x2)) == 0) {
						dist = set_array2d32(dist, y2, x2, d + 1);
						que = push_queue(que, P(P(x2, y2), d + 1));
					}
				}
				dir += 1;
			}
		}
	}
	return dist;
}

int evalAttack(int x, int y, int time) {
	int ret = 0, i, d, D = 10;
	P ghost;
	P p;
	P dist = bfs32(x, y, D);
	int x2, y2;
	i = 0;
	while (i < ghostN) {
		ghost = getList(ghostStatus, i);
		if (toi(fst(ghost)) < 2) {
			p = fst(snd(ghost));
			x2 = toi(fst(p)) - x + D;
			y2 = toi(snd(p)) - y + D;
			if (0 <= x2) {
				if (y2 <= 2 * D) {
					if (0 <= y2) {
						if (y2 <= 2 * D) {
							d = toi(get_array2d32(dist, y2, x2)) - 1;
							if (d >= 0) {
								if (time / 127 >= time / 204 + d) {
									ret += 160000 / (d + 1);
								}
							}
						}
					}
				}
			}
		}
		i += 1;
	}
	return ret;
}

int eval(int x, int y) {
	int c = toi(getList2D(board2DList, y, x));
	int ret = 0;
	int i, d;
	P ghost, tmp;
	int near = 0;
	int attack = 0;
	if (manVitality > 0) {
		ret = evalAttack(x, y, manVitality);
		if (ret > 0) {
			attack = 1;
		}
	} else {
		if (c == 3) {
			ret = evalAttack(x, y, 127 * 20);
			if ((ret > 0) + (lastPointUp > 50) + near) {
				attack = 1;
				if (lastPointUp <= 50) {
					ret -= 20000;
				} else {
					ret += 200000;
				}
				ret += 5000;
			}
		}
	}
	if (attack == 0) {
		i = 0;
		while (i < ghostN) {
			ghost = getList(ghostStatus, i);
			if (toi(fst(ghost)) < 2) {
				tmp = fst(snd(ghost));
				d = myabs(toi(fst(tmp)) - manX) + myabs(toi(snd(tmp)) - manY);
				if (d <= 1) {
					if (near < 2) {
						near = 1;
					}
				}
				if ((toi(fst(tmp)) == x) * (toi(snd(tmp)) == y)) {
					near = 2;
				}
			}
			i += 1;
		}
		ret = 0; // myrand(10);
		if (c == 2) {
			ret += 1000;
		} else {
			if (c == 3) {
				ret -= 20000;
			} else {
				if (c == 4) {
					if (fruitStatus > 0) {
						ret += fruitBonus * 100;
					}
				}
			}
		}
		if (near == 2) {
			ret -= INF;
		} else {
			ret += evalAround(x, y, near);
		}
	}
	return ret;
}

P step_(P ai, P game) {
	P manStatus;
	int ret, dir, maxScore, score, x, y, c;
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
	ret = 0;
	maxScore = -INF;
	c = toi(get_array2d256(board2DArray, manY, manX));
	if ((c == 2) + (c == 3)) {
		board2DArray = set_array2d256(board2DArray, manY, manX, 1);
	}
	dir = 0;
	topKPowerPills = getTopKPowerPills(manX, manY, 4);
	debug(fruitStatus);
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
	x = manX + dx(ret);
	y = manY + dy(ret);
	c = toi(getList2D(board2DList, y, x));
	if (c == 2) {
		lastPointUp = 0;
	} else {
		if (c == 3) {
			lastPointUp = 0;
		} else {
			lastPointUp += 1;
		}
	}
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
	fruitBonus = getFruitBonus();
	lastPointUp = 0;
	board2DArray = list2d_to_array2d256(board2DList);
	powerPills = getPowerPills();
	return top(0);
}
