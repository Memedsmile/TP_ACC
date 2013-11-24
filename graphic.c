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
	      int f = graph[column][line].flow;
	      printf("c %d f %d\n",c,f);
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


void flowMax(struct arcs** graph, struct arcs** graphEcart, int n)
{
  int line;
  int column;
  int flowMax = 0;
  for(column = 0 ; column < n ; column++)
    {
      flowMax = flowMax + graphEcart[column][0].capacity;
    }
  printf("Le flot max est de %d \n",flowMax);
  for(line = 0 ; line < n ; line++)
    {
      for(column = 0 ; column < n ; column++)
	{
	  
	}
    }
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
  struct arcs** graphEcart = graphSD(graph,n);
  //affiche(graph,n);
  affiche(graphEcart,n);

  //determine le graph d'écart max
  int sizeRoad = dijkstra(graphEcart,0,n-1,road,n);
  while(sizeRoad != 0)
    {
  afficheRoad(road,sizeRoad); 
  int load[3] ={0,0,0};
  minLoad(graphEcart,road,load,sizeRoad);
  //afficheLoad(load);
  //affiche(graphEcart,n);
  
  upFlow(graphEcart,road,sizeRoad,load[2]);
  affiche(graphEcart,n);
  sizeRoad = dijkstra(graphEcart,0,n-1,road,n);
  }
  flowMax(graph,graphEcart,n);
    int line=0;
    while(line < n)
    {
      free(graph[line]);
      line++;
    }
  free(graphEcart);
  free(graph);
}

