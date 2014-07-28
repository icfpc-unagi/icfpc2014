#include "translator/lib.h"
//#include "sbl/tree.cpp"
#include "sbl/queue.cpp"
#include "sbl/array256.h"

P gmap;
P distghosttree;
P distlmantree;
P jisutree;

int randx;
int turn;
int fruitbonus;

int h;
int w;

int ly;
int lx;
int addnum;

int randomv;

P boardtree;
P allmaxtree;

int MAXNUM;

P q1;
P gghosts;

int nowata;

int i;
int j;
int inicount;


int defvitality;
int vitality;
int lambdadirection;
int lambdalive;
int lambdascore;

int dfsdepth;

int nearghostlength;




int mod(int a, int b){
	int c;
	c = a / b;
	return a - b * c;
}

int mymax(int a, int b){
	int ret;
	if(a > b){
		ret = a;
	}
	else{
		ret = b;
	}
	return ret;
}

int myrand(){
	randx = mod(randx * 163 + 43751, 1000033);
	return randx;
}




int INF;

P board2DList_wata;
int sizeX_wata;
int sizeY_wata;
int manVitality_wata;
int manX_wata;
int manY_wata;
int manDir_wata;
int manLives_wata;
int currentScore_wata;
P ghostStatus_wata;
int ghostN_wata;
int fruitStatus_wata;

P dist2D; // distance from pills

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


int myrand_wata(int m) {
	randx = mymod(randx * 163 + 43751, 1000033);
	return mymod(randx, m);
}

P swap(P p) {
	return P(snd(p), fst(p));
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

P initDist(P list) {
	int v;
	if (atom(list)) {
	} else {
		v = toi(fst(list));
		if (v == 0) {
			v = -1;
		} else {
			if ((v == 2) + (v == 3)) {
				v = 0;
			} else {
				v = INF;
			}
		}
		list = P(v, initDist(snd(list)));
	}
	return list;
}

P initDist2D(P list2D) {
	if (atom(list2D)) {
	} else {
		list2D = P(initDist(fst(list2D)), initDist2D(snd(list2D)));
	}
	return list2D;
}

P updateDist2D_(P newDist2D, P dist2D) {
	P fromUp = createList(sizeX_wata, INF);
	P retNewDist2D = top(0);
	P retDist2D = top(0);
	int fromLeft, d;
	P newDist, dist, retNewDist, retDist, fromUp_;
	while (atom(dist2D) == 0) {
		newDist = fst(newDist2D);
		newDist2D = snd(newDist2D);
		dist = fst(dist2D);
		dist2D = snd(dist2D);
		fromLeft = INF;
		retNewDist = top(0);
		retDist = top(0);
		fromUp_ = top(0);
		while (atom(dist) == 0) {
			d = mymin(mymin(toi(fst(newDist)), toi(fst(fromUp)) + 1), fromLeft + 1);
			retNewDist = P(d, retNewDist);
			d = mymin(d, toi(fst(dist)));
			if (d < 0) {
				d = INF;
			}
			fromLeft = d;
			fromUp_ = P(d, fromUp_);
			fromUp = snd(fromUp);
			retDist = P(fst(dist), retDist);
			dist = snd(dist);
			newDist = snd(newDist);
		}
		fromUp = reverseList(fromUp_);
		retNewDist2D = P(retNewDist, retNewDist2D);
		retDist2D = P(retDist, retDist2D);
	}
	return P(retNewDist2D, retDist2D);
}

P updateDist2D(P dist2D) {
	P tmp = updateDist2D_(initDist2D(board2DList_wata), dist2D);
	return fst(updateDist2D_(fst(tmp), snd(tmp)));
}

int eval(int x, int y) {
	int c = toi(getList2D(board2DList_wata, y, x));
	int ret = -1000000000;
	int i, d;
	P tmp;
	if (c > 0) {
		ret = 0;//myrand(100);
		if ((c == 2) + (c == 3)) {
			ret += 1000;
		} else {
			ret += 1000 - toi(getList2D(dist2D, y, x));
		}
		i = 0;
		while (i < ghostN_wata) {
			tmp = fst(snd(getList(ghostStatus_wata, i)));
			d = myabs(toi(fst(tmp)) - x) + myabs(toi(snd(tmp)) - y);
			if (d == 0) {
				if (manVitality_wata > 0) {
					ret += 80000;
				} else {
					ret -= 10000000;
				}
			} else {
				if (d <= 1) {
					if (manVitality_wata > 0) {
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

	if(nowata==0){
	board2DList_wata = fst(game);
	manStatus = fst(snd(game));
	ghostStatus_wata = fst(snd(snd(game)));
	ghostN_wata = lengthList(ghostStatus_wata);
	fruitStatus_wata = toi(snd(snd(snd(game))));
	manVitality_wata = toi(fst(manStatus));
	manX_wata = toi(fst(fst(snd(manStatus))));
	manY_wata = toi(snd(fst(snd(manStatus))));
	manDir_wata = toi(fst(snd(snd(manStatus))));
	manLives_wata = toi(fst(snd(snd(snd(manStatus)))));
	currentScore_wata = toi(snd(snd(snd(snd(manStatus)))));
	dist2D = updateDist2D(dist2D);
	ret = -1;
	maxScore = -INF;
	dir = 0;
	while (dir < 4) {
		x = manX_wata + dx(dir);
		y = manY_wata + dy(dir);
		if (toi(getList2D(board2DList_wata, y, x)) == 0) {
			x = manX_wata;
			y = manY_wata;
		}
		score = eval(x, y);
		if (maxScore < score) {
			maxScore = score;
			ret = dir;
		}
		dir += 1;
	}
//	debugList2D(dist2D);
	}
	else{
		ret = 0;
	}
	return P(ai, ret);
}




int getNumber(int y, int x){
	return toi(get_array2d256(boardtree, y, x));
}


int getPoint2(int ret){
	if(ret == 0){
		ret = -1;
	}
	else{
		if(ret == 1){
			ret = 0;
		}
		else{
			if(ret == 2){
				ret = 1;
			}
			else{
				if(ret == 3){
					ret = 10;
				}
				else{
					if(ret == 4){
						ret = fruitbonus;
					}
					else{
						ret = 0;
					}
				}
			}
		}
	}
	return ret;
}

int getPoint(int y, int x){
	int ret;
	ret = getNumber(y, x);
	return getPoint2(ret);
}


int powdiv(int a){
	int ret;
	ret = 1;
	while(a > 3){
		ret = ret * 2;
		a = a - 3;
	}
	while(a > 1){
		ret = ret * 5;
		ret = ret / 4;
		a = a - 1;
	}
	return ret;
}


int pow(int a, int b){
	int ret;

	if(a == 0){
		ret = 1;
	}
	else{
		ret = b * pow(a - 1, b);
	}
	return ret;
}

int pow2(int a){
	int ret;
	ret = 1;
	while(a > 10){
		ret = 1 + ret;
		a = a - 1;
	}
	while(a > 0){
		ret = 2 * ret;
		a = a - 1;
	}
	return ret;
}


int checkdfs(int y, int x, int depth, int predirection, int count){
	int ret = 0;
	if(getNumber(y, x) > 0){
		if(toi(get_array2d256(distghosttree, y, x)) > addnum){
			ret = 1;
		}
		else{
			if(vitality > 0){
				ret = 1;
			}
		}
	}
	return ret;
}


int sign(int a){
	int ret;
	if(a < 0){
		ret = 0 - 1;
	}
	else{
		if(a > 0){
			ret = 1;
		}
		else{
			ret = 0;
		}
	}
	return ret;
}

int over0(int a){
	int ret;
	if(a > 0 - 1){
		ret = 1;
	}
	else{
		ret = 0 - 1;
	}
	return ret;
}


int uppoint;
int rightpoint;
int downpoint;
int leftpoint;

void ghostbfs(){
	P ghosts;
	
	P tempghost;
	int ghostvitality;
	P ghostlocation;
	int ghosty;
	int ghostx;
	int ghostdirection;

	int countqueue;
	int ghostdist;

	int x;
	int y;
	int d;
	int cost;

	P now;

	ghosts = gghosts;

	q1 = create_queue();

	while(1 - atom(ghosts)){
		tempghost = fst(ghosts);
		ghosts = snd(ghosts);
		ghostvitality = toi(fst(tempghost));
		tempghost = snd(tempghost);
		ghostlocation = fst(tempghost);
		ghostx = toi(fst(ghostlocation));
		ghosty = toi(snd(ghostlocation));
		ghostdirection = toi(snd(tempghost));

		ghostdist = myabs(lx- ghostx) + myabs(ly-ghosty);
		if(ghostvitality < 2){
			if(ghostdist < 30){
				q1 = push_queue(q1, P(P(ghostx, ghosty), P(ghostdirection, 0)));
			}
			distghosttree = set_array2d256(distghosttree, ghosty, ghostx, 0);
		}
		else{
			if(ghostdist < 30){
				q1 = push_queue(q1, P(P(ghostx, ghosty), P(ghostdirection, 0)));
			}

		}
		
	}

	countqueue = 0;

	while(1 - is_empty_queue(q1)){
		countqueue = countqueue + 1;
		now = front_queue(q1);
		q1 = pop_queue(q1);
		x = toi(fst(fst(now)));
		y = toi(snd(fst(now)));
		d = toi(fst(snd(now)));
		cost = toi(snd(snd(now)));

		
		//debug(1000000 * cost + 1000 * x + y);

		if(d == 2){}
		else{
			if(getNumber(y-1, x)== 0){}
			else{
				//debug(5000000 + toi(get_array2d256(distghosttree, y-1, x)));
				if(toi(get_array2d256(distghosttree, y-1, x)) == MAXNUM){
					distghosttree = set_array2d256(distghosttree, y-1, x, cost+1);
					q1 = push_queue(q1, P(P(x, y-1), P(0, cost+1)));
				}
			}
		}

		if(d == 3){}
		else{
			if(getNumber(y, x+1)== 0){}
			else{
				if(toi(get_array2d256(distghosttree, y, x+1)) == MAXNUM){
					distghosttree = set_array2d256(distghosttree, y, x+1, cost+1);
					q1 = push_queue(q1, P(P(x+1, y), P(1, cost+1)));
				}
			}
		}

		if(d == 0){}
		else{
			if(getNumber(y+1, x)== 0){}
			else{
				if(toi(get_array2d256(distghosttree, y+1, x)) == MAXNUM){
					distghosttree = set_array2d256(distghosttree, y+1, x, cost+1);
					q1 = push_queue(q1, P(P(x, y+1), P(2, cost+1)));
				}
			}
		}

		if(d == 1){}
		else{
			if(getNumber(y, x-1) == 0){}
			else{
				if(toi(get_array2d256(distghosttree, y, x-1)) == MAXNUM){
					distghosttree = set_array2d256(distghosttree, y, x-1, cost+1);
					q1 = push_queue(q1, P(P(x-1, y), P(3, cost+1)));
				}
			}
		}

		if(countqueue > 300){
			q1 = create_queue();
		}
		if(cost > 10){
			q1 = create_queue();
		}
	}
	//debug(777);
	//debug(countqueue);
}


P nowp;

void bfs(){
	int y;
	int x;
	int d;
	int cost;
	int id;
	int countqueue;
	int num;
	int point;
	int mypoint;
	int gdist;
	
	//push_queue(q1, P(P(lx,ly),P(lambdadirection, P(1, 0))));
	//push_queue(q1, P(P(lx,ly),P(lambdadirection, P(1, 1))));
	//push_queue(q1, P(P(lx,ly),P(lambdadirection, P(1, 2))));
	//push_queue(q1, P(P(lx,ly),P(lambdadirection, P(1, 3))));

	while(1 - is_empty_queue(q1)){
		countqueue = countqueue + 1;
		nowp = front_queue(q1);
		q1 = pop_queue(q1);
		x = toi(fst(fst(nowp)));
		y = toi(snd(fst(nowp)));
		d = toi(fst(snd(nowp)));
		cost = toi(fst(snd(snd(nowp))));
		id =  toi(snd(snd(snd(nowp))));
		mypoint = toi(get_array2d256(distlmantree, y, x)) + 1000000;

		//debug(x);
		//debug(y);
		//debug(mypoint);

		if(cost > dfsdepth)
		{
			mypoint = mypoint + 1000000000;
			if(id==0){
				uppoint = mymax(mypoint, uppoint);
			}
			if(id==1){
				rightpoint = mymax(mypoint, rightpoint);
			}
			if(id==2){
				downpoint = mymax(mypoint, downpoint);
			}
			if(id==3){
				leftpoint = mymax(mypoint, leftpoint);
			}
		}
		else
		{
			//debug(1000000 * id + 1000 * x + y);

			//debug(toi(get_array2d256(distlmantree, y, x)) * 1000 + toi(get_array2d256(distghosttree, y, x)));
			//if(cost < vitality + 1){
			if(cost < vitality * 5 / 3){
				if(d == 2){}
				else{
					num = getNumber(y-1, x);
					point = mypoint + getPoint2(num) * pow2(dfsdepth - cost);
					if(num==3){
						point = point + 300000000;
						if(id==0){
							uppoint = mymax(uppoint, point);
						}
						if(id==1){
							rightpoint = mymax(rightpoint, point);
						}
						if(id==2){
							downpoint = mymax(downpoint, point);
						}
						if(id==3){
							leftpoint = mymax(leftpoint, point);
						}
					}
					else{

						if(num == 0){}
						else{
							if(toi(get_array2d256(distlmantree, y-1, x)) == MAXNUM){
								if(toi(get_array2d256(distghosttree, y-1, x)) == 0){
									point = point + 50001 * pow2(dfsdepth - cost);
								}

								distlmantree = set_array2d256(distlmantree, y-1, x, point);
								q1 = push_queue(q1, P(P(x, y - 1), P(0, P(cost+1, id))));

								if(id==0){
									uppoint = mymax(uppoint, point);
								}
								if(id==1){
									rightpoint = mymax(rightpoint, point);
								}
								if(id==2){
									downpoint = mymax(downpoint, point);
								}
								if(id==3){
									leftpoint = mymax(leftpoint, point);
								}
							}
						}
					}
				}

				if(d == 3){}
				else{
					num = getNumber(y, x + 1);
					point = mypoint + getPoint2(num) * pow2(dfsdepth - cost);
					if(num==3){
						point = point + 300000000;
						if(id==0){
							uppoint = mymax(uppoint, point);
						}
						if(id==1){
							rightpoint = mymax(rightpoint, point);
						}
						if(id==2){
							downpoint = mymax(downpoint, point);
						}
						if(id==3){
							leftpoint = mymax(leftpoint, point);
						}
					}
					else{
						if(num == 0){}
						else{
							if(toi(get_array2d256(distlmantree, y, x+1)) == MAXNUM){
								if(toi(get_array2d256(distghosttree, y, x + 1)) == 0){
									point = point + 50001 * pow2(dfsdepth - cost);
								}
								distlmantree = set_array2d256(distlmantree, y, x+1, point);
								q1 = push_queue(q1, P(P(x+1, y),  P(1, P(cost+1, id))));

								if(id==0){
									uppoint = mymax(uppoint, point);
								}
								if(id==1){
									rightpoint = mymax(rightpoint, point);
								}
								if(id==2){
									downpoint = mymax(downpoint, point);
								}
								if(id==3){
									leftpoint = mymax(leftpoint, point);
								}
							}
						}
					}
				}

				if(d == 0){}
				else{
					num = getNumber(y+1, x);
					point = mypoint + getPoint2(num) * pow2(dfsdepth - cost);
					if(num==3){
						point = point + 300000000;
						if(id==0){
									uppoint = mymax(uppoint, point);
								}
								if(id==1){
									rightpoint = mymax(rightpoint, point);
								}
								if(id==2){
									downpoint = mymax(downpoint, point);
								}
								if(id==3){
									leftpoint = mymax(leftpoint, point);
								}
					}
					else{
						if(num == 0){}
						else{
							if(toi(get_array2d256(distlmantree, y+1, x)) == MAXNUM){
								if(toi(get_array2d256(distghosttree, y+1, x)) == 0){
									point = point + 50001 * pow2(dfsdepth - cost);
								}

								distlmantree = set_array2d256(distlmantree, y+1, x, point);
								q1 = push_queue(q1, P(P(x, y+1),  P(2, P(cost+1, id))));

								if(id==0){
									uppoint = mymax(uppoint, point);
								}
								if(id==1){
									rightpoint = mymax(rightpoint, point);
								}
								if(id==2){
									downpoint = mymax(downpoint, point);
								}
								if(id==3){
									leftpoint = mymax(leftpoint, point);
								}
							}
						}
					}
				}

				if(d == 1){}
				else{
					num = getNumber(y, x - 1);
					point = mypoint + getPoint2(num) * pow2(dfsdepth - cost);
					if(num==3){
						point = point + 300000000;
						if(id==0){
									uppoint = mymax(uppoint, point);
								}
								if(id==1){
									rightpoint = mymax(rightpoint, point);
								}
								if(id==2){
									downpoint = mymax(downpoint, point);
								}
								if(id==3){
									leftpoint = mymax(leftpoint, point);
								}
					}
					else{
						if(num == 0){}
						else{
							if(toi(get_array2d256(distlmantree, y, x-1)) == MAXNUM){
								if(toi(get_array2d256(distghosttree, y, x - 1)) == 0){
									point = point + 50001 * pow2(dfsdepth - cost);
								}
								distlmantree = set_array2d256(distlmantree, y, x-1, point);
								q1 = push_queue(q1, P(P(x-1, y),  P(3, P(cost+1, id))));

								if(id==0){
									uppoint = mymax(uppoint, point);
								}
								if(id==1){
									rightpoint = mymax(rightpoint, point);
								}
								if(id==2){
									downpoint = mymax(downpoint, point);
								}
								if(id==3){
									leftpoint = mymax(leftpoint, point);
								}
							}
						}
					}
				}
			}
			else{

				if(d == 2){}
				else{
					num = getNumber(y-1, x);
					point = mypoint + getPoint2(num) * pow2(dfsdepth - cost);
					if(num==3){
						gdist = toi(get_array2d256(distghosttree, y-1,x)) - cost - addnum;
						if(gdist > 0){
							if(gdist < nearghostlength){
								point = point + 1300000000 - 2000000 * cost;
							}
						}
						else{
							point = point + 300000000;
						}

						if(id==0){
							uppoint = mymax(uppoint, point);
						}
						if(id==1){
							rightpoint = mymax(rightpoint, point);
						}
						if(id==2){
							downpoint = mymax(downpoint, point);
						}
						if(id==3){
							leftpoint = mymax(leftpoint, point);
						}
					}
					else{
						if(num == 0){}
						else{
							if(toi(get_array2d256(distlmantree, y-1, x)) == MAXNUM){
								if(toi(get_array2d256(distghosttree, y-1, x)) > cost + addnum){
									distlmantree = set_array2d256(distlmantree, y-1, x, point);
									q1 = push_queue(q1, P(P(x, y - 1), P(0, P(cost+1, id))));

									if(id==0){
										uppoint = mymax(uppoint, point);
									}
									if(id==1){
										rightpoint = mymax(rightpoint, point);
									}
									if(id==2){
										downpoint = mymax(downpoint, point);
									}
									if(id==3){
										leftpoint = mymax(leftpoint, point);
									}
								}
							}
						}
					}
				}

				if(d == 3){}
				else{
					num = getNumber(y, x + 1);
					point = mypoint + getPoint2(num) * pow2(dfsdepth - cost);
					if(num==3){
						gdist = toi(get_array2d256(distghosttree, y,x + 1)) - cost - addnum;
						if(gdist > 0){
							if(gdist < nearghostlength){
								point = point + 1300000000 - 2000000 * cost;
							}
						}
						else{
							point = point + 300000000;
						}
						if(id==0){
									uppoint = mymax(uppoint, point);
								}
								if(id==1){
									rightpoint = mymax(rightpoint, point);
								}
								if(id==2){
									downpoint = mymax(downpoint, point);
								}
								if(id==3){
									leftpoint = mymax(leftpoint, point);
								}
					}
					else{
						if(num == 0){}
						else{
							if(toi(get_array2d256(distlmantree, y, x+1)) == MAXNUM){
								if(toi(get_array2d256(distghosttree, y, x + 1)) > cost + addnum){ 
									distlmantree = set_array2d256(distlmantree, y, x+1, point);
									q1 = push_queue(q1, P(P(x+1, y),  P(1, P(cost+1, id))));

									if(id==0){
										uppoint = mymax(uppoint, point);
									}
									if(id==1){
										rightpoint = mymax(rightpoint, point);
									}
									if(id==2){
										downpoint = mymax(downpoint, point);
									}
									if(id==3){
										leftpoint = mymax(leftpoint, point);
									}
								}
							}
						}
					}
				}

				if(d == 0){}
				else{
					num = getNumber(y+1, x);
					point = mypoint + getPoint2(num) * pow2(dfsdepth - cost);
					if(num==3){
						gdist = toi(get_array2d256(distghosttree, y+1,x)) - cost - addnum;
						if(gdist > 0){
							if(gdist < nearghostlength){
								point = point + 1300000000 - 2000000 * cost;
							}
						}
						else{
							point = point + 300000000;
						}
						
						if(id==0){
									uppoint = mymax(uppoint, point);
								}
								if(id==1){
									rightpoint = mymax(rightpoint, point);
								}
								if(id==2){
									downpoint = mymax(downpoint, point);
								}
								if(id==3){
									leftpoint = mymax(leftpoint, point);
								}
					}
					else{
						if(num == 0){}
						else{
							if(toi(get_array2d256(distlmantree, y+1, x)) == MAXNUM){
								if(toi(get_array2d256(distghosttree, y+1, x)) > cost + addnum){ 
									distlmantree = set_array2d256(distlmantree, y+1, x, point);
									q1 = push_queue(q1, P(P(x, y+1),  P(2, P(cost+1, id))));

									if(id==0){
										uppoint = mymax(uppoint, point);
									}
									if(id==1){
										rightpoint = mymax(rightpoint, point);
									}
									if(id==2){
										downpoint = mymax(downpoint, point);
									}
									if(id==3){
										leftpoint = mymax(leftpoint, point);
									}
								}
							}
						}
					}
				}

				if(d == 1){}
				else{
					num = getNumber(y, x - 1);
					point = mypoint + getPoint2(num) * pow2(dfsdepth - cost);

					if(num==3){
						gdist = toi(get_array2d256(distghosttree, y,x-1)) - cost - addnum;
						if(gdist > 0){
							if(gdist < nearghostlength){
								point = point + 1300000000 - 2000000 * cost;
							}
						}
						else{
							point = point + 300000000;
						}
						if(id==0){
									uppoint = mymax(uppoint, point);
								}
								if(id==1){
									rightpoint = mymax(rightpoint, point);
								}
								if(id==2){
									downpoint = mymax(downpoint, point);
								}
								if(id==3){
									leftpoint = mymax(leftpoint, point);
								}
					}
					else{
						if(num == 0){}
						else{
							if(toi(get_array2d256(distlmantree, y, x-1)) == MAXNUM){
								if(toi(get_array2d256(distghosttree, y, x - 1)) > cost + addnum){ 
									distlmantree = set_array2d256(distlmantree, y, x-1, point);
									q1 = push_queue(q1, P(P(x-1, y),  P(3, P(cost+1, id))));

									if(id==0){
										uppoint = mymax(uppoint, point);
									}
									if(id==1){
										rightpoint = mymax(rightpoint, point);
									}
									if(id==2){
										downpoint = mymax(downpoint, point);
									}
									if(id==3){
										leftpoint = mymax(leftpoint, point);
									}
								}
							}
						}
					}
				}
			}
		}


	}
	//debug(888);
	//debug(countqueue);

}


int bfsgnum;

void bfs2(){
	int point;
	q1 = create_queue();

	bfsgnum = getNumber(ly-1,lx);
	if(bfsgnum == 0){ uppoint -= 20000000; }
	else{
		if(checkdfs(ly-1,lx,10,0,1)){
			if(bfsgnum==3){
				if(toi(get_array2d256(distghosttree, ly-1, lx)) - 1 < nearghostlength){
					if(vitality < 1){
						uppoint = mymax(uppoint, 1300000000);
					}
					else{
						uppoint = mymax(uppoint, 300000000);
					}
				}
				else{
					uppoint = mymax(uppoint, 300000000);
				}
			}
			else{
				distlmantree = allmaxtree;
				point = getPoint(ly-1, lx) * pow2(dfsdepth);
				if(toi(get_array2d256(distghosttree, ly-1, lx)) == 0){
					point = point + pow2(dfsdepth) * 50001;
				}
				distlmantree = set_array2d256(distlmantree, ly-1, lx, point);
				q1 = push_queue(q1, P(P(lx,ly-1), P(0, P(1, 0))));
				uppoint = mymax(uppoint, point);
				bfs();
			}
		}
		else{
			uppoint -= 20000000;
		}
	}

	
	bfsgnum = getNumber(ly,lx+1);
	if(bfsgnum == 0){ rightpoint -= 20000000; }
	else{
		if(checkdfs(ly,lx + 1,10,0,1)){
			if(bfsgnum==3){
				if(toi(get_array2d256(distghosttree, ly, lx + 1)) - 1 < nearghostlength){
					if(vitality < 1){
						rightpoint = mymax(rightpoint, 1300000000);
					}
					else{
						rightpoint = mymax(rightpoint, 300000000);
					}
				}
				else{
					rightpoint = mymax(rightpoint, 300000000);
				}
			}
			else{
				distlmantree = allmaxtree;
				point = getPoint(ly, lx+1) * pow2(dfsdepth);
				if(toi(get_array2d256(distghosttree, ly, lx + 1)) == 0){
					point = point + pow2(dfsdepth) * 50001;
				}
				distlmantree = set_array2d256(distlmantree, ly, lx+1, point);
				q1 = push_queue(q1, P(P(lx+1,ly), P(1, P(1, 1))));
				rightpoint = mymax(rightpoint, point);
				bfs();
			}
		}
		else{
			rightpoint -= 20000000;
		}
	}

	
	bfsgnum = getNumber(ly+1,lx);
	if(bfsgnum == 0){ downpoint -= 20000000; }
	else{
		if(checkdfs(ly+1,lx,10,0,1)){
			if(bfsgnum==3){
				if(toi(get_array2d256(distghosttree, ly+1, lx)) - 1 < nearghostlength){
					if(vitality < 1){
						downpoint = mymax(downpoint, 1300000000);
					}
					else{
						downpoint = mymax(downpoint, 300000000);
					}
				}
				else{
					downpoint = mymax(downpoint, 300000000);
				}
			}
			else{
				distlmantree = allmaxtree;
				point = getPoint(ly+1, lx) * pow2(dfsdepth);
				if(toi(get_array2d256(distghosttree, ly+1, lx)) == 0){
					point = point + pow2(dfsdepth) * 50001;
				}
				distlmantree = set_array2d256(distlmantree, ly+1, lx, point);
				q1 = push_queue(q1, P(P(lx,ly+1), P(2, P(1, 2))));
				downpoint = mymax(downpoint, point);
				bfs();
			}
		}
		else{
			downpoint -= 20000000;
		}
	}

	
	bfsgnum = getNumber(ly,lx-1);
	if(bfsgnum == 0){ leftpoint -= 20000000; }
	else{
		if(checkdfs(ly,lx-1,10,0,1)){
			if(bfsgnum==3){
				if(toi(get_array2d256(distghosttree, ly, lx - 1)) - 1 < nearghostlength){
					if(vitality < 1){
						leftpoint = mymax(leftpoint, 1300000000);
					}
					else{
						leftpoint = mymax(leftpoint, 300000000);
					}
				}
				else{
					leftpoint = mymax(leftpoint, 300000000);
				}
			}
			else{
				distlmantree = allmaxtree;
				point = getPoint(ly, lx-1) * pow2(dfsdepth);
				if(toi(get_array2d256(distghosttree, ly, lx - 1)) == 0){
					point = point + pow2(dfsdepth) * 50001;
				}
				distlmantree = set_array2d256(distlmantree, ly, lx-1, point);
				q1 = push_queue(q1, P(P(lx-1,ly), P(3, P(1, 3))));
				leftpoint = mymax(leftpoint, point);
				bfs();
			}
		}
		else{
			leftpoint -= 20000000;
		}
	}

}

int countnotpoint;

// step
P step2(P ai, P game) {
	P map;

	P game2;

	P lambdaman;
	P lambdaman2;
	P lambdalocation;
	int lambdax;
	int lambday;
	P lambdaman3;
	P lambdaman4;

	P game3;
	P ghosts;


	P fruits;




	int maxpoint;

	int retdirection;


	int fruittime;

	int nowpos;

	P farpoint;

	P wata_result = step_(ai,game);
	P ret;

	distghosttree = allmaxtree;
	distlmantree = allmaxtree;

	uppoint = 0;
	rightpoint = 0;
	downpoint = 0;
	leftpoint = 0;

	maxpoint = 0 - 199999999;
	retdirection = 0;

	map = fst(game);
	gmap = map;

	game2 = snd(game);
	lambdaman = fst(game2);
	game3 = snd(game2);
	ghosts = fst(game3);
	gghosts = ghosts;
	fruits = snd(game3);

	fruitbonus = 0;

	fruittime = toi(fruits);
	if(fruittime > 0){
		fruitbonus = 200;
	}
	else{}
	
	//debug(fruittime);

	defvitality = toi(fst(lambdaman));
	vitality = defvitality / 137 - 1;
	lambdaman2 = snd(lambdaman);
	lambdalocation = fst(lambdaman2);
	lambdax = toi(fst(lambdalocation));
	lambday = toi(snd(lambdalocation));
	lambdaman3 = snd(lambdaman2);
	lambdadirection = toi(fst(lambdaman3));
	lambdaman4 = snd(lambdaman3);
	lambdalive = toi(fst(lambdaman4));
	lambdascore = toi(snd(lambdaman4));


	lx = lambdax;
	ly = lambday;

	nowpos = toi(get_array2d256(boardtree, lambday, lambdax));
	if(nowpos == 2){
		countnotpoint = 0;
		boardtree = set_array2d256(boardtree, lambday, lambdax, 1);
	}
	if(nowpos == 3){
		countnotpoint = 0;
		boardtree = set_array2d256(boardtree, lambday, lambdax, 1);
	}
	countnotpoint += 1;

	turn = turn + 1;
	if((turn > h * w * 9) * (1 - nowata)){
		ret = wata_result;
		//dfsdepth = 20;
	}
	else{
		if((countnotpoint > 100) * (1 - nowata)){
			debug(9999999);
			ret = wata_result;
		}
		else{

	//debug(1245);

	ghostbfs();


	//for(int i=0;i<h;i++){
	//	for(int j=0;j<w;j++){
	//		if(getNumber(i,j)==0) printf("#");
	//		else{
	//			int costnum = toi(get_array2d256(distghosttree, i,j));
	//			if(costnum==MAXNUM) printf("x");
	//			else printf("%d", costnum % 10);
	//		}
	//	}
	//	printf("\n");
	//}

	addnum = 2;
	if(toi(get_array2d256(distghosttree, ly,lx)) < 2){
		addnum = 1;
	}


	bfs2();


	//uppoint = dfs(lambday - 1, lambdax, 10, 0);
	//rightpoint = dfs(lambday, lambdax + 1, 10, 1);
	//downpoint = dfs(lambday + 1, lambdax, 10, 2);
	//leftpoint = dfs(lambday, lambdax - 1, 10, 3);


	if(mod(myrand(), 15) == 0){
		randomv = mod(myrand(), 15);
	}

	//uppoint = uppoint + mod(myrand(), 20);
	//rightpoint = rightpoint + mod(myrand(), 20);
	//downpoint = downpoint + mod(myrand(), 20);
	//leftpoint = leftpoint + mod(myrand(), 20);


	if(randomv == 0){
		uppoint = uppoint + 10000;
	}
	else{}
	if(randomv == 1){
		rightpoint = rightpoint + 10000;
	}
	else{}
	if(randomv == 2){
		downpoint = downpoint + 10000;
	}
	else{}
	if(randomv == 3){
		leftpoint = leftpoint + 10000;
	}
	else{}



	if(getNumber(lambday - 1,lambdax) > 0){
		if(maxpoint < uppoint){
			retdirection = 0;
			maxpoint = uppoint;
		}
		else{}
	}
	else{}
	if(getNumber(lambday,lambdax + 1) > 0){
		if(maxpoint < rightpoint){
			retdirection = 1;
			maxpoint = rightpoint;
		}
		else{}
	}
	else{}
	
	if(getNumber(lambday + 1,lambdax) > 0){
		if(maxpoint < downpoint){
			retdirection = 2;
			maxpoint = downpoint;
		}
		else{}
	}
	else{}
	if(getNumber(lambday,lambdax - 1) > 0){
		if(maxpoint < leftpoint){
			retdirection = 3;
			maxpoint = leftpoint;
		}
		else{}
	}
	else{}
	
	debug(77777777);
	debug(uppoint);
	debug(rightpoint);
	debug(downpoint);
	debug(leftpoint);
	debug(retdirection);
	debug(88888888);

		ret = P(P(retdirection, 0), retdirection);
		}
	}
	return ret;
}

int getLength(P a){
	int ret = 0;
	while(1 - atom(a)){
		ret = ret + 1;
		a = snd(a);
	}
	return ret;
}





P step(P ai, P game) {
	return step2(ai, game);
}

P init(P game, P nazo) {

	h = getLength(fst(game));
	w = getLength(fst(fst(game)));
	boardtree = list2d_to_array2d256(fst(game));
	allmaxtree = boardtree;
	if(h * w > 10000){
		nowata = 1;
	}
	else{
		nowata = 0;
	}

	nearghostlength = 3;
	dfsdepth = 10;

	randx = 123456;
	turn = 0;
	randomv = 5;

	MAXNUM = 1100000000;
	
	i = 0;
	while(i < h){
		j = 0;
		while(j < w){
			allmaxtree = set_array2d256(allmaxtree, i, j, MAXNUM);
			j = j + 1;
		}
		i = i + 1;
	}

	jisutree = allmaxtree;
	
	i = 0;
	while(i < h)
	{
		j = 0;
		while(j < w)
		{
			allmaxtree = set_array2d256(allmaxtree, i, j, MAXNUM);
			//inicount = 0;

			j = j + 1;
		}
		i = i + 1;
	}
	
	INF = 1000000000;
	board2DList_wata = fst(game);
	sizeY_wata = lengthList(board2DList_wata);
	sizeX_wata = lengthList(fst(board2DList_wata));

	if(nowata == 0){
		dist2D = initDist2D(board2DList_wata);
		dist2D = updateDist2D(dist2D);
		dist2D = updateDist2D(dist2D);
		dist2D = updateDist2D(dist2D);
		dist2D = updateDist2D(dist2D);
		dist2D = updateDist2D(dist2D);
		dist2D = updateDist2D(dist2D);
		dist2D = updateDist2D(dist2D);
		dist2D = updateDist2D(dist2D);
		dist2D = updateDist2D(dist2D);
		dist2D = updateDist2D(dist2D);
	}

	return P(0, 0);
}