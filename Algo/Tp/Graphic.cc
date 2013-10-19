#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#include "Vertex.h"
#include "Arcs.h"
#include "Graphic.h"


///////////////Variable global
const char file[]="graph.dot";
const int infinity=999999;
//////////////


Graphic::Graphic(): source(Vertex()), well(Vertex()){
  v.push_back(source);
  v.push_back(well);
}

Graphic::Graphic(const Vertex s,const Vertex w): source(s),well(w){
  v.push_back(source);
  v.push_back(well);
}


vector<Vertex> Graphic::pcc(){
  
  vector<int> distance;
  vector<bool> isTravel;
  Vertex *father=new Vertex[v.size()];
  for(int i=0 ; i<v.size(); i++){
    isTravel.push_back(false);
    distance.push_back(infinity);
  }
  father[0]=source;
  distance[0]=0;
  int toTreat=0;
  
  while(toTreat != v.size()){
    
    if(isTravel[toTreat]){ 
      toTreat++;
    }
    else{
      
      for(int i=toTreat ; i<v.size() ; i++){
	
	if(distance[toTreat]>distance[i]){
	  toTreat=i;
	}
      
      }
      
      isTravel[toTreat]=true;
      Vertex minDistance = returnVertexOfName(toTreat);
      int quantityOutArcs = minDistance.sizeArcOut();
      
      for(int i=0 ; i<quantityOutArcs ; i++){
	int nameArcOut = minDistance.getArcOut(i)->getVertexArrive().getVertex();
	  
	if(!isTravel[nameArcOut] && (distance[nameArcOut] > distance[toTreat] + 1)){
	  distance[nameArcOut] = distance[toTreat] + 1;
	  father[nameArcOut] = minDistance;
	}
	
      }
      toTreat=0;
      
    }
  }
  vector<Vertex> wellToSource;
  wellToSource.push_back(well);
  Vertex searchSource = father[well.getVertex()];
  
  while(!(searchSource == source)){
    wellToSource.push_back(searchSource);
    searchSource = father[searchSource.getVertex()];
  }
  
  wellToSource.push_back(source);
  return wellToSource;
}

Vertex Graphic::returnVertexOfName(int name){
  for (int i=0 ; i<v.size() ; i++){

    if(name == this->getV(i).getVertex()){
      return this->getV(i);
    }
 
  }
}


void Graphic::displayGraphic(){
  //Ouverture fichier
  ofstream output; //ouvre le fichier .dot
  output.open(file,ios::out);
  output << "strict digraph {"<<endl;

  int firstFifo=0; //parcours la file
  int tripFifo=1; //donne la taille de la file
  
  vector<bool> isTravel;
  vector<Vertex> fifo;
  for(int i=0;i<v.size();i++){
    isTravel.push_back(false); //On a parcouru encore aucun sommet 
  }
  isTravel[0]=true; 
  fifo.push_back(source.getVertex());
  
  while(firstFifo<tripFifo){
    Vertex topStack=fifo.back();
    
    
    for(int i = 0; i < topStack.sizeArcOut() ; i++){
      Arcs* outVertex=topStack.getArcOut(i);
      
      /////////////////////////////////////On écrit dans le .dot
      output << topStack.getVertex(); 
      output << " " << outVertex->getVertexArrive().getVertex();
      output <<" [label = \"";
      output << outVertex->getFlow()<<" - ";
      output << outVertex->getCapacity();
      output << " \"]; " <<endl; 
      /////////////////////////////////////////////////////////
      
      //On regarde si un sommet a deja était parcouru ou non///
      if(!isTravel[outVertex->getVertexArrive().getVertex()]){
	isTravel[outVertex->getVertexArrive().getVertex()]=true;
	fifo.push_back(outVertex->getVertexArrive());
	tripFifo++;
      }
    }
    firstFifo++;
    //////////////////////////////////////////////////////////
  }
  output << " } " << endl;
}

