#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#include "Vertex.h"
#include "Arcs.h"
#include "Graphic.h"

///////////////Variable global
const char file[]="graph.dot";
const int infinity=999999;
//////////////


//Constructeur non-parametré
Graphic::Graphic(): source(Vertex()), well(Vertex()){
  v.push_back(source);
  v.push_back(well);
}

Graphic::Graphic(const Vertex s,const Vertex w): source(s),well(w){
  v.push_back(source);
  v.push_back(well);
}

//constructeur par copie
Graphic::Graphic(const Graphic& G){
	this->setSource(G.getSource());
	this->setWell(G.getWell());
	vector<Vertex> copies = new vector<Vertex>;
	for(int i=0; i<G.getVectv().size(); i++){
		copies[i+3]=G.getV().getVertex(i+3);
	}
	copie.v=copies;
}

void Graphic::setV(Vertex v,int i){}
void Graphic::setSource(Vertex vSource){}
void Graphic::setWell(Vertex vWell){}
void Graphic::setAllVertex(vector<Vertex> allVertex){}

Vertex Graphic::getV(int i){return v[i];}
Vertex Graphic::getSource(){return source;}
Vertex Graphic::getWell(){return well;}
vector<Vertex> getV(){return v;}//rends le vector des Sommet du Graphe
void Copie(Graphic&){} //methode qui servent a la surcharge d'operateur=(affectation)

Graphic Graphic::graphEcart(){

  Graphic* Ge = new Graphic(*this); // Graphe d'écart

  bool marque[v.size()]; // Tableau de marquage des sommets parcourues

  queue<Vertex> ATraite; // file des sommets en attente

  for(int i = 0 ; i < v.size() ; i++){
    marque[i]=false;
  }

  ATraite.push(Ge->getSource());

  while(!ATraite.empty()){
    Vertex* v = new Vertex (ATraite.front());
    ATraite.pop();

    for(int j = 0 ; j < v->sizeArcOut() ; j++){
      if(!marque[v->getArcOut(j)->getVertexArrive().getVertex()]){
	marque[v->getArcOut(j)->getVertexArrive().getVertex()]=true;
	ATraite.push(v->getArcOut(j)->getVertexArrive());

	for(int i = 0 ; i < v->getArcOut(j)->getVertexArrive().sizeArcIn() ; i++){
	  if(v->getArcOut(j)->getVertexArrive().getArcIn(i)->isSaturate()){
	    Arcs* a = new Arcs (v->getArcOut(j)->getVertexArrive().getArcIn(i)->getVertexArrive(), v->getArcOut(j)->getVertexArrive().getArcIn(i)->getVertexStart(), v->getArcOut(j)->getVertexArrive().getArcIn(i)->getCapacity());
	    *v->getArcOut(j)->getVertexArrive().getArcIn(i) = *a;
	    delete a;
	  }
	 
	  else if(v->getArcOut(j)->getVertexArrive().getArcIn(i)->getFlow() != 0){
	    Arcs* a= new Arcs (v->getArcOut(j)->getVertexArrive().getArcIn(i)->getVertexArrive(), v->getArcOut(j)->getVertexArrive().getArcIn(i)->getVertexStart(), v->getArcOut(j)->getVertexArrive().getArcIn(i)->getFlow());
	    v->getArcOut(j)->getVertexArrive().getArcIn(i)->setCapacity(v->getArcOut(j)->getVertexArrive().getArcIn(i)->getCapacity() - v->getArcOut(j)->getVertexArrive().getArcIn(i)->getFlow());
	  }
	}
      }
    }
  }
  return *Ge;
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



//Methode d'affichage d'un Sommet
void Graphic::toString(ostream& o){
  for(int i =0 ; i < v.size() ; i++){
    v[i].toString(o);
  }
}


//Surcharge de l'operateur <<
ostream &operator<<(ostream& o, Graphic& g){
   g.toString(o);
   return o;
}
