#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "list.h"
#include "file.h"

struct arcs{
  int flow; //flot circulant sur l'arc
  int capacity; //capacité de l'arc
  int layer;
}; 

//Crée le graphe 
//Retourne la matrice du graphe
struct arcs** graph_initialization(int);
void arcs_initialization(struct arcs**,int);
void createRoadSourceWell(struct arcs** graph,int n);

//Question 1
struct arcs** graphSD(struct arcs** graph,int n); //Graph d'écart

//Question 2
int dijkstra(struct arcs**,int,int,int*,int);
int createRoad(int*,int,int,int*,int);

//Question 3
void minLoad(struct arcs**,int*,int*,int);

//Question 4
void upFlow(struct arcs**, int*,int ,int);

//Question 5
int flowMax(struct arcs**, struct arcs**, int, int, int);

//Question 6
struct arcs** edmondsKarp(struct arcs**, int*, int, int, int);

//Question 7
struct arcs** graphLayer(struct arcs**, int, int, int);

//Question 8
void minflow(struct arcs**, int*, int);

//Question 9
int* predecessors(struct arcs**, int, int, int);
int readroad(struct arcs**, int*, int*, int*, int, int, int);
void upFlowLayer(struct arcs**, struct arcs**, int, int, int);



void affiche(struct arcs**,int);
void afficheMatrice(struct arcs**, int);
void afficheLayer(struct arcs**, int);
void affichePere(int*,int,int);
void afficheRoad(int*,int);
void afficheLoad(int*);


#endif
