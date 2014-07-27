#include "translator/lib.h"
#include "sbl/list.h"
#include "sbl/tree.h"

#include "translator/tosdebug.cc"

int imax;
int jmax;

P ghostmap;

int randx;

int mod(int a, int b){
  return a - b * (a / b);
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

P step_(P state, P world) {
  P map, lman, ghosts, fruit;
  int lvital; int li, lj, ld;
  int gvital; int gi, gj, gd;

  P happy;
  P tmp_list, tmp_elem;
  int i,j,k;
  int answer;

  map = fst(world);
//  // init?????
//  imax = length_list(map);
//  jmax = length_list(fst(map));
//  // init?????
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

  ghostmap = list2d_to_tree2d(
      replicate_list(imax, replicate_list(jmax, 0)) );

  tmp_list = ghosts; while (atom(tmp_list) == 0) {  // foreach(ghosts)
    tmp_elem = fst(tmp_list);

    // gvital = toi(fst(tmp_elem));
    tmp_elem = snd(tmp_elem);
    gj = toi(fst(fst(tmp_elem)));
    gi = toi(snd(fst(tmp_elem)));
// debug(P(gi,gj));
    gd = toi(snd(tmp_elem));
    ghostmap = write_tree2d(ghostmap, gi,gj, 1);  // current pos
    k=0; while(k<4) {
      if (mod(gd+2 - k, 4) == 0) {
	// ghost cannot FURIMUKI
      } else {
	ghostmap = write_tree2d(ghostmap, gi+di(k),gj+dj(k), 1);  // next pos
      }
    k+=1; }
//     ghostmap = write_tree2d(ghostmap, gi+di(gd),gj+dj(gd), 2);  // next pos
// debug(P(P(gi,gj),P(gi+di(gd),gj+dj(gd))));

  tmp_list = snd(tmp_list); }  // end foreach
// debug_tree2d(ghostmap, imax, jmax);

  happy = replicate_list(5, 0);
  
  k=0; while(k<4) {
    i = li+di(k);
    j = lj+dj(k);
    if (toi(read_tree2d(map, i,j)) > 0) {
      if (mod(gd+2 - k, 4) == 0) {
	// FURIMUKI
	happy = write_list(happy, k, 2);
      } else {
	happy = write_list(happy, k, 3);
      }
    } else {
      // walk towards wall
      happy = write_list(happy, k, 1);
      i = li; j = lj;  // thus, lman cannot move
    }
    if (lvital < 137) {
      if (toi(read_tree2d(ghostmap, i,j)) > 0) {
	// danger
	happy = write_list(happy, k, 0);
      }
    }
//debug(P(P(i,j),read_list(happy,k)));
  k+=1; }
debug(happy);

  answer = 4;
  k = 0;
  while (100 * toi(read_list(happy, answer)) + k < 300) {
    answer = rand_r(4);
    k += 1;
  }
  return P(top(0), answer);

//  k=0; while(k<1000000000) { k+=1; }
//  return P(top(k), answer);
}

P init(P game, P ghost_ai) {
  imax = length_list(fst(game));
  jmax = length_list(fst(fst(game)));
  randx = 123456;
  return top(0);
}

P step(P state, P world) {
  return step_(state, world);
}

