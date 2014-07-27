#include "translator/lib.h"
#include "sbl/tree.cpp"

P gmap;
P distghostmap;
P distlmanmap;

int randx;
int turn;
int fruitbonus;

int h;
int w;

int randomv;

P boardtree;

int mod(int a, int b){
	int c;
	c = a / b;
	return a - b * c;
}

int myrand(){
	randx = mod(randx * 163 + 43751, 1000033);
	return randx;
}

int getNumber(int y, int x){
	return toi(read_tree2d(boardtree, y, x));
}

int getPoint(int y, int x){
	int ret;
	ret = getNumber(y, x);
	if(ret == 0){
		ret = -1;
	}
	else{
		if(ret == 1){
			ret = 0;
		}
		else{
			if(ret == 2){
				ret = 3;
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

int powdiv(int a, int mul, int div){
	int ret;
	if(a == 0){
		ret = 1;
	}
	else{
		ret = powdiv(a - 1, mul, div) * mul / div;
	}
	return ret;
}

int getLength(P a){
	int ret;
	if(atom(a)) {
		ret = 0;
	}
	else{
		ret = getLength(snd(a));
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
	if(a <= 0){
		ret = 1;
	}
	else{
		ret = 2 * pow2(a - 1);
	}
	return ret;
}

int dfs(int y, int x, int depth, int predirection){
	int ret;
	int gp;
	ret = 0;
	if(depth > 0 - 1){
		gp = getPoint(y, x);
		if(gp > 0 - 1){
			ret = ret + gp * pow2(depth);
			if(predirection == 2){}
			else
			{
				ret = ret + dfs(y - 1, x, depth - 1, 0);
			}
			if(predirection == 3){}
			else
			{
				ret = ret + dfs(y, x + 1, depth - 1, 1);
			}
			if(predirection == 0){}
			else
			{
				ret = ret + dfs(y + 1, x, depth - 1, 2);
			}
			if(predirection == 1){}
			else
			{
				ret = ret + dfs(y, x - 1, depth - 1, 3);
			}

		}
		else{}
	}
	else{}
	return ret;
}

int abs(int a){
	int ret;
	if(a < 0){
		ret = 0 - a;
	}
	else{
		ret = a;
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

P getfarpoint2(int y, int x, P map, int ly, int lx){
	P ret;
	P temp;
	int point;

	ret = P(0, 0);
	if(atom(map)){}
	else{
		point = getPoint(y, x) / 10;
		//point = 0;
		ret = P(point * sign(y - ly), point * sign(x - lx));
		temp = getfarpoint2(y, x + 1, snd(map), ly, lx);
		ret = P(toi(fst(ret)) + toi(fst(temp)), toi(snd(ret)) + toi(snd(temp)));
	}
	return ret;
}


// step
P step2(P ai, P game) {
	P map;

	P game2;

	P lambdaman;
	int vitality;
	P lambdaman2;
	P lambdalocation;
	int lambdax;
	int lambday;
	P lambdaman3;
	int lambdadirection;
	P lambdaman4;
	int lambdalive;
	int lambdascore;

	int ghostlength;

	P game3;
	P ghosts;

	P tempghost;
	int ghostvitality;
	P ghostlocation;
	int ghosty;
	int ghostx;
	int ghostdirection;

	int ghostdist;
	int ghostdist2;
	int ghostpoint;

	P fruits;

	int uppoint;
	int rightpoint;
	int downpoint;
	int leftpoint;

	int maxpoint;

	int retdirection;

	int ghostmul;

	int fruittime;

	int nowpos;

	P farpoint;



	turn = turn + 1;

	uppoint = 0;
	rightpoint = 0;
	downpoint = 0;
	leftpoint = 0;

	maxpoint = 0 - 99999999;
	retdirection = 0;

	map = fst(game);
	gmap = map;

	game2 = snd(game);
	lambdaman = fst(game2);
	game3 = snd(game2);
	ghosts = fst(game3);
	fruits = snd(game3);

	fruitbonus = 0;

	fruittime = toi(fruits);
	if(fruittime > 0){
		fruitbonus = 20;
	}
	else{}

	//debug(fruittime);

	vitality = toi(fst(lambdaman));
	lambdaman2 = snd(lambdaman);
	lambdalocation = fst(lambdaman2);
	lambdax = toi(fst(lambdalocation));
	lambday = toi(snd(lambdalocation));
	lambdaman3 = snd(lambdaman2);
	lambdadirection = toi(fst(lambdaman3));
	lambdaman4 = snd(lambdaman3);
	lambdalive = toi(fst(lambdaman4));
	lambdascore = toi(snd(lambdaman4));

	nowpos = toi(read_tree2d(boardtree, lambday, lambdax));
	if(nowpos == 2){
		boardtree = write_tree2d(boardtree, lambday, lambdax, 1);
	}
	if(nowpos == 3){
		boardtree = write_tree2d(boardtree, lambday, lambdax, 1);
	}

	uppoint = dfs(lambday - 1, lambdax, 10, 0);
	rightpoint = dfs(lambday, lambdax + 1, 10, 1);
	downpoint = dfs(lambday + 1, lambdax, 10, 2);
	leftpoint = dfs(lambday, lambdax - 1, 10, 3);


	ghostlength = 3;

	if(mod(myrand(), 15) == 0){
		randomv = mod(myrand(), 15);
	}

	if(randomv == 0){
		uppoint = uppoint + 100;
	}
	else{}
	if(randomv == 1){
		rightpoint = rightpoint + 100;
	}
	else{}
	if(randomv == 2){
		downpoint = downpoint + 100;
	}
	else{}
	if(randomv == 3){
		leftpoint = leftpoint + 100;
	}
	else{}

	while(1 - atom(ghosts)){
		tempghost = fst(ghosts);
		ghosts = snd(ghosts);
		ghostvitality = toi(fst(tempghost));
		tempghost = snd(tempghost);
		ghostlocation = fst(tempghost);
		ghostx = toi(fst(ghostlocation));
		ghosty = toi(snd(ghostlocation));
		ghostdirection = toi(snd(tempghost));

		//debug(ghostx);
		//debug(ghosty);
	
		ghostdist = abs(lambdax - ghostx) + abs(lambday - ghosty);

		if(ghostdist < (vitality / 127 - 3) * 2){
			if(ghostvitality == 2){
				ghostmul = 0;
			}
			else{
				ghostmul = -1;
			}
		}
		else{
			ghostmul = 1;
		}

		if(ghostdist < ghostlength){
			ghostpoint = 10000 * ghostlength / pow2(ghostdist) * ghostmul;
		}
		else{
			ghostpoint = 0;
		}
	
		uppoint = uppoint + ghostpoint * over0(ghosty - lambday);
		rightpoint = rightpoint + ghostpoint * over0(lambdax - ghostx);
		downpoint = downpoint + ghostpoint * over0(lambday - ghosty);
		leftpoint = leftpoint + ghostpoint * over0(ghostx - lambdax);
	}

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

	//debug(uppoint);
	//debug(rightpoint);
	//debug(downpoint);
	//debug(leftpoint);
	//debug(retdirection);

	return P(P(retdirection, 0), retdirection);
}

P init(P game, P nazo) {
	h = getLength(fst(game));
	w = getLength(fst(fst(game)));
	boardtree = list2d_to_tree2d(fst(game));

	randx = 123456;
	turn = 0;
	randomv = 5;
	return P(0, 0);
}


P step(P ai, P game) {
	return step2(ai, game);
}

