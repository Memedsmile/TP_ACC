#include <iostream>
#include <vector>
using namespace std;
#include "Vertex.h"
#include "Arcs.h"


//Constructeur
Vertex::Vertex(){
  vertex=-1;
}

Vertex::Vertex(int v){
  vertex=v;
}

//Get et Set 
void Vertex::setVertex(int v){vertex=v;}
void Vertex::setArcOut(Arcs* arc,int row){
  if(row<arcOut.size())
    arcOut[row]=arc;}
void Vertex::setArcIn(Arcs* arc,int row){
  if(row<arcIn.size())
    arcIn[row]=arc;}

int Vertex::getVertex(){return vertex;}
Arcs* Vertex::getArcOut(int row){
  if(row<arcOut.size())
    return arcOut[row];}
Arcs* Vertex::getArcIn(int row){
  if(row<arcIn.size())
    return arcIn[row];}

//Methode d'ajout d'un arc
void Vertex::addArcOut(Arcs* arc){arcOut.push_back(arc);}
void Vertex::addArcIn(Arcs* arc){arcIn.push_back(arc);}


//Methode d'affichage d'un Sommet
void Vertex::toString(ostream& o){
  o << vertex << endl;
  o << "Arc Entrant : " << endl; 
  for(int i = 0 ; i < arcIn.size() ; i++){
    arcIn[i]->toString(o);
  }
  o << "Arc Sortant : " << endl; 
  for(int i = 0 ; i < arcIn.size() ; i++){
    arcOut[i]->toString(o);
  }
}

//Methode de copie d'un vertex a partir d'un autre Vertex

void Vertex::Copie(const Vertex& v1){
  this->setVertex(v1.getVertex());
  this->setArcIn(v1.getArcIn());
  this->setArcOut(v1.getArcOut());
}

//methodes qui donnent les tailles des vectors arcIn et arcOut

int Vertex::sizeArcIn(){
  return arcIn.size();
}

int Vertex::sizeArcOut(){
  return arcOut.size();
}

Vertex Vertex::operator=(const Vertex& v2){
  this->Copie(v2)
  return *this;
}




//Surcharge de l'operateur <<
ostream &operator<<(ostream& o, Vertex& s){
   s.toString(o);
   return o;
}

//Surcharge
bool Vertex::operator==(const Vertex& v2){
  return this->getVertex() == v2.getVertex();
}


