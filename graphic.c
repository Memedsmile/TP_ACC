#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Graphic.h"
#define NOMBRE_DE_SOMMET 10
#define CAPACITY_MAX 100


struct arcs** graph_initialization(int n){
 
  //Creation du graph
  struct arcs** graph;
  graph=(struct arcs**)malloc(n*sizeof(struct arcs*));
  int line=0;
  while(line<n){
    graph[line]=(struct arcs*)malloc(n*sizeof(struct arcs));
    line++;
  }
  
  //Iniatilisation du graph
  line=0;
  int column=0;
  while(line<n){
    while(column<n){
      graph[line][column].flow=0;
      graph[line][column].capacity=0;
      column++;
    }
    line++;
  }
  return graph;
 
}

void arcs_initialization(struct arcs** graph,int n){
  //Initialisation des arcs
  srand(time(NULL));
  int line=0;
  int column=0;
  while(line<n){
    while(column<n){
      if(line!=column && line!=n-1 && column != 0 && 
	 (line!=0 || column!=n-1)){
	int random=rand()%2;
	if(random)
	  graph[line][column].capacity=rand()%CAPACITY_MAX;
      }
      	column++;
    }
    column=0;
    line++;
  }

  //Destruction des doubles arcs sur deux sommet
  line=0;
  column=0;
  
  return;
}
void affiche(struct arcs** graph,int n){
  int line=0;
  int column=0;
  while(line < n){
    printf("Ligne %d\n",line);
    while(column < n){
      printf("   Column %d de capacité %d\n",column,graph[line][column].capacity);
      column++;
    }
    column=0;
    line++;
  }
}

int main(){
  int n=NOMBRE_DE_SOMMET;


  struct arcs** graph=graph_initialization(n);
  arcs_initialization(graph,n);
  affiche(graph,n);


  int line=0;
  while(line < n){
    free(graph[line]);
    line++;
  }
  free(graph);
}

