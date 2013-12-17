#include <stdlib.h>
#include <stdio.h>
#include "list.h"


int main (){
  List* liste = (List*)malloc(sizeof(List));
  listInit(liste);
  afficheList(liste);
  printf("taille de la liste : %d\n", sizeList(liste));
  push_back(liste, 10);
  afficheList(liste);
  printf("taille de la liste : %d\n", sizeList(liste));
  push_front(liste, 20);
  afficheList(liste);
  printf("taille de la liste : %d\n", sizeList(liste));
  push_back(liste, 30);
  afficheList(liste);
  printf("taille de la liste : %d\n", sizeList(liste));
  push_front(liste, 40);
  afficheList(liste);
  printf("taille de la liste : %d\n", sizeList(liste));
  push_back(liste, 50);
  afficheList(liste);
  printf("taille de la liste : %d\n", sizeList(liste));
  pop_front(liste);
  afficheList(liste);
  printf("taille de la liste : %d\n", sizeList(liste));
  pop_back(liste);
  afficheList(liste);
  printf("taille de la liste : %d\n", sizeList(liste));
  freeList(liste);
  afficheList(liste);
  printf("taille de la liste : %d\n", sizeList(liste));
  return 0;
}
