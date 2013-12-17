 #include <stdlib.h>
#include <stdio.h>
#include "file.h"

// Initialisation de la file
void initialization(Queue* file){
  file->first = NULL;
  file->last = NULL;
  file->size = 0;
}

int emptyFile(Queue* file){
  if(file->size == 0)
    return 1;
  else return 0;
}

//Taille de la file
int size(Queue* file){
  return file->size;
}

//Ajout d'un élément dans la file
int push(Queue* file, int data){
  QueueElt* newelt = (QueueElt*) malloc (sizeof (QueueElt));
  if (newelt == NULL)
    return -1;
 
  newelt->data = data;

  if(file->first == NULL){        // cas où file est vide
    newelt->next = file->last;
    file->first = newelt;
  }else{
    if(file->first->next == NULL){   // cas où file n'a qu'un élément
      file->last = newelt;
      newelt->next = NULL;
      file->first->next = file->last;
    }
    else{
      file->last->next = newelt;
      newelt->next = NULL;
      file->last = newelt;
    }
  }
  file->size++;
  return 0;
}


//Supression du premier élément de la file
int pop(Queue* file){
  QueueElt* eltsupp;
  if (file->size == 0)
    return -1;
  eltsupp = file->first;
  file->first = file->first->next;
  free(eltsupp);
  file->size--;
  return 0;
}

//Supression de la file
int freeFile(Queue* file){
  if(file->size == 0)                       // cas d'une file vide 
    return -1;

  while(emptyFile(file) != 1){
    pop(file);
   }
  free(file);
  return 1;
}

//Affichage de la liste
void afficheQueue(Queue* file){
  if(emptyFile(file)==1){
    printf("La file est vide\n");
  }
  else{
    QueueElt* courant;
    int i;
    courant = file->first;
    
    for(i = 0 ; i < file->size ; i++){
      printf("%d  ", courant->data);
      courant = courant->next;
    }
    printf("\n");
  }
}

