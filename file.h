#ifndef FILE_H
#define FILE_H


typedef struct tagQueueElt{
  int data;
  struct tagQueueElt* next;
}QueueElt;

typedef struct tagQueue{
  QueueElt* first;
  QueueElt* last;
  int size;
}Queue;

// Initialisation de la file
void initialization(Queue*);

// Test de file vide
int emptyFile(Queue*);

//Taille de la file
int size(Queue*);

//Ajout d'un élément dans la file
int push(Queue*, int);

//Supression du premier élément de la file
int pop(Queue*);

//Supression de la file
int freeFile(Queue*);

//Affichage de la liste
void afficheQueue(Queue*);

#endif
