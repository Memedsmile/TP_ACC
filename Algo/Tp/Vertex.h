#ifndef VERTEX_H
#define VERTEX_H

class Arcs;

class Vertex{
 private:
  int vertex; // représentation du sommet
  vector<Arcs*> arcOut; // arc sortant
  vector<Arcs*> arcIn; // arc entrant 
 public:
  //Constructeur
  Vertex();
  Vertex(int);
  Vertex(const Vertex);
  //Get et Set
  void setVertex(int);
  void setArcOut(Arcs*,int);
  void setArcIn(Arcs*,int);

  int getVertex();
  Arcs* getArcOut(int);
  Arcs* getArcIn(int);
  

  //Methode d'ajout d'un arc
  void addArcOut(Arcs*); //ajout d'un arc sortant
  void addArcIn(Arcs*); //ajout d'un arc entrant

  
};


#endif
