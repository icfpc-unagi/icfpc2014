#include "translator/lib.h"
#include "sbl/list.h"
#include "sbl/tree.h"
#include "sbl/queue.h"

P pushfront_queue(P queue, P x) {
  return P(push_stack(fst(queue), x), snd(queue));
}

#include "translator/tosdebug.cc"

P map;
int imax;
int jmax;

int lastdir;

P smell;

int randx;

int mod(int a, int b){
  return a - b * (a / b);
}

int myabs(int n) {
  if (n < 0) {
    n = -n;
  }
  return n;
}

int mynot(int n) {
  int res;
  if (n == 0) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}

int mysqrt(int n) {
  int lo, mi, hi;
  lo = 0;
  hi = 1;
  while (hi*hi<n) {
    lo = hi;
    hi *= 2;
  }
  while (hi - lo > 1) {
    mi = (hi + lo) / 2;
    if (mi*mi<n) {
      lo = mi;
    } else {
      hi = mi;
    }
  }
  return lo;
}

int mylog(int n){
  int res=0;
  while(n>1){
    n = n*9/10;
    res += 1;
  }
  return res;
}

int myrand(){  // chokudai
  randx = mod(randx * 163 + 43751, 1000033);
  return randx;
}

int rand_r(int n) {  // 0 .. n-1
  int t;
  t = myrand();
  return mod((t/1000) + mod(t,1000), n);
}


int di(int d) {
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

int dj(int d) {
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

P yabai;

void make_yabai() {
  P que, list;
  P tmp_elem;
  int i,j,k,d, ni,nj, ti,tj;
  int cnt;

  yabai =
    list_to_tree(replicate_list(imax,
    list_to_tree(replicate_list(jmax,
	0)) ));

  que = create_queue();

  i=1; while (i<imax-1) {
    j=1; while (j<jmax-1) {
      if (toi(read_tree2d(map, i,j)) > 0) {  // not wall
	cnt = 0;
	k=0; while (k<4) {
	  ni = i+di(k); nj = j+dj(k);
	  if (toi(read_tree2d(map, ni,nj)) > 0) {  // not wall
	    cnt += 1;
	  }
	k += 1; }
	if (cnt <= 1) {
	  que = push_queue(que, P(i,j));
	  // que = push_queue(que, P(1,P(i,j)));
	}
      }
    j += 1; }
  i += 1; }

  list = top(0);
  while (is_empty_queue(que) == 0) {
    tmp_elem = front_queue(que);
    list = P(tmp_elem, list);
    que = pop_queue(que);

//    d = toi(fst(tmp_elem));
//    tmp_elem = snd(tmp_elem);
    i = toi(fst(tmp_elem));
    j = toi(snd(tmp_elem));
    if (toi(read_tree2d(yabai, i,j)) == 0){
      cnt = 0;
      k=0; while (k<4) {
	ni = i+di(k); nj = j+dj(k);
	if (mynot(toi(read_tree2d(yabai, ni,nj))) * toi(read_tree2d(map, ni,nj)) > 0) {  // not wall, yabakunai.
	  cnt += 1;
	  ti = ni; tj = nj;
	}
	k += 1; }
      if (cnt <= 1) {
	yabai = write_tree2d(yabai, i,j, 65536);
	que = push_queue(que, P(ti,tj));
      }
    }
  }
//debug(list);

  que = create_queue();
  while (atom(list) == 0) {
    tmp_elem = fst(list);
    list = snd(list);

    i = toi(fst(tmp_elem));
    j = toi(snd(tmp_elem));

    if (toi(read_tree2d(yabai, i,j)) == 0) {
      que = push_queue(que, P(0,P(i,j)));
    }
  }

  if (is_empty_queue(que)) {  // all cells are yabai
    yabai = 
    list_to_tree(replicate_list(imax,
    list_to_tree(replicate_list(jmax,
	0)) ));
    // yabakunai kotoni suru.
  } else {  // yabasa := distance from yabakunai
    while (is_empty_queue(que) == 0) {
      tmp_elem = front_queue(que);
//debug(tmp_elem);
      que = pop_queue(que);

      d = toi(fst(tmp_elem));
      tmp_elem = snd(tmp_elem);
      i = toi(fst(tmp_elem));
      j = toi(snd(tmp_elem));

      if (toi(read_tree2d(yabai, i,j)) >= d) {  // GT or EQ for 0 == 0
	yabai = write_tree2d(yabai, i,j, d);
	k=0; while (k<4) {
	  ni = i+di(k); nj = j+dj(k);
	  if (toi(read_tree2d(map, ni,nj)) > 0) {  // not wall
	    que = push_queue(que, P(d+1, P(ni,nj)));
	  }
	k += 1; }
      }
    }
  }
}

P read_listtree2d(P ltt, int i, int j, int k) {
  return read_tree2d(read_list(ltt, i), j,k);
}
P write_listtree2d(P ltt, int i, int j, int k, P val) {
  return write_list(ltt, i, write_tree2d(read_list(ltt, i), j, k, val) );
}

P get_ghostdist(P ghosts) {
  P dist, dist_ex;
  P que;
  int tmp;
  int gi,gj,gd,d;
  P tmp_list, tmp_elem;
  int i,j,k;

  que = create_queue();

  dist =
    list_to_tree(replicate_list(imax,
    list_to_tree(replicate_list(jmax,
	65536)) ));
  dist_ex = replicate_list(4,dist);

  tmp_list = ghosts; while (atom(tmp_list) == 0) {  // foreach(ghosts)
    tmp_elem = fst(tmp_list);

    // gvital = toi(fst(tmp_elem));
    tmp_elem = snd(tmp_elem);
    gj = toi(fst(fst(tmp_elem)));
    gi = toi(snd(fst(tmp_elem)));
// debug(P(gi,gj));
    gd = toi(snd(tmp_elem));

    que = push_queue(que, P(0,P(gd,P(gi,gj))));
  tmp_list = snd(tmp_list); }  // end foreach

  while (is_empty_queue(que) == 0) {
    tmp_elem = front_queue(que);
    que = pop_queue(que);

    d = toi(fst(tmp_elem));
    tmp_elem = snd(tmp_elem);
    gd = toi(fst(tmp_elem));
    tmp_elem = snd(tmp_elem);
    gi = toi(fst(tmp_elem));
    gj = toi(snd(tmp_elem));

    tmp = toi(read_listtree2d(dist_ex, gd,gi,gj));
    if (tmp > d){
      dist_ex = write_listtree2d(dist_ex, gd,gi,gj, top(d));
      tmp = toi(read_tree2d(dist, gi,gj));
      if (tmp > d){
	dist = write_tree2d(dist, gi,gj, top(d));
      }

      tmp = 0;
      k=0; while(k<4) {
	if (mod(gd+2 - k, 4) == 0) {
	  // ghost cannot FURIMUKI
	} else {
	  i = gi+di(k);
	  j = gj+dj(k);
	  if (toi(read_tree2d(map, i,j)) > 0) {  // not wall
	    tmp = 1;
	    if (toi(read_tree2d(yabai, i,j)) > toi(read_tree2d(yabai, gi,gj))) {
	      que = pushfront_queue(que, P(d,P(k,P(i,j))));
	    } else {
	      que = push_queue(que, P(d+1,P(k,P(i,j))));
	    }
	  }
	}
      k+=1; }
      if (tmp == 0) {  // ghost can FURIMUKI exceptionally
	k = mod(gd+2, 4);
	// copipe vv
	  if (toi(read_tree2d(map, i,j)) > 0) {  // not wall
	    tmp = 1;
	    if (toi(read_tree2d(yabai, i,j)) > toi(read_tree2d(yabai, gi,gj))) {
	      que = pushfront_queue(que, P(d,P(k,P(i,j))));
	    } else {
	      que = push_queue(que, P(d+1,P(k,P(i,j))));
	    }
	  }
	// copipe ^^
      }
    }
  }

  
  return dist;
}

// P open;
// 
// void update_open() {
//   P oldopen;
//   int i,j,k,ni,nj;
//   int t,s,cnt,sum;
//   P list;
//   oldopen = open;
//   i=1; while (i<imax-1) {
//     j=1; while (j<jmax-1) {
//       if (toi(read_tree2d(map, i,j)) > 0) {  // not wall
// 	cnt = 0;
// 	sum = 0;
// 	list = top(0);
// 	k=0; while (k<4) {
// 	  ni = i+di(k); nj = j+dj(k);
// 	  if (toi(read_tree2d(map, ni,nj)) > 0) {  // not wall
// 	    cnt += 1;
// 	    sum += 1+mylog(toi(read_tree2d(oldopen, ni,nj)));
// 	    list = P(P(ni,nj),list);
// 	  }
// 	k += 1; }
// 	t = toi(read_tree2d(oldopen, i,j));
// 	while (atom(list) == 0) {
// 	  ni = toi(fst(fst(list)));
// 	  nj = toi(snd(fst(list)));
// 	  list = snd(list);
// 	  s = 1+mylog(toi(read_tree2d(oldopen, ni,nj)));
// 	  open = write_tree2d(open, ni,nj, toi(read_tree2d(open, ni,nj)) + t*s/sum);
// 	    // open = write_tree2d(open, i,j, top(toi(read_tree2d(open, i,j)) - t));
// 	k += 1; }
//       }
//     j += 1; }
//   i += 1; }
//   i=1; while (i<imax-1) {
//     j=1; while (j<jmax-1) {
//       if (toi(read_tree2d(map, i,j)) > 0) {  // not wall
// 	t = toi(read_tree2d(open, i,j));
// 	open = write_tree2d(open, i,j, t/2);
//       }
//     j += 1; }
//   i += 1; }
// }

P step_(P state, P world) {
  P lman, ghosts; int fruit_time;
  int powerpill_time; int li, lj, ld;

  P ghostdist;
  P oldsmell;
  P happy;
  int i,j,k, ni,nj; int d,s,t;
  P tmp_list, tmp_elem;
  int answer;

  map = list2d_to_tree2d(fst(world));
  world = snd(world);
  lman = fst(world);
  world = snd(world);
  ghosts = fst(world);
  fruit_time = toi(snd(world));

  powerpill_time = toi(fst(lman));
  lman = snd(lman);
  lj = toi(fst(fst(lman)));  // j = x
  li = toi(snd(fst(lman)));  // i = y
  lman = snd(lman);
  ld = toi(fst(lman));
  lman = snd(lman);
  // lman = (num_lives, score)

  ghostdist = get_ghostdist(ghosts);

//debug_tree2d(ghostdist, imax, jmax);
  
  oldsmell = smell;
  // smell defuses
  i=1; while (i<imax-1) {
    j=1; while (j<jmax-1) {
      t = toi(read_tree2d(oldsmell, i,j)) / 6;
      k=0; while (k<4) {
	ni = i+di(k); nj = j+dj(k);
	if (toi(read_tree2d(map, ni,nj)) > 0) {  // not wall
	  smell = write_tree2d(smell, ni,nj, top(toi(read_tree2d(smell, ni,nj)) + t));
	  smell = write_tree2d(smell, i,j, top(toi(read_tree2d(smell, i,j)) - t));
	}
      k += 1; }
    j += 1; }
  i += 1; }

//  tmp_list = ghosts; while (atom(tmp_list) == 0) {  // foreach(ghosts)
//    tmp_elem = fst(tmp_list);
//    tmp_list = snd(tmp_list);
//
//    j = toi(fst(fst(tmp_elem)));
//    i = toi(snd(fst(tmp_elem)));
//  }

  d = toi(read_tree2d(ghostdist, li,lj));  // how safe?
  i=0; while (i<imax) {
    j=0; while (j<jmax) {
      t = toi(read_tree2d(map, i,j));
      s = 0;
      if (t==4) {  // fruit
	if (fruit_time > 0) {  // there exists a fruit now
	  s = imax * jmax * 200;
	  if (s > 5000) {
	    s = 5000;
	  }  // approx points of fruit
	  s = s * fruit_time / (127*80);
	  s = s * fruit_time / (127*80);
	}
      } else {
	if (t==2) {  // pill
	  s = 10;
	} else {
	  if (t==3) {  // power pill
	    // s = 100;
	    if (powerpill_time == 0) {  // yes, I need it, now
	      s = (400 - 20 * (myabs(li-i)+myabs(lj-j))) / (d+1);
	      if (s < 0) {
		s = 0;
	      }
	      // how I need power pills: nearer pill, non safe situation.
	    }
	  }
	}
      }

      t = toi(read_tree2d(ghostdist, i,j));
      if (t > 10) { t = 10; }
      s = s*t + toi(read_tree2d(smell, i,j));
      // smell = write_tree2d(smell, i,j, s);
      smell = write_tree2d(smell, i,j, s-s/100);
      // smell decays (99/100)
    j += 1; }
  i += 1; }
  // smell = write_tree2d(smell, li,lj, -toi(read_tree2d(smell, li, lj)));  // I've just visited.
  smell = write_tree2d(smell, li,lj, toi(read_tree2d(smell, li, lj))/2);  // I've just visited.
  // smell = write_tree2d(smell, li,lj, 0);  // I've just visited.

  happy = replicate_list(4, 0);
  
  k=0; while(k<4) {
    s = 0;  // the eval

    i = li+di(k);
    j = lj+dj(k);
    if (toi(read_tree2d(map, i,j)) == 0) {
      // walk towards wall
      i = li; j = lj;  // thus, lman cannot move
    }

    s += toi(read_tree2d(smell, i,j));

//     if (lastdir == ld) {  // I can't trust system-call's "lambdaman's direction".
//       if (mod(ld+2 - k, 4) == 0) {
// 	// FURIMUKI
// 	s = s * 2 / 3;
//       }
//     }
    d = toi(read_tree2d(ghostdist, i,j));
    if (powerpill_time < 137) {
      if (d < 3) {  // too dangerous
	s -= (3-d) * 123456789;
      } else {
	if (d > 10) { d = 10; }
	s *= d+10;
      }
    } else {
      if (powerpill_time > 127*3) {  // if I can fight
	if (d > 10) { d = 10; }
	s *= 20-d;
      }
    }

    // s += rand_r(5);
    happy = write_list(happy, k, s);
  k+=1; }
debug(happy);

  // find maximum idx
  answer = 4;
  s = -987654321;
  k=0; while(k<4) {
    t = toi(read_list(happy, k));
    if (t > s) {
      s = t;
      answer = k;
    }
  k+=1; }

  lastdir = answer;
  return P(top(0), answer);

//  k=0; while(k<1000000000) { k+=1; }
//  return P(top(k), answer);
}

P init(P game, P ghost_ai) {
  int i;
  map = fst(game);
  imax = length_list(map);
  jmax = length_list(fst(map));
  map = list2d_to_tree2d(map);

  smell =
    list_to_tree(replicate_list(imax,
    list_to_tree(replicate_list(jmax,
	0)) ));
  make_yabai();
debug_tree2d(yabai, imax, jmax);

//   open =
//     list_to_tree(replicate_list(imax,
//     list_to_tree(replicate_list(jmax,
// 	10000)) ));
//   i = 0; while (i < 60) {
//     update_open();
//   i += 1; }
// for(int i=0; i<imax; i++){
//   for(int j=0; j<jmax; j++){
//     if(toi(read_tree2d(map,i,j))==0){
//       printf("######");
//     }else {
//       printf("%5d ", toi(read_tree2d(open,i,j)));
//     }
//   }
//   printf("\n");
// }

  randx = 123456;

  lastdir = -1;
  return top(0);
}

P step(P state, P world) {
  return step_(state, world);
}

