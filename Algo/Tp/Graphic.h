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
  Graphic(const Vertex,const Vertex);

  //Get et Set
  void setV(Vertex,int);
  void setSource(Vertex);
  void setWell(Vertex);

  Vertex getV(int);
  Vertex getSource(int);
  Vertex getWell(int);
  
  vector<Vertex> pcc();
  /**
   *Permet d'obtenir un sommet à partir de son nom
   * @param name le nom du sommet 
   * @return le somet de nom name
   */
  Vertex returnVertexOfName(int); 


  //Méthode de visualition d'un graphe
  /**
   *Création d'un fichier .dot
   *Permet la visualitation du graphe
   */
  void displayGraphic();
  
};

#endif
