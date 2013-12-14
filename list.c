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
int emptyList(List* liste){
  if(liste->size == 0)
    return 1;
  else return 0;
}

// Taille de la liste
int sizeList(List* liste){
  return liste->size;
}

//Accesseur à l'élément i de la liste
int element(List* liste, int i){
  if(i >= sizeList(liste)){
    printf("élément en dehors de la liste !");
    return -1;
  }
  EltList* courant = liste->first;
  int j = 0;
  while(j < i)
    courant = courant->next;
  
  return courant->data;
}

//Ajout d'un élément en tete de la liste
int push_front(List* liste, int val){
  EltList* newelt = (EltList*) malloc (sizeof (EltList));
  if (newelt == NULL)
    return -1;
 
  newelt->data = val;

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
int push_back(List* liste, int val){
 EltList* newelt = (EltList*) malloc (sizeof (EltList));
  if (newelt == NULL)
    return -1;
 
  newelt->data = val;

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
    free(liste->first);
    liste->size--;
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
    free(liste->first);
    liste->size--;
    return 0;
  }

  EltList* courant = liste->first;           // cas d'une liste à au moins 2 éléments
  EltList* eltsupp = liste->first->next;

  while(eltsupp->next != NULL){
    courant = eltsupp;
    eltsupp = courant->next;
  }
  courant->next = NULL;
  liste->last = courant;
  
  free(eltsupp);
  liste->size--;
  return 1;
}

//Supression de la liste
int freeList(List* liste){
  if(liste->size == 0)                       // cas d'une liste vide 
    return -1;

  if(liste->size == 1){                      // cas d'une liste à un élément
    pop_front(liste);
    free(liste);
    return 0;
  }

  while(emptyList(liste) != 1){
    pop_back(liste);
   }
  free(liste);
  return 1;
}

//Affichage de la liste
void afficheList(List* liste){
 if(emptyList(liste)==1){
   printf("La liste est vide\n");
 }
 else if(sizeList(liste) == 1){
      printf("[ %d ]\n", liste->first->data);
 }
 else{
    EltList* courant;
    int i, y;
    courant = liste->first;
    
    printf("[");
    while(courant != liste->last){
      printf("%d,  ", courant->data);
      courant = courant->next;
    }
     printf("%d]\n", liste->last->data);
  }
}
