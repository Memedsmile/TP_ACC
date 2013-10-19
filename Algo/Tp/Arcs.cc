#include <iostream>
#include <vector>
using namespace std;
#include "Arcs.h"


//Constructeurs
Arcs::Arcs(): vertexStart(Vertex()), 
	      vertexArrive(Vertex()),
	      capacity(0), 
	      flow(0) {}

Arcs::Arcs(Vertex v1,Vertex v2): vertexStart(v1), 
				 vertexArrive(v2),
				 capacity(0), 
				 flow(0) {}

Arcs::Arcs(Vertex v1,Vertex v2,int c): vertexStart(v1), 
				       vertexArrive(v2),
				       capacity(c),
				       flow(0) {}
					    


//Set et get
void Arcs::setVertexStart(Vertex v1){vertexStart=v1;}
void Arcs::setVertexArrive(Vertex v2){vertexArrive=v2;}
void Arcs::setCapacity(int c){capacity=c;}
void Arcs::setFlow(int f){flow=f;}

Vertex Arcs::getVertexStart(){return vertexStart;}
Vertex Arcs::getVertexArrive(){return vertexArrive;}
int Arcs::getCapacity(){return capacity;}
int Arcs::getFlow(){return flow;}

//Methode de circulation de flot
void Arcs::upFlow(int f){flow+=f;}
void Arcs::downFlow(int f){flow+=f;}
