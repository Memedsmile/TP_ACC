#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <tgmath.h>
#include <math.h>
#include "graphic.h"
#include "file.h"
#include "list.h"

#define NOMBRE_DE_SOMMET 10
#define CAPACITY_MAX 100


struct arcs** graph_initialization(int n){
 
  //Creation du graph
  struct arcs** graph;
  graph=(struct arcs**)malloc(n*sizeof(struct arcs*));
  int line=0;
  while(line<n){
    graph[line]=(struct arcs*)malloc(n*sizeof(struct arcs));
    line++;
  }
  
  //Iniatilisation du graph
  line=0;
  while(line<n){
    int column = 0;
    while(column<n){
      graph[line][column].flow=0;
      graph[line][column].capacity=0;
      graph[line][column].layer=-1;
      column++;
    }
    line++;
  }
  return graph;
 
}

void arcs_initialization(struct arcs** graph,int n){
  //Initialisation des arcs
  srand(time(NULL));
  int line=1;
  int column=0;
  createRoadSourceWell(graph,n); // Permet de créer un chemin de la source jusqu'au puit. Permet d'avoir au moins un chemin
  while(line<n)
    {
      while(column<n)
	{
	  if(line!=column &&line!=n-1 && column != 0 && 
	     (line!=0 || column!=n-1))
	    {
	      int random=rand()%(1+abs(line-column));
	      if(random==0)
		graph[line][column].capacity=rand()%CAPACITY_MAX;
	    }
	  column++;
	}
      column=0;
      line++;
    }
  
  //Destruction des doubles arcs sur deux sommet
  line=0;
  column=0;
  
  return;
}

void createRoadSourceWell(struct arcs** graph, int n)
{
  srand(time(NULL));
  int i;
  for(i = 0 ; i < n-1 ; i++)
    {
      graph[i][i+1].capacity=1;
      graph[i][i+1].capacity += rand()%(CAPACITY_MAX-1);
    }
  return;
}


struct arcs** graphSD(struct arcs** graph, int n)
{
  struct arcs** graphEcart = graph_initialization(n);
  int line;
  int column;
  for(line = 0 ; line < n ; line++)
    {
      for(column = 0 ; column < n ; column++)
	{
	  if(graph[line][column].capacity != 0)
	    {
	      int c = graph[line][column].capacity;
	      int f = graph[line][column].flow;
	      // printf("c %d f %d\n",c,f);
	      graphEcart[line][column].capacity = c - f;
	      graphEcart[column][line].capacity =graphEcart[column][line].capacity +  f;
	    } 
	}
    }

  //affiche(graphEcart,n);
  return graphEcart;
}





int dijkstra(struct arcs** graph, int s , int p,int* road, int n)
{
  int distance[n];
  int traite[n];
  int* pere=(int*)malloc(sizeof(int) * n);
  int isAllTraite=0;
  int i;
  for(i = 0 ; i < n ; i++)
    {
      distance[i]=999999;
      traite[i]=0;
      pere[i] = i;
    }
  //pere[s]= s;
  distance[s]= 0;
  
  while(isAllTraite==0)
    {
      //Permet d'avoir le sommet avec la distance min
      int distanceMin = 99999;
      int x=-1;
      for(i = 0 ; i < n ; i++)
	{
	  if(traite[i]==0 && distance[i] < distanceMin)
	    {
	      x = i;
	      distanceMin = distance[i];
	    }
	}

      
      if(x == -1)
	{
	  isAllTraite = 1; //Tous les sommets sont traité
	}
      else
	{
	  //Pour tous les voisin de x
	  traite[x] = 1;
	  int voisX;
	  for(voisX = 0 ; voisX < n ; voisX++)
	    {
	      if(graph[x][voisX].capacity != 0)
		{
		  if(traite[voisX] == 0 && 
		     distance[voisX] > distance[x] + 1)
		    {
		      distance[voisX] = distance[x] + 1;
		      pere[voisX] = x;
		    } 
		}
	    }
	}
    }
  int sizeRoad = createRoad(pere,s,p,road,n);
  //  affichePere(pere,s,p);
  return sizeRoad;
}


int createRoad(int* pere,int s,int p,int* road,int n)
{
  int root = p;
  int sizeRoad = 1;
  while(root != s && pere[root] != root)
    {
      root = pere[root];
      sizeRoad++;
    }
  
  if(pere[root] == root && root!=s)
    {
      return 0;
    }
  root = p;
  int i = 0;
  while(i < sizeRoad)
    {
      road[sizeRoad - i - 1] = root;
      root = pere[root];
      i++;
    }
  return sizeRoad;
}



void minLoad(struct arcs** graph,int* road,int* load,int sizeRoad)
{
  int minLoad = 99999;
  int rangMinLoad = 0;
  int i = 0;

  
  while(i < sizeRoad - 1)
    {
      int flow =  graph[road[i]][road[i+1]].flow;
      int capacity = graph[road[i]][road[i+1]].capacity;
      if(minLoad > capacity - flow)
	{
	  rangMinLoad = i;
	  minLoad = capacity - flow;
	}
      i++;
    }

  
  int flow =  graph[road[rangMinLoad]][road[rangMinLoad+1]].flow;
  int capacity = graph[road[rangMinLoad]][road[rangMinLoad+1]].capacity;
  load[0] = road[rangMinLoad];
  load[1] = road[rangMinLoad + 1];
  load[2] = capacity - flow;
}

void upFlow(struct arcs** graph, int* road, int sizeRoad, int k)
{
  int i;
  for(i = 0 ; i < sizeRoad - 1 ; i++)
    {
      graph[road[i]][road[i+1]].capacity = graph[road[i]][road[i+1]].capacity - k;
      graph[road[i+1]][road[i]].capacity = graph[road[i+1]][road[i]].capacity + k;
    }
}


int flowMax(struct arcs** graph, struct arcs** graphEcart, int s, int p, int n)
{
  int road[n];
  int sizeroad = dijkstra(graph, s, p, road, n);
  if(sizeroad == 0){
    return 0;
  }
  else{
    int load[3] = {0, 0, 0};
    minLoad(graph, road, load, sizeroad);
    upFlow(graphEcart, road, sizeroad, load[2]);
    return load[2] + flowMax(graphEcart, graphEcart, s, p, n);
  }
}


struct arcs** edmondsKarp(struct arcs** graph, int* flowmax, int s, int p, int n){

  /* Contruction d'un graphe de flot nul */
  struct arcs** flow = graph_initialization(n);
 
  int line;
  int column;
  for(line = 0 ; line < n ; line++){
    for(column = 0 ; column < n ; column++){
      flow[line][column].flow = 0;
      flow[line][column].capacity = graph[line][column].capacity;
    }
  }
 
  /* Recherche d'un chemin */
  int road[n];
  int sizeRoad = dijkstra(flow, s, p, road, n);
  /* Mise à jour du graphe flow */
  while(sizeRoad != 0){
    int load[3];
    minLoad(flow, road, load, sizeRoad);
    int i;
    upFlow(flow, road, sizeRoad, load[2]);
    *flowmax += load[2];
    sizeRoad = dijkstra(flow, s, p, road, n);
  }
  return flow;
}


struct arcs** graphLayer(struct arcs** graphEcart, int s, int p, int n){
  struct arcs** gL = graph_initialization(n);
  int treated[n];
  List* treat = (List*)malloc(sizeof(List));
  listInit(treat);
  int currentlayer = 1, nbsom = 0;
  int i, j;
  for(i = 0 ; i < n ; i++){
    treated[i] = -1;
  }
  push_back(treat, s);
  treated[0] = 1;
  for(i = 0 ; i < n ; i++){
    if(graphEcart[s][i].capacity != 0 && graphEcart[s][i].flow < graphEcart[s][i].capacity && treated[i] == -1){
      gL[s][i].capacity = graphEcart[s][i].capacity;
      gL[s][i].layer = currentlayer;
      push_back(treat, i);
      treated[i] = 1;
    }
  }
  pop_front(treat);
  currentlayer++;

  while(emptyList(treat) == 0){
    int sizecouche = sizeList(treat);
    for(i = 0 ; i < sizecouche ; i++){
      int elt_i = element(treat, 0);
      for(j = 0 ; j < n ; j++){
	if(graphEcart[elt_i][j].capacity != 0 && graphEcart[elt_i][j].flow < graphEcart[elt_i][j].capacity && treated[j] == -1){
	  gL[elt_i][j].capacity = graphEcart[elt_i][j].capacity;
	  gL[elt_i][j].layer = currentlayer;
	  push_back(treat, j);
	  treated[j] = 1;
	}
      }
      pop_front(treat);
    }
    currentlayer++;
  }
  return gL;
}

	  
void minflow(struct arcs** graphLayer, int* load, int n){
  int minF = 1000000;
  int i, j;
  for(i = 0 ; i < n ; i++){
    for(j = 0 ; j < n ; j++){
      if(minF > graphLayer[i][j].capacity && graphLayer[i][j].capacity != 0){
	load[0] = i;
	load[1] = j;
	load[2] = graphLayer[i][j].capacity;
	minF = graphLayer[i][j].capacity;
      }
    }
  }
}


int rRoad(struct arcs** graph, int* load, int* road, int s, int p, int n){
  int roadsi[n];
  int roadjp[n];
  
  int sizesi = dijkstra(graph, s, load[0], roadsi, n);
  int sizejp = dijkstra(graph, load[1], p, roadjp, n);

  int sizeroad = sizesi + sizejp;
  int i, j = 0;

  for(i = 0 ; i < sizesi ; i++){
    road[j] = roadsi[i];
    j++;
  }
  
  for(i = 0 ; i < sizejp ; i++){
    road[j] = roadjp[i];
    j++;
  }
 
  return sizeroad;
}
    

int upFlowLayer(struct arcs** graph, struct arcs** graphcouche, int s, int p, int n){
  int load[3] = {0, 0, 0};
  minflow(graphcouche, load, n);
  int road[n];
  int sizeroad = rRoad(graph, load, road, s, p, n); 
  upFlow(graph, road, sizeroad, load[2]);
  return load[2];
}

int dinic(struct arcs** graph, int s, int p, int n){
  struct arcs** graphEcart = graphSD(graph, n);
  struct arcs** graphcouche;
  int flow = 0;
  int road[n];
  int sizeroad = dijkstra(graphEcart, s, p, road, n);
  while(sizeroad != 0){
    graphcouche = graphLayer(graphEcart, s, p, n);
    flow += upFlowLayer(graph, graphcouche, s, p, n);
    graphEcart = graphSD(graph, n);
    sizeroad = dijkstra(graphEcart, s, p, road, n);
  }
  return flow;
}

void DFS(struct arcs** graph, int* pere, int s, int p, int n){
  int dv[n];
  int pipo[n];
  int indice = 0;
  int i;
  for(i = 0 ; i < n ; i++){
    dv[i] = 0;
  }
  dv[s] = 1;
  pere[s] = s;
  pipo[0] = s;
  while(indice >= 0 && pipo[indice] != p){
    i = 0;
    while(i < n && (graph[pipo[indice]][i].capacity == 0 || dv[i]==1))
	{
	  i++;
	}
    if(i < n)
      {
	pere[i] = pipo[indice];
	indice++;
	pipo[indice] = i;
	dv[i] = 1;
      }
    else
      {
	indice--;
      }
  }
}


int fordfulkerson(struct arcs** graph, struct arcs** graphEcart, int s, int p, int n){
  int pere[n];
  int i;
  for(i = 0 ; i < n ; i++)
    pere[i] = i;
  DFS(graph, pere, s, p, n);
  int road[n];
  int sizeroad = createRoad(pere, s, p, road, n);
  if(sizeroad == 0){
    return 0;
  }
  else{
    int load[3] = {0, 0, 0};
    minLoad(graph, road, load, sizeroad);
    upFlow(graphEcart, road, sizeroad, load[2]);
    return load[2] + fordfulkerson(graphEcart, graphEcart, s, p, n);
  }
}

int capacityscaling(struct arcs** graph, int s, int p, int n){
  struct arcs** graphDelta = graph_initialization(n);
  struct arcs** graphEcart = graphSD(graph, n);
  int line, column;
  int maxflow = 0;
  int maxcap = 0;
  for(line = 0 ; line < n ; line++){
    for(column = 0 ; column < n ; column++){
      if(maxcap < graph[line][column].capacity){
	maxcap =  graph[line][column].capacity;
      }
    }
  }
  int log2C = log10(maxcap)/log10(2);
  int delta = pow(2, log2C);
  while(delta >= 1){  
    for(line = 0 ; line < n ; line++){
      for(column = 0 ; column < n ; column++){
	if(graphEcart[line][column].capacity < delta){
	  graphDelta[line][column].capacity = 0;
	}
	else{
	  graphDelta[line][column].capacity = graphEcart[line][column].capacity;
	}
      }
    }
    int road[n];
    int sizeroad = dijkstra(graphDelta, s, p, road, n);
    while(sizeroad != 0){
      int load[3] = {0, 0, 0};
      minLoad(graphDelta, road, load, sizeroad);
      int i;
      for(i = 0 ; i < sizeroad-1 ; i++){
	graph[road[i]][road[i+1]].flow += load[2];
      } 
      upFlow(graphEcart, road, sizeroad, load[2]);
      upFlow(graphDelta, road, sizeroad, load[2]);
      maxflow += load[2];
      sizeroad =  dijkstra(graphDelta, s, p, road, n);
    }
    delta /= 2;
  }
  return maxflow;
}
 
void affiche(struct arcs** graph,int n)
{
  int line=0;
  int column=0;
  while(line < n)
    {
      printf("Ligne %d\n",line);
      while(column < n)
	{
	  printf("   Column %d de capacité %d\n",column,graph[line][column].capacity);
	  column++;
	}
      column=0;
      line++;
    }
}

void afficheMatrice(struct arcs** graph, int n){
  int line, column;
  printf(" 0  ");
  for(line = 0 ; line < n ; line++)
    printf("   %d   ", line);
  printf("\n");
  for(line = 0 ; line < n ; line++){
    printf(" %d  ", line);
    for(column = 0 ; column < n ; column++){
      if(graph[line][column].capacity < 10){
	printf("( %d,", graph[line][column].capacity);
	if(graph[line][column].flow < 10){
	  printf(" %d)",graph[line][column].flow);
	}
	else{
	  printf("%d)",graph[line][column].flow);
	}
      }
      else{
	printf("(%d,", graph[line][column].capacity);
	if(graph[line][column].flow < 10){
	  printf(" %d)",graph[line][column].flow);
	}
	else{
	  printf("%d)",graph[line][column].flow);
	}
      }
    }
    printf("\n");
  }
}

void afficheLayer(struct arcs** graph, int n){
  int line, column;
  printf(" 0  ");
  for(line = 0 ; line < n ; line++)
    printf(" %d  ", line);
  printf("\n");
  for(line = 0 ; line < n ; line++){
    printf(" %d  ", line);
    for(column = 0 ; column < n ; column++){
      if(graph[line][column].layer < 10 && graph[line][column].layer >= 0){
	printf(" %d  ", graph[line][column].layer);
      }
      else{
	printf("%d  ", graph[line][column].layer);
      }
    }
    printf("\n");
  }
}
    
    

void affichePere(int* pere,int s, int p)
{
  int pereP = p;
  while(pereP != s && pereP != pere[pereP])
    {
      printf("%d ",pereP);
      pereP = pere[pereP];
    }
  printf("%d \n", s);
}

void afficheRoad(int* road,int sizeRoad)
{
  int i=0;
  while(i < sizeRoad)
    {
      printf("%d ",road[i]);
      i++;
    }
  printf("\n");
}


void afficheLoad(int* load)
{
  printf("%d %d est de poids %d\n", load[0], load[1], load[2]);
}

int main()
{
  int n=NOMBRE_DE_SOMMET;

  int road[n+1];
  struct arcs** graph=graph_initialization(n);
  arcs_initialization(graph,n);
  //  afficheMatrice(graph,n);
  struct arcs** graphEcart = graphSD(graph,n);
 
  //determine le graph d'écart max
 
  //int sizeRoad = dijkstra(graphEcart,0,n-1,road,n);
  /*
 int load[3] ={0,0,0};
 minLoad(graphEcart,road,load,sizeRoad);
  */// afficheLoad(load);
 
 //afficheMatrice(graphEcart,n);
 // upFlow(graphEcart,road,sizeRoad,load[2]);
 printf("\n\n");
 //afficheMatrice(graphEcart,n);
 
 //int fmax = flowMax(graph, graphEcart, 0, n-1, n);
 // printf("Flot Max = %d\n",fmax);
 //printf("\n\n");
 //afficheMatrice(graphEcart,n);

 // printf("Graph avant edmondsKarps : \n");
 //  afficheMatrice(graph, n);

 int flowmax = 0;
 // printf("test\n");
 struct arcs** flow = edmondsKarp(graph, &flowmax, 0, n-1, n);
 afficheMatrice(flow, n);
 printf("Flot Max = %d\n", flowmax);
  
  /*int** listPCC;

  int nbPCC = pluscourtchemins(graph, listPCC, 0, n-1, n);
  printf("Nombres de PCC : %d\n", nbPCC);
    int i, j;
  for(i = 0 ; i < nbPCC ; i++){
    printf("[");
    for(j = 0 ; j < sizeRoad-1 ; j++){
      printf("%d, ",listPCC[i][j]);
      }
    //printf("%d]\n",listPCC[i][sizeRoad-1]);
    }
  */
  
  /*  struct arcs** graphcouche = graphLayer(graphEcart, 0, n-1, n);
  printf("Graphe de couche :\n");
  afficheMatrice(graphcouche, n);
  printf("\n");
  afficheLayer(graphcouche, n);
  int loadbis[3];
  minflow(graphcouche, load, n);
  upFlowLayer(graph, graphcouche, 0, n-1, n);
  afficheMatrice(graph, n);
  */
  
  /*int flowdinic = dinic(graph, 0, n-1, n);
  printf("flot max dinic = %d\n\n", flowdinic);
  afficheMatrice(graph, n);
  */
/*
  int* pred = (int*)malloc(sizeof(int) * n);
  int i;
  for(i = 0 ; i < n ; i++){
    pred[i] = -1;
  }
  pred[0] = 0;
 
  int* treat = (int*)malloc(sizeof(int) * n); 
  for(i = 0 ; i < n ; i++){
    treat[i] = 0;
  }
*/
/*
 int pere[n];
 int i;
 for(i = 0 ; i < n ; i++){
   pere[i] = i;
 }

 DFS(graph, pere, 0, n-1, n);

 printf("Tableau de prédecesseur :\n");
 for(i = 0 ; i < n ; i++){
   printf("%d -> %d   ", i, pere[i]);
 }
 printf("\n");  
 */
 
 afficheMatrice(graphEcart, n);
 printf("\n");
 int flowFF = fordfulkerson(graph, graphEcart, 0, n-1, n);
 printf("flowFF = %d\n",flowFF);
 afficheMatrice(graphEcart, n);

 int flowCS =  capacityscaling(graph, 0, n-1, n);
 printf("flowCS = %d\n",flowCS);
 
  // free(pred);
  //free(listPCC);
  // free(graphcouche);
  free(flow);
  free(graphEcart);
  free(graph);
}

