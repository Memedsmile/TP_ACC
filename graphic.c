#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <tgmath.h>
#include "graphic.h"
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
  int column=0;
  while(line<n){
    while(column<n){
      graph[line][column].flow=0;
      graph[line][column].capacity=0;
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
      graph[road[i+1]][road[i]].capacity =graph[road[i+1]][road[i]].capacity + k;
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

/*
int* predecessors(struct arcs** graph, int s, int p, int n){
  int* pred = (int*)malloc(sizeof(int) * n);
  pred[s] = s;
  int i;  
  for(i = 0 ; i < n ; i++){
    pred[i] = -1;
  }
  Queue* treat = malloc(sizeof(Queue));
  push(treat,s);
  while(empty(treat) == 0){
    int eltTraite = treat->first->data;
    pop(treat);
    for(i = 0 ; i < n ; i++){
      if(graph[eltTraite][i].capacity > 0 && pred[i] == -1){
	pred[i] = eltTraite;
	if(i == p){
	  free(treat);
	  return pred;
	}
	push(treat,i);
      }
    }
  }
  printf("Aucun chemin de la source au puit\n");
  return NULL;
}

*/
/*int* readRoadDFS(struct arcs** graph, int* pred, int s, int p){
  List roadDFS;
  int eltcourant = p;
  afficheList(roadDFS);
  printf("element courant : %d\n", eltcourant);
  roadDFS = push_front(roadDFS, eltcourant);
  afficheList(roadDFS);
  while(eltcourant != s){
    roadDFS = push_front(roadDFS, eltcourant);
    printf("element courant : %d\n", eltcourant);
    afficheList(roadDFS);
    eltcourant = pred[eltcourant];
  }
  int i;
  int* roadtab = (int*)malloc(sizeof(int)*sizeList(roadDFS));
  for(i = 0 ; i < sizeList(roadDFS) ; i++){
    roadtab[i] = element(roadDFS, i);
  }
  freeList(roadDFS);
  return roadtab;
  }*/

struct arcs** edmondsKarp(struct arcs** graph, int* flowmax, int s, int p, int n){

  /* Contruction d'un graphe de flot nul */
  struct arcs** flow = graph_initialization(n);
  printf("Matrice du flow\n");
  // afficheMatrice(flow, n);
  int line;
  int column;
  for(line = 0 ; line < n ; line++){
    for(column = 0 ; column < n ; column++){
      flow[line][column].flow = 0;
      flow[line][column].capacity = graph[line][column].capacity;
    }
  }
  afficheMatrice(flow, n);

  /* Recherche d'un chemin */
  int road[n];
  int sizeRoad = dijkstra(flow, s, p, road, n);

  /* Mise à jour du graphe flow */
  while(sizeRoad != 0){
    int load[3];
    minLoad(flow, road, load, sizeRoad);
    int i;
    afficheLoad(load);
    upFlow(flow, road, sizeRoad, load[2]);
    *flowmax += load[2];
    sizeRoad = dijkstra(flow, s, p, road, n);
  }
  
  return flow;
}


int pluscourtchemins(struct arcs** graph, int** listPCC, int s, int p, int n){
  int road[n];
  int sizeroad = dijkstra(graph, s, p , road, n);
  int nbroad = 0;
  int i = 0;
  int nbPCC = pccrec(graph, listPCC, nbroad, sizeroad, s, p , n, i);
  return nbPCC;
}

int pccrec(struct arcs** graph, int** listPCC, int nbroad, int sizeroad, int s, int p, int n, int j){

  /*printf("Boucle n°%d\nnbroad : %d\nsizeroad = %d\ns = %d, p = %d, n = %d\n",j, nbroad, sizeroad, s, p, n);
  if(nbroad == 0)
    printf("Pas de PCC!\n");
  else{
    int k;
    for(k = 0 ; k < nbroad ; k++){
      afficheRoad(listPCC[k], sizeroad);
    }
    }*/
  
  int curentroad[n];
  int size = dijkstra(graph, s, p, curentroad, n);

  if(size > sizeroad){
    return 0;
  }

  int** list = (int**)malloc(sizeof(int*) * (nbroad+1));
  int i;
  for(i = 0 ; i < nbroad+1 ; i++){
    list[i] = (int*)malloc(sizeof(int) * n);
  }
  if(nbroad != 0){
    int i;
    for(i = 0 ; i < nbroad ; i++){
      list[i] = listPCC[i];
    }
  }

  list[nbroad+1] = curentroad;
  nbroad += 1;
  listPCC = list;

  struct arcs** graphEcart = graphSD(graph, n);
  int load[3] = {0, 0, 0};
  minLoad(graph, curentroad, load, sizeroad);
  upFlow(graphEcart, curentroad, sizeroad, load[2]);

  return 1 + pccrec(graphEcart, listPCC, nbroad, sizeroad, s, p, n, j+1);
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
  //  afficheMatrice(graph, n);
  arcs_initialization(graph,n);
  afficheMatrice(graph,n);
  struct arcs** graphEcart = graphSD(graph,n);
  //printf("Graphe :\n\n");
  //afficheMatrice(graph,n);
  //printf("\n\nGraphe d'écart : \n\n ");
  // afficheMatrice(graphEcart,n);
 
  //determine le graph d'écart max
 
 int sizeRoad = dijkstra(graphEcart,0,n-1,road,n);
 
 //printf("PCC : \n");
 //afficheRoad(road,sizeRoad); 
 
 int load[3] ={0,0,0};
 minLoad(graphEcart,road,load,sizeRoad);
 // afficheLoad(load);
 
 //afficheMatrice(graphEcart,n);
 // upFlow(graphEcart,road,sizeRoad,load[2]);
 printf("\n\n");
 //afficheMatrice(graphEcart,n);
 
 int fmax = flowMax(graph, graphEcart, 0, n-1, n);
 printf("Flot Max = %d\n",fmax);
 printf("\n\n");
 //afficheMatrice(graphEcart,n);

 printf("Graph avant edmondsKarps : \n");
  afficheMatrice(graph, n);

  /* int* pred;
  pred = predecessors(graph, 0, n-1, n);
  int i;
  printf("Tableau de prédecesseur :\n");
  for(i = 1 ; i < n ; i++){
    printf("%d -> %d   ", i, pred[i]);
    }
  printf("\n");
  */
  // afficheMatrice(graph, n);

  int flowmax = 0;
  printf("test\n");
  struct arcs** flow = edmondsKarp(graph, &flowmax, 0, n-1, n);
  printf("Flot Max = %d\n", flowmax);
  afficheMatrice(flow, n);
  printf("Flot Max = %d\n", flowmax);
 
  int** listPCC;

  int nbPCC = pluscourtchemins(graph, listPCC, 0, n-1, n);
  printf("Nombres de PCC : %d\n", nbPCC);
  /*  int i, j;
  for(i = 0 ; i < nbPCC ; i++){
    printf("[");
    for(j = 0 ; j < sizeRoad-1 ; j++){
      printf("%d, ",listPCC[i][j]);
      }
    //printf("%d]\n",listPCC[i][sizeRoad-1]);
    }
  */
  //  free(pred);
  free(listPCC);
  free(flow);
 free(graphEcart);
  free(graph);
}
