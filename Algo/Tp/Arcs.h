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
  Arcs();
  Arcs(Vertex,Vertex);
  Arcs(Vertex,Vertex,int);

  //Set et get
  void setVertexStart(Vertex);
  void setVertexArrive(Vertex);
  void setCapacity(int);
  void setFlow(int);

  Vertex getVertexStart();
  Vertex getVertexArrive();
  int getCapacity();
  int getFlow();

  //Methode de circulation de flot
  void upFlow(int); //Augmente le flot
  void downFlow(int); //Diminue le flot
};

#endif
