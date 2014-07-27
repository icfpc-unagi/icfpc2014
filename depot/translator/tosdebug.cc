#include "sbl/sbl.h"

//#include<iostream>
void debug_tree2d(P t, int imax, int jmax){
  int v;
  //std::cout << "----" << std::endl;
  printf("vvvv debug_tree2d vvvv\n");
  for(int i=0; i<imax; i++){
    for(int j=0; j<jmax; j++){
      v = toi(read_tree2d(t,i,j));
      if (v > 99) {
	printf("##");
      } else {
	if (v < -9) {
	  printf("**");
	} else {
	  //std::cout << toi(read_tree2d(t,i,j));
	  printf("%2d", v);
	}
      }
    }
    //std::cout << std::endl;
    printf("\n");
  }
  printf("^^^^ debug_tree2d ^^^^\n");
  //std::cout << "----" << std::endl;
}
