#include <stdlib.h>
#include <stdio.h>
#include "list.h"



//Initialisation de la liste
void listInit(List* liste){
  liste->first = NULL;
  liste->last = NULL;
  liste->size = 0;
}

// Test de liste vide
int empty(List* liste){
  if(liste->size == 0)
    return 1;
  else return 0;
}

// Taille de la liste
int sizeList(List* liste){
  return liste->size;
}

// Taille du tableau data
int sizeTab(int* data){
  if(data == NULL)
    return 0;
  int i = 0;
  int size = 0;
  while(data[i] != NULL){
    size++;
    i++;
  }
  return size;
}

//Accesseur à l'élément i de la liste
int* element(List* liste, int i){
  if(i >= sizeList(liste)){
    printf("élément en dehors de la liste !");
    return NULL;
  }
  EltList* courant = liste->first;
  int j = 0;
  while(j < i)
    courant = courant->next;
  
  return courant->data;
}

//Ajout d'un élément en tete de la liste
int push_front(List* liste, int* tab){
  EltList* newelt = (EltList*) malloc (sizeof (EltList));
  if (newelt == NULL || tab == NULL)
    return -1;
 
  newelt->data = tab;

  if(liste->first == NULL){        // cas où liste est vide
    newelt->next = liste->last;
    liste->first = newelt;
  }else{
    if(liste->first->next == NULL){   // cas où liste n'a qu'un élément
      newelt->next = liste->first;
      liste->last = liste->first;
      liste->first = newelt;
    }
    else{
      newelt->next = liste->first;
      liste->first = newelt;
    }
  }
  liste->size++;
  return 1;
}
  

//Ajout d'un élément en fin de la liste
int push_back(List* liste, int* tab){
 EltList* newelt = (EltList*) malloc (sizeof (EltList));
  if (newelt == NULL || tab == NULL)
    return -1;
 
  newelt->data = tab;

  if(liste->first == NULL){        // cas où liste est vide
    newelt->next = liste->last;
    liste->first = newelt;
  }else{
    if(liste->first->next == NULL){   // cas où liste n'a qu'un élément
      liste->last = newelt;
      newelt->next = NULL;
      liste->first->next = liste->last;
    }
    else{
      liste->last->next = newelt;
      newelt->next = NULL;
      liste->last = newelt;
    }
  }
  liste->size++;
  return 1;
}

//Supression du premier élément de la liste
int pop_front(List* liste){
  if (liste->size == 0)                      // cas d'une liste vide 
    return -1;

  if(liste->size == 1){                      // cas d'une liste à un élément
    freeList(liste);
    return 0;
  }

  EltList* eltsupp = liste->first;           // cas d'une liste à au moins 2 éléments
  liste->first = liste->first->next;
  free(eltsupp);
  liste->size--;
  return 1;
}

//Supression du dernier élément de la liste
int pop_back(List* liste){
  if(liste->size == 0)                       // cas d'une liste vide 
    return -1;

  if(liste->size == 1){                      // cas d'une liste à un élément
    freeList(liste);
    return 0;
  }

  EltList* courant = liste->first;           // cas d'une liste à au moins 2 éléments
  EltList* eltsupp = liste->first->next;

  while(eltsupp->next != NULL){
    courant = eltsupp;
    eltsupp = courant->next;
  }
  
  free(eltsupp);
  liste->size--;
  return 1;
}

//Supression de la liste
int freeList(List* liste){
  if(liste->size == 0)                       // cas d'une liste vide 
    return -1;

  if(liste->size == 1){                      // cas d'une liste à un élément
    freeList(liste);
    return 0;
  }

  while(empty(liste) != 1){
    pop_back(liste);
  }
  free(liste);
  return 1;
}

//Affichage de la liste
void afficheList(List* liste){
 if(empty(liste)==1){
    printf("La liste est vide\n");
  }
  else{
    EltList* courant;
    int i, y;
    courant = liste->first;
    
    for(i = 0 ; i < liste->size ; i++){
      int s = sizeof courant->data;
      printf("tab%d est de taille : %d\n",i, s);
      printf("[");
      for(y = 0 ; y < (sizeof courant->data)/4 ; y++){
	printf("%d,  ", courant->data[y]);
      }
      printf("%d]\n", courant->data[(sizeof courant->data)/4]);
      courant = courant->next;
    }
  }
}
