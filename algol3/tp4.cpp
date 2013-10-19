#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;
////Excercice1
void pointrandom(int n,int point[][10]){
  srand(time(NULL));
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
    point[i][j]=i*60;
    point[i][j]=j*60;
    }
  }
}
void voisins2(int n , int dmax, int point[][2],vector<int> voisin[]){
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      float dist;
      if(point[i][0]!=point[j][0] && point[i][1]!=point[j][1]){
	dist = sqrt(((point[i][0]-point[j][0])*(point[i][0]-point[j][0]))+((point[i][1]-point[j][1])*(point[i][1]-point[j][1])));
	if(dist<=dmax){
	  voisin[i].push_back(j);
	}
      }
    }
  }
}
void voisins(int n , int dmax, int point[][n],vector<int> voisin1[],vector<int>voisin2){
  for(int i=0;;i<n;i++){
    for(int j=0;j<n;j++){
      voisin[i][j].push_back()
    }
  }
}
void affichage(int n, vector<int> voisin[]){
  for(int i=0;i<n;i++){
    cout<<"C'est l'élément"<<i<<endl;
    while(!voisin[i].empty()){
      cout<<voisin[i].back()<<endl;;
      voisin[i].pop_back();
    }
  }
}
///Excerice2
void affichageGraphe(int n, int point[][2],vector<int> voisin[]){
 ofstream output;                           
 output.open("Tp4-1.ps",ios::out);
 output << "%!PS-Adobe-3.0" << endl;
 output << "%%BoundingBox: 0 0 612 792" << endl;
 output << endl;  
 for(int i=0;i<n;i++)
   {output << point[i][0] << " " << point[i][1] << " 3 0 360 arc" <<endl;
   output << "0 setgray" <<endl;
   output << "fill" <<endl;
   output << "stroke"<<endl;
   output << endl;
   }
 output << endl;
 for(int i=0;i<n;i++){
   while(!(voisin[i].empty())){
     {
       output << point[i][0] << " " << point[i][1] 
	      << " moveto" << endl;
       output << point[voisin[i].back()][0] << " " << point[voisin[i].back()][1] 
	      << " lineto" << endl;
       output << "stroke" << endl;
       output << endl;
       voisin[i].pop_back();
     }
   }
 }
}
///Exercice 3
void dijkstra(int n, vector<int> voisin[], int point[][2], int pere[]){
  float distance[n];
  int traite[n];
  for (int i=0;i<n;i++){
    distance[i]=99999999;
    traite[i]=0;
  }
  pere[0]=0;
  distance[0]=0;
  int aVerif=0;
  while(aVerif<n){
    if(traite[aVerif] ==1){
      aVerif++;
    }
    else{
      for(int i=aVerif;i<n;i++){
	if(distance[aVerif]>=distance[i] && traite[i]==0){
	  aVerif=i;
	}
      }
      traite[aVerif]=1;
      while(!(voisin[aVerif].empty())){
	float longeurXY=sqrt(((point[aVerif][0]-point[voisin[aVerif].back()][0])*(point[aVerif][0]-point[voisin[aVerif].back()][0]))+((point[aVerif][1]-point[voisin[aVerif].back()][1])*(point[aVerif][1]-point[voisin[aVerif].back()][1])));
	
	if((traite[voisin[aVerif].back()]==0 ) && (distance[voisin[aVerif].back()])>((distance[aVerif]+longeurXY))){
	  distance[voisin[aVerif].back()]=distance[aVerif]+longeurXY;
	  pere[voisin[aVerif].back()]=aVerif;
	}
	voisin[aVerif].pop_back();
      }
      aVerif=0;
    }
  }
}


int construitarbre(int n, int arbre[][2], int pere[]){
  for (int i=0;i<n;i++){
    arbre[i][0]=pere[i];
    arbre[i][1]=i;
    
  }
  return n-1;
}
void affichageGraphique(int n, int k,int point[][2], int arbre[][2]){
   ofstream output;                           
 output.open("Tp42.ps",ios::out);
 output << "%!PS-Adobe-3.0" << endl;
 output << "%%BoundingBox: 0 0 612 792" << endl;
 output << endl;  
 for(int i=0;i<n;i++)
   {output << point[i][0] << " " << point[i][1] << " 3 0 360 arc" <<endl;
   output << "0 setgray" <<endl;
   output << "fill" <<endl;
   output << "stroke"<<endl;
   output << endl;
   }
 output << endl;
 for(int i=0;i<k;i++){
       output << point[arbre[i][0]][0] << " " << point[arbre[i][0]][1] 
	      << " moveto" << endl;
       output << point[arbre[i][1]][0] << " " << point[arbre[i][1]][1] 
	      << " lineto" << endl;
       output << "stroke" << endl;
       output << endl;
 }
}


int main(){
 int n;                   //Le nombre de points.
int m;                   //Le nombre d aretes.
cout << "Entrer le nombre de points: ";
cin >> n;

int dmax=50;             // La distance jusqu'a laquelle on relie deux points.

vector<int> voisin[n][n];   // Les listes de voisins.          
int point[n][n];         // Les coordonnees des points.

int d[n];                // La distance a la racine.
int arbre[n-1][2];// Les aretes de l'arbre de Dijkstra.
int pere[n];             // La relation de filiation de l'arbre de Dijkstra.
 for(int i=0;i<n;i++){
   pere[i]=i;
 }
   pointrandom(n,point);
 voisins(n,dmax,point,voisin);
 //affichage(n,voisin);
 //affichageGraphe(n,point,voisin);
 dijkstra( n, voisin, point,pere);
 int k=construitarbre(n, arbre,pere);
 
affichageGraphique(n, k,point,arbre);
return 0;
}
