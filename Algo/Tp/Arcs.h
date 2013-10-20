#ifndef ARCS_H
#define ARCS_H

#include "Vertex.h"

class Arcs{
 private:
  Vertex vertexStart; //sommet de départ
  Vertex vertexArrive; //sommet d'arrivé
  int capacity; //capacité de l'arc
  int flow; //flot circulant sur l'arc
 public:
  //Constructeurs
  Arcs();//par defaut (non-parametré)
  Arcs(Vertex,Vertex);//constructeur parametré param: Depart, Arrivé(sommets)
  Arcs(Vertex,Vertex,int);//constructeur parametre param: Depart, Arrivé(sommets), Capacité
  Arcs(Arcs&);//constructeur par copie
 

  //Set et get
  void setVertexStart(Vertex);//maj de Sommet de depart de l'arc courant
  void setVertexArrive(Vertex);//maj de Sommet d'arrive de l'arc courant
  void setCapacity(int);//maj la capacité de l'arc courant
  void setFlow(int);//maj la flot de l'arc courant

  Vertex getVertexStart();//rends le sommet de depart
  Vertex getVertexArrive();//rends le sommet d'arrive
  int getCapacity();//rends la capacité de l'arc courant
  int getFlow();//rends la flots de l'arc courant 

  //Methode de circulation de flot
  void upFlow(int); //Augmente le flot
  void downFlow(int); //Diminue le flot
  bool isSaturate(); //Vérifie si l'arc est saturé


  //Methode d'affichage d'un arc
  void toString(ostream&);

};

//Surcharge de l'operateur <<
ostream &operator<<(ostream&, Arcs&);

#endif
