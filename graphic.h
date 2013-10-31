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
void affiche(struct arcs**,int);


#endif
