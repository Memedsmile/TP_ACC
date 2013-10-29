#ifndef GRAPH_H
#define GRAPH_H

class Graph{
 private :
  int nbsom;
  double ** matrice;
  //  vector<vector<Arc>> matrice 
  // On peut utiliser des Arc au lieu du double pour ne pas se limiter à la capacité & le vector permet de gerer dynamiquement la taille du graphe

 public :
  Graph();
  Graph(int);
  ~Graph();
  int getNbsom();
  void setNbsom(int);
  double getArc(int, int);
  void setArc(int, int, double);
  
  void affiche(ostream&);
};

ostream &operator<<(ostream&, Graph&);


#endif
