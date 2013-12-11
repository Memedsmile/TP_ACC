#ifndef GRAPHIC_H
#define GRAPHIC_H

struct arcs{
  int flow; //flot circulant sur l'arc
  int capacity; //capacité de l'arc
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
int* predecessors(struct arcs**, int, int, int);
int* readRoadDFS(struct arcs**, int*, int, int);
struct arcs** edmondsKarp(struct arcs**, int*, int, int, int);

//Question 7
int pluscourtchemins(struct arcs**, int**, int, int, int);
int pccrec(struct arcs**, int**, int, int, int, int, int, int);


void affiche(struct arcs**,int);
void afficheMatrice(struct arcs**, int);
void affichePere(int*,int,int);
void afficheRoad(int*,int);
void afficheLoad(int*);


#endif
