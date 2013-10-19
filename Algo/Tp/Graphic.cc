#include <iostream>
#include <vector>
using namespace std;

#include "Vertex.h"
#include "Arcs.h"
#include "Graphic.h"


Graphic::Graphic(): source(Vertex()), well(Vertex()){
  v.push_back(source);
  v.push_back(well);
}

Graphic::Graphic(const Vertex s,const Vertex w): source(v),well(w){
  v.push_back(source);
  v.push_back(well);
}
