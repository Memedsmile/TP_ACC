#ifndef LIST_H
#define LIST_H

typedef struct tagEltList{
  int data;
  struct tagEltList* next;
}EltList;

typedef struct tagList{
  EltList* first;
  EltList* last;
  int size;
}List;

//Initialisation de la liste
void listInit(List*);

// Test de liste vide
int emptyList(List*);

// Taille de la liste
int sizeList(List*);

//Accesseur à l'élément i de la liste
int element(List*, int);

//Ajout d'un élément en tete de la liste
int push_front(List*, int);

//Ajout d'un élément en fin de la liste
int push_back(List*, int);

//Supression du premier élément de la liste
int pop_front(List*);

//Supression du dernier élément de la liste
int pop_back(List*);

//Supression de la liste
int freeList(List*);

//Affichage de la liste
void afficheList(List*);

#endif
