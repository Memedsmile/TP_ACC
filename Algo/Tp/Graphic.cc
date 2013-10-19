#include <iostream>
#include <vector>
using namespace std;

#include "Graphic.h"
#include "Vertex.h"
#include "Arcs.h"

Graphic::Graphic(): source(Vertex()), well(Vertex()){
  v.push_back(source);
  v.push_back(well);
}

Graphic::Graphic(Vertex s,Vertex w): source(v),well(w){
  v.push_back(source);
  v.push_back(well);
}
