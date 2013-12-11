#include <stdlib.h>
#include <stdio.h>
#include "list.h"


int main (){
  List* liste = (List*)malloc(sizeof(List));
  listInit(liste);
  afficheList(liste);

  int tab[6] = {1, 2, 3, 4, 5, 6};
  int* p = tab;
  printf("sizeof tab vaut %d.\n", (int)sizeof tab);
  printf("sizeof p vaut %d.\n", sizeTab(p));
  // printf("taille de la liste : %d\n", sizeList(liste));
  /*int tab1[3] = {1, 2, 3};
  int s = sizeof tab1;
  // printf("tab1 est de taille : %d\n", s);
  push_back(liste,tab1);
  afficheList(liste);
  // printf("taille de la liste : %d\n", sizeList(liste));
  int tab2[3] = {5, 9, 8};
  push_front(liste,tab2);
  afficheList(liste);
  //printf("taille de la liste : %d\n", sizeList(liste));
  int tab3[4] = {0, 9, 4, 5};
  int s1 = sizeof(tab3);
  //printf("tab3 est de taille : %d\n", s1);
  push_back(liste,tab3);
  afficheList(liste);
  // printf("taille de la liste : %d\n", sizeList(liste));
  int tab4[5] = {7, 5, 8, 6, 3}; 
  push_front(liste,tab4);
  afficheList(liste);
  // printf("taille de la liste : %d\n", sizeList(liste));
  int tab5[3] = {8, 5, 2};
  push_back(liste, tab5);
  afficheList(liste);
  //printf("taille de la liste : %d\n", sizeList(liste));
  pop_front(liste);
  afficheList(liste);
  // printf("taille de la liste : %d\n", sizeList(liste));
  pop_back(liste);
  afficheList(liste);
  // printf("taille de la liste : %d\n", sizeList(liste));
  freeList(liste);
  afficheList(liste);
  // printf("taille de la liste : %d\n", sizeList(liste));*/
  return 0;
}
