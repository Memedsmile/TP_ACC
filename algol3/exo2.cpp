#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <math.h>


using namespace std;
///Exo1
void pointrandom(int n,int point[][2]){
  srand(time(NULL));
  for(int i=0;i<n;i++){
    point[i][0]=rand()%613;
    point[i][1]=rand()%793;
  }
}
///Exo2
void distances(int n, int m, int point[][2], int edge[][3]){
  int k=0;
  for(int i=0;i<n-1;i++){
    for(int j=i+1;j<n;j++){
      edge[k][0]=i;
      edge[k][1]=j;
      edge[k][2]=(point[i][1]-point[j][1])*(point[i][1]-point[j][1]);
      // cout<<"["<<edge[k][0]<<" "<<edge[k][1]<<" "<<edge[k][2]<<"]"<<endl;
      k++;
    }
  }
}
////Exercice 5
void AffichageGraphique(int n, int point[][2], int arbre[][2])       // Cree le fichier Exemple.ps qui affiche
                                                                     // les points et l'arbre de Kruskal.
{ofstream output;                           
 output.open("Exo3Exam.ps",ios::out);
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
 for(int i=0;i<n-1;i++)
   {output << point[arbre[i][0]][0] << " " << point[arbre[i][0]][1] 
	   << " moveto" << endl;
   output << point[arbre[i][1]][0] << " " << point[arbre[i][1]][1] 
	  << " lineto" << endl;
   output << "stroke" << endl;
   output << endl;
   }
}
////Exercice 4
void kruskal(int n,int m,int edge[][3],int arbre[][2]){
  int aux;
  int autre;
  int par;
  int vect[n];
  int comp[n];
  int terdit=0;
  for(int i=0;i<n;i++){
    comp[i]=i;
    vect[i]=i;
  }
  for(int i=0;i<m;i++){
      aux=comp[edge[i][0]];
      par=comp[edge[i][0]];
      autre=comp[edge[i][1]];
      if(comp[edge[i][0]] != comp[edge[i][1]]){
	arbre[terdit][0]=edge[i][0];
	arbre[terdit][1]=edge[i][1];
	terdit++;
      while(vect[par] != aux){
	comp[par]=autre;
	par=vect[par];
      }
      comp[par]=autre;
      vect[par]=vect[edge[i][1]];
      vect[edge[i][1]]=aux;
      }  
  }
  /*cout<<"{";
  for(int i=0;i<terdit;i++){
    cout<<"("<<arbre[i][0]<<" , "<<arbre[i][1]<<") ";
    }
    cout<<"}"<<endl;*/
}


////Excerice3
void tri1(int n,int m,int edge[][3]){
  int point1;
  int point2;
  int valMax;
  int ech;
  int k;
  for(int i=0;i<m;i++){
    point1=edge[i][0];
    point2=edge[i][1];
    valMax=edge[i][2];
    k=i;
    for(int j=i+1;j<m;j++){
      if(valMax>edge[j][2]){
	point1=edge[j][0];
	point2=edge[j][1];
	valMax=edge[j][2];
	k=j;
      }
    }
    for(int j=0;j<3;j++){
      ech=edge[i][j];
      if(j==0){
	edge[i][j]=point1;
	edge[k][j]=ech;
      }
      if(j==1){
	edge[i][j]=point2;
	edge[k][j]=ech;
      }
      if(j==2){
	edge[i][j]=valMax;
	edge[k][j]=ech;
      }
    }
  }			
}

 
  void fusion(int deb,int mil,int fin,int edge[][3]){
    int T1[mil-deb+1][3];
    int T2[fin-mil][3];
    int i1=0;
    int i2=0;
    int inc=deb;
    for (int i=0;i<mil-deb+1;i++){
      T1[i][0]=edge[deb+i][0];
      T1[i][1]=edge[deb+i][1];
      T1[i][2]=edge[deb+i][2];
      
    }
    for(int i=0;i<fin-mil;i++){
      T2[i][0]=edge[mil+1+i][0];
      T2[i][1]=edge[mil+1+i][1];
      T2[i][2]=edge[mil+1+i][2];
    }
    while(inc < fin+1 && i1 < mil-deb+1 && i2 <  fin-mil){
    if(T1[i1][2]>T2[i2][2]){
      edge[inc][0]=T2[i2][0];
      edge[inc][1]=T2[i2][1];
      edge[inc][2]=T2[i2][2];
      i2++;
    }
    else{
      edge[inc][0]=T1[i1][0];
      edge[inc][1]=T1[i1][1];
      edge[inc][2]=T1[i1][2];
      i1++;
    }
    inc++;
  }
  if(inc != fin+1){
    if(i1==mil-deb+1){
      while(i2<fin-mil){
	edge[inc][0]=T2[i2][0];
	edge[inc][1]=T2[i2][1];
	edge[inc][2]=T2[i2][2];
	inc++;
	i2++;}
    }
    else{
      while(i1<mil-deb+1){
	edge[inc][0]=T1[i1][0];
	edge[inc][1]=T1[i1][1];
	edge[inc][2]=T1[i1][2];
	inc++;    
	i1++;}
    }
  }
  }


   void triFusion(int deb,int fin,int edge[][3]){
     int mil;
     if(deb != fin){
       mil=(deb+fin)/2;
       triFusion(deb,mil,edge);
       triFusion(mil+1,fin,edge);
       fusion(deb,mil,fin,edge);
    }
  }


int main(){
  int n;             //Le nombre de points.
  cout << "Entrer le nombre de points: ";
  cin >> n;
  int m=n*(n-1)/2;   // Le nombre de paires de points.
  int point[n][2];   // Les coordonnees des points dans le plan.
  int edge[m][3];    // Les paires de points et le carre de leur longueur.
  int arbre[n-1][2]; // Les aretes de lÅ‚%GÅ‚ÇÅ¨%@ì¢‚arbre de Kruskal.
  pointrandom(n,point);
  distances(n,m,point,edge);
  cout<<endl;
  triFusion(0,m-1,edge);
  /* for(int k=0;k<m;k++){
    cout<<"["<<edge[k][0]<<" "<<edge[k][1]<<" "<<edge[k][2]<<"]"<<endl;
  }*/
  kruskal(n,m,edge,arbre);
  AffichageGraphique(n,point,arbre);



  return 0;
}
