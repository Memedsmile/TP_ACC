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
  Vertex(const Vertex&);
  //Get et Set
  void setVertex(int);
  void setArcOut(Arcs*,int);
  void setArcIn(Arcs*,int);

  int getVertex();
  Arcs* getArcOut(int);
  Arcs* getArcIn(int);

 //Methode de copie d'un vertex a partir d'un autre vertex
  void Copie(Vertex&);//copie les donnes d'un Sommet dans un sommet courant
  
  //methodes donnantes les tailles des vector d'arcIN et arcOut
  int sizeArcOut();
  int sizeArcIn();

  //Methode d'ajout d'un arc
  void addArcOut(Arcs*); //ajout d'un arc sortant
  void addArcIn(Arcs*); //ajout d'un arc entrant

  //Methode d'affichage d'un Sommet
  void toString(ostream&);

  //Surcharge
  bool operator==(const Vertex&);

  
};

//Surcharge de l'operateur <<
ostream &operator<<(ostream&, Vertex&);

//surcharge d'operateurs
Vertex operator=(Vertex v1, Vertex v2);



#endif
