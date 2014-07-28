#include "translator/lib.h"
#include "sbl/tree.cpp"
#include "sbl/queue.cpp"

P gmap;
P distghosttree;
P distlmantree;
P jisutree;

int randx;
int turn;
int fruitbonus;

int h;
int w;

int ly,lx;

int randomv;

P boardtree;
P allmaxtree;

int MAXNUM;

P q1;
P q2;
P gghosts;


int vitality;
int lambdadirection;
int lambdalive;
int lambdascore;

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
				ret = 3;
			}
			else{
				if(ret == 3){
					ret = 100;
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


int checkdfs(int y, int x, int depth, int predirection, int count){
	int ret = 0;
	if(getNumber(y, x) > 0){
		if(toi(read_tree2d(distghosttree, y, x)) > 1){
			ret = 1;
		}
	}
	return ret;
}

int checkdfsold(int y, int x, int depth, int predirection, int count){
	int ret;
	int gp;
	int glen;
	int jisu;
	ret = 1;

	if(depth > 0 - 1){
		glen = toi(read_tree2d(distghosttree, y, x));
		jisu = toi(read_tree2d(jisutree, y, x));
		if(jisu > 2){
			if(glen < count + 1){
				ret = 0;
			}
			else{
				ret = 1;
			}
		}
		else{
			if(glen < count){
				if(glen == 0){
					if(glen + 10 == mod(predirection + 2, 4)){
						ret = 1;
					}
					else{
						ret = 0;
					}
				}
				else{
					ret = 0;
				}
			}
			else{
				if(predirection == 2){}
				else
				{
					if(getNumber(y-1, x)==0){}
					else{
						ret = checkdfs(y - 1, x, depth - 1, 0, count + 1);
					}
				}
				if(predirection == 3){}
				else
				{
					if(getNumber(y, x + 1)==0){}
					else{
						ret = checkdfs(y, x + 1, depth - 1, 1, count + 1);
					}
				}
				if(predirection == 0){}
				else
				{if(getNumber(y+1, x)==0){}
					else{
						ret = checkdfs(y + 1, x, depth - 1, 2, count + 1);
					}
				}
				if(predirection == 1){}
				else
				{
					if(getNumber(y, x - 1)==0){}
					else{
						ret = checkdfs(y, x - 1, depth - 1, 3, count + 1);
					}
				}

			}
		}
	}
	else{
		ret = 1;
	}
	return ret;
}

int myabs(int a){
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

	int x,y,d,cost;

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
		if(ghostvitality == 0){
			if(ghostdist < 20){
				q1 = push_queue(q1, P(P(ghostx, ghosty), P(ghostdirection, 0)));
			}
			distghosttree = write_tree2d(distghosttree, ghosty, ghostx, 0);
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
				//debug(5000000 + toi(read_tree2d(distghosttree, y-1, x)));
				if(toi(read_tree2d(distghosttree, y-1, x)) == MAXNUM){
					distghosttree = write_tree2d(distghosttree, y-1, x, cost+1);
					q1 = push_queue(q1, P(P(x, y-1), P(0, cost+1)));
				}
			}
		}

		if(d == 3){}
		else{
			if(getNumber(y, x+1)== 0){}
			else{
				if(toi(read_tree2d(distghosttree, y, x+1)) == MAXNUM){
					distghosttree = write_tree2d(distghosttree, y, x+1, cost+1);
					q1 = push_queue(q1, P(P(x+1, y), P(1, cost+1)));
				}
			}
		}

		if(d == 0){}
		else{
			if(getNumber(y+1, x)== 0){}
			else{
				if(toi(read_tree2d(distghosttree, y+1, x)) == MAXNUM){
					distghosttree = write_tree2d(distghosttree, y+1, x, cost+1);
					q1 = push_queue(q1, P(P(x, y+1), P(2, cost+1)));
				}
			}
		}

		if(d == 1){}
		else{
			if(getNumber(y, x-1) == 0){}
			else{
				if(toi(read_tree2d(distghosttree, y, x-1)) == MAXNUM){
					distghosttree = write_tree2d(distghosttree, y, x-1, cost+1);
					q1 = push_queue(q1, P(P(x-1, y), P(3, cost+1)));
				}
			}
		}

		if(countqueue > 200){
			q1 = create_queue();
		}
		if(cost > 10){
			q1 = create_queue();
		}
	}
	//debug(777);
	//debug(countqueue);
}

void bfs(){
	int y, x, d, cost, id;
	int countqueue;
	P q1;
	P now;
	int num;
	int point;
	
	q1 = create_queue();
	if(getNumber(ly-1,lx) == 0){ uppoint -= 200000; }
	else{
		if(checkdfs(ly-1,lx,10,0,1)){
			distlmantree = write_tree2d(distlmantree, ly-1, lx, 1);
			q1 = push_queue(q1, P(P(lx,ly-1), P(0, P(1, 0))));
			uppoint += getPoint(ly-1, lx) * powdiv(20);
		}
		else{
			uppoint -= 200000;
		}
	}

	if(getNumber(ly,lx+1) == 0){ rightpoint -= 200000; }
	else{
		if(toi(read_tree2d(distghosttree, ly, lx+1)) > 1){
			distlmantree = write_tree2d(distlmantree, ly, lx+1, 1);
			q1 = push_queue(q1, P(P(lx+1,ly), P(1, P(1, 1))));
			rightpoint += getPoint(ly, lx+1) * powdiv(20);
		}
		else{
			rightpoint -= 200000;
		}
	}

	if(getNumber(ly+1,lx) == 0){ downpoint -= 200000; }
	else{
		if(checkdfs(ly+1,lx,10,0,1)){
			distlmantree = write_tree2d(distlmantree, ly+1, lx, 1);
			q1 = push_queue(q1, P(P(lx,ly+1), P(2, P(1, 2))));
			downpoint += getPoint(ly+1, lx) * powdiv(20);
		}
		else{
			downpoint -= 200000;
		}
	}

	if(getNumber(ly,lx-1) == 0){ leftpoint -= 200000; }
	else{
		if(toi(read_tree2d(distghosttree, ly, lx-1)) > 1){
			distlmantree = write_tree2d(distlmantree, ly, lx-1, 1);
			q1 = push_queue(q1, P(P(lx-1,ly), P(3, P(1, 3))));
			leftpoint += getPoint(ly, lx-1) * powdiv(20);
		}
		else{
			leftpoint -= 200000;
		}
	}

	//push_queue(q1, P(P(lx,ly),P(lambdadirection, P(1, 0))));
	//push_queue(q1, P(P(lx,ly),P(lambdadirection, P(1, 1))));
	//push_queue(q1, P(P(lx,ly),P(lambdadirection, P(1, 2))));
	//push_queue(q1, P(P(lx,ly),P(lambdadirection, P(1, 3))));

	while(1 - is_empty_queue(q1)){
		countqueue = countqueue + 1;
		now = front_queue(q1);
		q1 = pop_queue(q1);
		x = toi(fst(fst(now)));
		y = toi(snd(fst(now)));
		d = toi(fst(snd(now)));
		cost = toi(fst(snd(snd(now))));
		id =  toi(snd(snd(snd(now))));

		//debug(1000000 * id + 1000 * x + y);

		//debug(toi(read_tree2d(distlmantree, y, x)) * 1000 + toi(read_tree2d(distghosttree, y, x)));

		if(d == 2){}
		else{
			num = getNumber(y-1, x);
			point = getPoint2(num);
			if(num == 0){}
			else{
				if(toi(read_tree2d(distlmantree, y-1, x)) == MAXNUM){
					if(toi(read_tree2d(distghosttree, y-1, x)) > cost + 1){
						distlmantree = write_tree2d(distlmantree, y-1, x, cost+1);
						q1 = push_queue(q1, P(P(x, y - 1), P(0, P(cost+1, id))));

						if(id==0){
							uppoint += point * powdiv(20 - cost);
						}
						if(id==1){
							rightpoint += point * powdiv(20 - cost);
						}
						if(id==2){
							downpoint += point * powdiv(20 - cost);
						}
						if(id==3){
							leftpoint += point * powdiv(20 - cost);
						}
					}
				}
			}
		}

		if(d == 3){}
		else{
			num = getNumber(y, x + 1);
			point = getPoint2(num);
			if(num == 0){}
			else{
				if(toi(read_tree2d(distlmantree, y, x+1)) == MAXNUM){
					if(toi(read_tree2d(distghosttree, y, x + 1)) > cost + 1){ 
						distlmantree = write_tree2d(distlmantree, y, x+1, cost+1);
						q1 = push_queue(q1, P(P(x+1, y),  P(1, P(cost+1, id))));

						if(id==0){
							uppoint += point * powdiv(20 - cost);
						}
						if(id==1){
							rightpoint += point * powdiv(20 - cost);
						}
						if(id==2){
							downpoint += point * powdiv(20 - cost);
						}
						if(id==3){
							leftpoint += point * powdiv(20 - cost);
						}
					}
				}
			}
		}

		if(d == 0){}
		else{
			num = getNumber(y+1, x);
			point = getPoint2(num);
			if(num == 0){}
			else{
				if(toi(read_tree2d(distlmantree, y+1, x)) == MAXNUM){
					if(toi(read_tree2d(distghosttree, y+1, x)) > cost + 1){ 
						distlmantree = write_tree2d(distlmantree, y+1, x, cost+1);
						q1 = push_queue(q1, P(P(x, y+1),  P(2, P(cost+1, id))));

						if(id==0){
							uppoint += point * powdiv(20 - cost);
						}
						if(id==1){
							rightpoint += point * powdiv(20 - cost);
						}
						if(id==2){
							downpoint += point * powdiv(20 - cost);
						}
						if(id==3){
							leftpoint += point * powdiv(20 - cost);
						}
					}
				}
			}
		}

		if(d == 1){}
		else{
			num = getNumber(y+1, x);
			point = getPoint2(num);
			if(getNumber(x-1,y)== 0){
				if(toi(read_tree2d(distlmantree, y, x-1)) == MAXNUM){
					if(toi(read_tree2d(distghosttree, y, x - 1)) > cost + 1){ 
						distlmantree = write_tree2d(distlmantree, y, x-1, cost+1);
						q1 = push_queue(q1, P(P(x-1, y),  P(3, P(cost+1, id))));

						if(id==0){
							uppoint += point * powdiv(20 - cost);
						}
						if(id==1){
							rightpoint += point * powdiv(20 - cost);
						}
						if(id==2){
							downpoint += point * powdiv(20 - cost);
						}
						if(id==3){
							leftpoint += point * powdiv(20 - cost);
						}
					}
				}
			}
		}


		if(countqueue > 300){
			q1 = create_queue();
		}
		if(cost > 30){
			q1 = create_queue();
		}
	}
	//debug(888);
	//debug(countqueue);

}


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




	turn = turn + 1;
	distghosttree = allmaxtree;
	distlmantree = allmaxtree;

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
	gghosts = ghosts;
	fruits = snd(game3);

	fruitbonus = 0;

	fruittime = toi(fruits);
	if(fruittime > 0){
		fruitbonus = 20;
	}
	else{}

	//debug(fruittime);

	vitality = toi(fst(lambdaman)) / 137 - 2;
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

	nowpos = toi(read_tree2d(boardtree, lambday, lambdax));
	if(nowpos == 2){
		boardtree = write_tree2d(boardtree, lambday, lambdax, 1);
	}
	if(nowpos == 3){
		boardtree = write_tree2d(boardtree, lambday, lambdax, 1);
	}

	ghostbfs();

	//for(int i=0;i<h;i++){
	//	for(int j=0;j<w;j++){
	//		if(getNumber(i,j)==0) printf("#");
	//		else{
	//			int costnum = toi(read_tree2d(distghosttree, i,j));
	//			if(costnum==MAXNUM) printf("x");
	//			else printf("%d", costnum % 10);
	//		}
	//	}
	//	printf("\n");
	//}

	bfs();

	//uppoint = dfs(lambday - 1, lambdax, 10, 0);
	//rightpoint = dfs(lambday, lambdax + 1, 10, 1);
	//downpoint = dfs(lambday + 1, lambdax, 10, 2);
	//leftpoint = dfs(lambday, lambdax - 1, 10, 3);


	if(mod(myrand(), 15) == 0){
		randomv = mod(myrand(), 15);
	}

	if(randomv == 0){
		uppoint = uppoint + 10;
	}
	else{}
	if(randomv == 1){
		rightpoint = rightpoint + 10;
	}
	else{}
	if(randomv == 2){
		downpoint = downpoint + 10;
	}
	else{}
	if(randomv == 3){
		leftpoint = leftpoint + 10;
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
	debug(uppoint);
	debug(rightpoint);
	debug(downpoint);
	debug(leftpoint);
	debug(retdirection);
	debug(88888888);

	return P(P(retdirection, 0), retdirection);
}

int getLength(P a){
	int ret = 0;
	while(1 - atom(a)){
		ret = ret + 1;
		a = snd(a);
	}
	return ret;
}

P init(P game, P nazo) {
	int i,j;
	int count;

	h = getLength(fst(game));
	w = getLength(fst(fst(game)));
	boardtree = list2d_to_tree2d(fst(game));
	allmaxtree = boardtree;

	randx = 123456;
	turn = 0;
	randomv = 5;

	MAXNUM = 65535;
	
	i = 0;
	while(i < h){
		j = 0;
		while(j < w){
			allmaxtree = write_tree2d(allmaxtree, i, j, MAXNUM);
			j++;
		}
		i++;
	}

	jisutree = allmaxtree;
	
	i = 0;
	while(i<h){
		j = 0;
		while(j<w){
			count = 0;
			allmaxtree = write_tree2d(allmaxtree, i, j, MAXNUM);

			if(toi(read_tree2d(boardtree, i, j))){
			
				if(i>0){
					if(toi(read_tree2d(boardtree, i-1, j))){
						count = count + 1;
					}
				}

				if(j>0){
					if(toi(read_tree2d(boardtree, i, j-1))){
						count = count + 1;
					}
				}

				if(i<h-1){
					if(toi(read_tree2d(boardtree, i+1, j))){
						count = count + 1;
					}
				}

				if(j<w-1){
					if(toi(read_tree2d(boardtree, i, j+1))){
						count = count + 1;
					}
				}
			
			}

			jisutree = write_tree2d(jisutree, i, j, count);
			j++;
		}
		i++;
	}

	return P(0, 0);
}


P step(P ai, P game) {
	return step2(ai, game);
}

