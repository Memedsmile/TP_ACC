#ifndef GRAPHIC_H
#define GRAPHIC_H

class Graphic{
 private:
  vector<Vertex> v; //Ensemble des sommets dans le graphe
  Vertex source; //La source
  Vertex well; //Le puit
 public:
  //Constructeur
  Graphic();
  Graphic(Vertex,Vertex);

  //Get et Set
  void setV(Vertex,int);
  void setSource(Vertex);
  void setWell(Vertex);

  Vertex getV(int);
  Vertex getSource(int);
  Vertex getWell(int);

  
  
};

#endif
