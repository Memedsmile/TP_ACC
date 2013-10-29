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
  Graphic(const Graphic&);

  //Get et Set
  void setV(Vertex,int);
  void setSource(Vertex);
  void setWell(Vertex);
  void setAllVertex(vector<Vertex>);//maj de vecteur des sommets du graphe courant par le vecteur des sommets passé en parametres 


  Vertex getV(int);
  Vertex getSource();
  Vertex getWell();
  vector<Vertex> getV();//rends le vector des Sommet du Graphe
  void Copie(Graphic&);// methode qui servent a la surcharge d'operateur=(affectation)

  //Construction d'un graphe d'écart
  Graphic graphEcart();

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
  

  //Methode d'affichage d'un graphe
  void toString(ostream&);
   

  Graphic operator=(Graphic&);

};

//Surcharge de l'operateur <<
ostream &operator<<(ostream&, Graphic&);




#endif
