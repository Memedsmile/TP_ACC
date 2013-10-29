#include <iostream>
#include <vector>

using namespace std;

#include "graph.h"

///////////////////////////////////////////////////////////////////////////////
// Constructeurs
///////////////////////////////////////////////////////////////////////////////
Graph::Graph():nbsom(0){}

Graph::Graph(int n):nbsom(n){
    matrice = new double*[n];
    for(int i = 0 ; i < n ; ++i) 
      matrice[i] = new double[n];
}

///////////////////////////////////////////////////////////////////////////////
// Destructeur
///////////////////////////////////////////////////////////////////////////////
Graph::~Graph(){
  for(int i = 0 ; i < nbsom ; i++)
    delete[] matrice[i];
  delete[] matrice;
}

///////////////////////////////////////////////////////////////////////////////
// Getter
///////////////////////////////////////////////////////////////////////////////
int Graph::getNbsom(){
  return nbsom;
}

double Graph::getArc(int i, int j){
    return matrice[i][j];
}

///////////////////////////////////////////////////////////////////////////////
// Setter
///////////////////////////////////////////////////////////////////////////////
void Graph::setNbsom(int n){
  nbsom = n;
  matrice = new double*[n];
  for(int i = 0 ; i < n ; ++i) 
    matrice[i] = new double[n];
}

void Graph::setArc(int i, int j, double value)
{
    matrice[i][j] = value;
}

///////////////////////////////////////////////////////////////////////////////
// Affichage
/////////////////////////////////////////////////////////////////////////////// 

void Graph::affiche(ostream& os){
   for(int i = 0 ; i < nbsom ; i++){
        for(int j = 0 ; j < nbsom ; j++){
	  os << getArc(i,j) << "  ";
        }
	os << endl;
    }
   os << endl;
}

ostream &operator<<(ostream& os, Graph& G){
  G.affiche(os);
  return os;
}

///////////////////////////////////////////////////////////////////////////////
// Test
///////////////////////////////////////////////////////////////////////////////


int main(int argc, char ** argv){

Graph G1(2);
Graph G2();
  
    G1.setArc(0,0,1);
    G1.setArc(0,1,2);
    G1.setArc(1,0,3);
    G1.setArc(1,1,4);
    G2.setNbsom(3);
    G2.setArc(0,0,9);
    G2.setArc(0,1,8);
    G2.setArc(0,2,7);
    G2.setArc(1,0,6);
    G2.setArc(1,1,5);
    G2.setArc(1,2,4);
    G2.setArc(2,0,3);
    G2.setArc(2,1,2);
    G2.setArc(2,2,1);

    cout << G1 << endl;
    cout << G2 << endl;

    return 0;
}
