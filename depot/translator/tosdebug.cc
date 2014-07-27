//#include<iostream>
void debug_tree2d(P t){
  //std::cout << "----" << std::endl;
  printf("vvvv debug_tree2d vvvv\n");
  for(int i=0; i<imax; i++){
    for(int j=0; j<jmax; j++){
      //std::cout << toi(read_tree2d(t,i,j));
      printf("%2d",toi(read_tree2d(t,i,j)));
    }
    //std::cout << std::endl;
    printf("\n");
  }
  printf("^^^^ debug_tree2d ^^^^\n");
  //std::cout << "----" << std::endl;
}
