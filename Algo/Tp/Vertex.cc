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

int Vertex::getVertex()const{return vertex;}
Arcs* Vertex::getArcOut(int row){
  if(row<arcOut.size())
    return arcOut[row];}
Arcs* Vertex::getArcIn(int row){
  if(row<arcIn.size())
    return arcIn[row];}

//Methode d'ajout d'un arc
void Vertex::addArcOut(Arcs* arc){arcOut.push_back(arc);}
void Vertex::addArcIn(Arcs* arc){arcIn.push_back(arc);}


//Surcharge
bool Vertex::operator==(const Vertex& v2){
  return this->getVertex() == v2.getVertex();
}

