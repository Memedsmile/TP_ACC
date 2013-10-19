#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std;

int exo1(int n){
  srand(time(NULL));
  int comp[n];
  int m=n-1;
  int t=0;
  for(int i=0;i<n;i++){
    comp[i]=i;
  }
  while(m!=0){
    int x=rand()%n;
    int y=rand()%n;
    t++;
    if(comp[x]!=comp[y]){
      int aux=comp[x];
      m--;
      for(int i=0;i<n;i++){
	if(comp[i]==aux){
	  comp[i]=comp[y];
	}
      }
    }
  }
  return t;
}
/////////////////////////////////////////TP2//////////////////////////////////
void pointrandom(int n,int point[][2]){
  srand(time(NULL));
  int i=0;
  while(i<n){
    int x=rand()%613;
    int y=rand()%793;
    if((x%50)==0 && (y%50)==0){
      i++;
      point[i][0]=x;
      point[i][1]=y;
    }
  }
}
///Exo2
void distances(int n, int m, int point[][2], int edge[][3]){
  int k=0;
  for(int i=0;i<n-1;i++){
    for(int j=i+1;j<n;j++){
      edge[k][0]=i;
      edge[k][1]=j;
      edge[k][2]=((point[i][0]-point[j][0])*(point[i][0]-point[j][0]))+((point[i][1]-point[j][1])*(point[i][1]-point[j][1]));
      // cout<<"["<<edge[k][0]<<" "<<edge[k][1]<<" "<<edge[k][2]<<"]"<<endl;
      k++;
    }
  }
}
////Exercice 5
void AffichageGraphique(int n, int point[][2], int arbre[][2])       // Cree le fichier Exemple.ps qui affiche
                                                                     // les points et l'arbre de Kruskal.
{ofstream output;                           
 output.open("MulTste.ps",ios::out);
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
//////////////////////////////////////////////TP2/////////////////////////////
//////Exo2
void permutation(int m,int edge[][3]){
  srand(time(NULL));
  int x=rand()%m;
  int y=rand()%m;
  int ech;
  int ech2;
  for(int i=0;i<3;i++){
    ech=edge[0][i];
    edge[0][i]=edge[m-1][i];
    edge[m-1][i]=ech;
    ech2=edge[2][i];
    edge[2][i]=edge[m-3][i];
    edge[m-3][i]=ech2;
  }
}
///////////////////////////////////////////TP3/////////////////////////////////
////Excerice1
bool appartientPas(int x,int y,vector<int> voisins){
  vector<int> voi=voisins;
  while(!(voi.empty())){
    //cout<<voi[i].back()<<endl;
    if(voi.back() == x){
      return false;
    }
    voi.pop_back();
}
  return true;
}

void voisinstrandom(int n,int m, vector<int> voisins[]){
  srand(time(NULL));
  int arrete=0;
  int x=rand()%n;
  int y=rand()%n;
  while(arrete != m){
    if(x==y || !(appartientPas(x,y,voisins[y]) || appartientPas(y,x,voisins[x]))){
      x=rand()%n;
      y=rand()%n;
    }
    else{
      voisins[x].push_back(y);
      voisins[y].push_back(x);
      x=rand()%n;
      y=rand()%n;
      arrete++;
    }
  }
}

////Excerice2
void parcourslargeur(int n, vector<int> voisins[],int niveau[],int ordre[],int pere[]){
  int dejaVu[n];
  int r=0;
  int deb=0;
  int inc=0;
  int aT[n];
  for(int i=0;i<n;i++){
    dejaVu[i]=0;
    niveau[i]=0;
    pere[i]=i;
  }
  dejaVu[r]=1;
  ordre[r]=1;
  pere[r]=0;
  niveau[r]=0; //racine
  aT[inc]=r;
  inc++;
  int t=2;
  while(deb<inc){
    while(voisins[r].size() != 0){
      if(dejaVu[voisins[r].back()]==0){
	dejaVu[voisins[r].back()]=1;
	aT[inc]=voisins[r].back();
	inc++;
	ordre[voisins[r].back()]=t;
	t++;
	pere[voisins[r].back()]=r;
	niveau[voisins[r].back()]=niveau[r]+1;
      }
      voisins[r].pop_back();
    }
    deb++;
    r=aT[deb];
  }
}



void affichageParcoursEnLargeur(int pere[],int n){
  for(int i=0;i<n;i++){
    cout<<i<<": "<<pere[i]<<endl;
  }
}
////Exercice4
void parcoursProfondeur(int n, vector<int> voisins[], int niveau[],int pere[],int debut[], int fin[]){
  int dejaVu[n];
  int cpt=0;
  vector<int> pile;
  int r=0;
  int t=2;
  int y;
  niveau[0]=1;
  for(int i=0;i<n;i++){
    dejaVu[i]=0;
    niveau[i]=0;
    pere[i]=i;
  }
  debut[0]=1;
  dejaVu[r]=1;
  pere[r]=r;
  pile.push_back(r);
  while(!(pile.empty())){
    r=pile.back();
    if(!(voisins[r].empty())){
      y=voisins[r].back();
      voisins[r].pop_back();
      if(dejaVu[y]==0){
	dejaVu[y]=1;
	niveau[y]=niveau[r]+1;
	pile.push_back(y);
	debut[r]=t;
	t++;
	pere[y]=r;
      }
    }
    else{
      pile.pop_back();
      fin[r]=t;
      t++;
    }
  }
}
////Exercice3
void ecritureniveaux(int n, int niveau[]){
  int parcours=1;
  int cpt;
  int total=0;
  cout<<"Il y a 1 sommets de niveau 0."<<endl;
  for(int i=1;i<n;i++){
    cpt=0;
    for(int j=1;j<n;j++){
      if(parcours == niveau[j]){
	cpt++;
      }
    }
    if(cpt!=0){
    cout<<"Il y a "<<cpt<<" sommets au niveau "<<parcours<<endl;
    total+=cpt;
    }
    parcours++;
  }
  cout<<"Il y a "<<n-total-1<<" sommets qui ne sont pas dans la composante de 0"<<endl;
}
///////////////////////////////TP3///////////////////////////////////////

//////////////////Exo3

int choixVoisins(vector<int> voisins[], int dejaVu[],int i,int n){
  int tailleNonVu=0; //Compteur comparé
  int cpt=0; //Compteur provisoire des voisins
  int xRetourne=voisins[i].back();
  for(int k=0;k<voisins[i].size();k++){
    if(dejaVu[voisins[i][k]]==0){
      int x=voisins[i][k];
      for(int j=0;j<voisins[x].size();j++){
	if(dejaVu[voisins[x][j]]==0){
	  cpt++;
	}
      }
      if(tailleNonVu<cpt){
	xRetourne=x;
      }
    }
  }
  return xRetourne;
}

void parcoursProfondeurExo3(int n, vector<int> voisins[], int niveau[],int pere[],int debut[], int fin[]){
  int dejaVu[n];
  int cpt=0;
  vector<int> pile;
  int r=0;
  int t=2;
  int y;
  niveau[0]=1;
  for(int i=0;i<n;i++){
    dejaVu[i]=0;
    niveau[i]=0;
    pere[i]=i;
  }
  debut[0]=1;
  dejaVu[r]=1;
  pere[r]=r;
  pile.push_back(r);
  while(!(pile.empty())){
    r=pile.back();
    if(!(voisins[r].empty())){
      y=choixVoisins(voisins,dejaVu,r,n);
      if(y == voisins[r].back()){
	voisins[r].pop_back();
      }
      if(dejaVu[y]==0){
	dejaVu[y]=1;
	niveau[y]=niveau[r]+1;
	pile.push_back(y);
	debut[r]=t;
	t++;
	pere[y]=r;
      }
    }
    else{
      pile.pop_back();
      fin[r]=t;
      t++;
    }
  }
}


int main(){
  srand(time(NULL));
  int n;
  cout<<"Entrez la valeur de n"<<endl;
  cin>>n;
  //Exo1
  //cout<<exo1(n)<<endl;
  //int m=n*(n-1)/2;   // Le nombre de paires de points.
  int m;
  cout<<"Entrer le nombre d'arretes: ";
  cin>> m;
  int point[n][2];   // Les coordonnees des points dans le plan.
  int edge[m][3];    // Les paires de points et le carre de leur longueur.
  int arbre[n-1][2]; // Les aretes de lâ%Gâ¬%@¢âarbre de Kruskal.
  vector<int> voisins[n];	// Les listes des voisins. 
  vector<int> voisinsRandom[n];
  int pere[n];            // L'arbre en largeur.
  int ordre[n];           // L'ordre de parcours.
  int niveau[n];          // Le niveau du point.
  int debut[2*n];
  int fin[2*n];
  //Exo 2
  /* 
  pointrandom(n,point);
  distances(n,m,point,edge);
  permutation(m,edge);
  triFusion(0,m-1,edge);
  permutation(m,edge);
  kruskal(n,m,edge,arbre);
  AffichageGraphique(n,point,arbre);
  */
  
  //Exo 3
  voisinstrandom(n,m,voisins);
  //parcourslargeur(n,voisins,niveau,ordre,pere);
  //affichageParcoursEnLargeur(pere,n);
  parcoursProfondeurExo3(n,voisins,niveau,pere,debut,fin);
  ecritureniveaux(n,niveau);
}
