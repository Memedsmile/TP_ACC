#include <stdlib.h>
#include <stdio.h>
#include "file.h"


int main (){
  Queue* fifo = (Queue*)malloc(sizeof (Queue));;
  initialization(fifo);
  afficheQueue(fifo);
  push(fifo,10);
  afficheQueue(fifo);
  push(fifo,20);
  printf("%d\n", fifo->first->next->data);
  printf("dernier élément : %d\n", fifo->last->data);
  afficheQueue(fifo);
  push(fifo,30);
  afficheQueue(fifo);
  push(fifo,40);
  printf("dernier élément : %d\n", fifo->last->data);
  afficheQueue(fifo);
  push(fifo,50);
  afficheQueue(fifo);
  pop(fifo);
  afficheQueue(fifo);
  return 0;
}
