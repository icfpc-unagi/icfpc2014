#include "translator/lib.h"
#include "sbl/list.h"
#include "sbl/tree.h"
#include "sbl/queue.h"

// #include "translator/tosdebug.cc"

P map;
int imax;
int jmax;

int lastdir;

P value;

int randx;

int mod(int a, int b){
  return a - b * (a / b);
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
	    que = push_queue(que, P(d+1,P(k,P(gi+di(k),gj+dj(k)))));
	  }
	}
      k+=1; }
      if (tmp == 0) {  // ghost can FURIMUKI exceptionally
	k = mod(gd+2, 4);
	// copipe vv
	  i = gi+di(k);
	  j = gj+dj(k);
	  if (toi(read_tree2d(map, i,j)) > 0) {  // not wall
	    tmp = 1;
	    que = push_queue(que, P(d+1,P(k,P(gi+di(k),gj+dj(k)))));
	  }
	// copipe ^^
      }
    }
  }
  return dist;
}

P step_(P state, P world) {
  P lman, ghosts, fruit;
  int lvital; int li, lj, ld;

  P ghostdist;
  P happy;
  int i,j,k; int s,t;
  int answer;

  map = fst(world);

  world = snd(world);
  lman = fst(world);
  world = snd(world);
  ghosts = fst(world);
  fruit = snd(world);
  map = list2d_to_tree2d(map);


  lvital = toi(fst(lman));
  lman = snd(lman);
  lj = toi(fst(fst(lman)));  // j = x
  li = toi(snd(fst(lman)));  // i = y
  lman = snd(lman);
  ld = toi(fst(lman));
  lman = snd(lman);
  // lman = (num_lives, score)

  ghostdist = get_ghostdist(ghosts);

//debug_tree2d(ghostdist, imax, jmax);

  happy = replicate_list(4, 0);
  
  k=0; while(k<4) {
    s = 3;

    i = li+di(k);
    j = lj+dj(k);
    if (toi(read_tree2d(map, i,j)) == 0) {
      // walk towards wall
      i = li; j = lj;  // thus, lman cannot move

      s = 2;
    }

    if (lvital < 137) {
      t = toi(read_tree2d(ghostdist, i,j));
      if (t > 100) t = 100;
      t = mysqrt(10000 * (2*t-1));
      s *= t;
    } else {
      s *= 500;
    }
    if (lastdir == ld) {  // I can't trust system-call's "lambdaman's direction".
      if (mod(ld+2 - k, 4) == 0) {
	// FURIMUKI
	s = s * 2 / 3;
      }
    }
    happy = write_list(happy, k, s);
    s += rand_r(5);
  k+=1; }
debug(happy);

  // find maximum idx
  answer = 4;
  s = -65536;
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
  imax = length_list(fst(game));
  jmax = length_list(fst(fst(game)));

  value =
    list_to_tree(replicate_list(imax,
    list_to_tree(replicate_list(jmax,
	0)) ));

  randx = 123456;

  lastdir = -1;
  return top(0);
}

P step(P state, P world) {
  return step_(state, world);
}

