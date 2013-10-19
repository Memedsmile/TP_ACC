#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;
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

////Pour aller plus loin

void pointrandom(int n,int point[][2]){
  srand(time(NULL));
  for(int i=0;i<n;i++){
    point[i][0]=rand()%613;
    point[i][1]=rand()%793;
  }
}
double distances(int x, int y, int point[][2]){
  
      return sqrt(((point[x][0]-point[y][0])*(point[x][0]-point[y][0]))+((point[x][1]-point[y][1])*(point[x][1]-point[y][1])));
}
void voisinsRandomGrille(int n,int &m, vector<int> voisins[],int seuil,int point[][2]){
  srand(time(NULL));
  int arrete=0;
  int x=rand()%n;
  int y=rand()%n;
  while(arrete!=m){
     if(x==y || !(appartientPas(x,y,voisins[y]) || appartientPas(y,x,voisins[x]))){
      x=rand()%n;
      y=rand()%n;
    }
    else{
      if(distances(x,y,point) < seuil){
	voisins[x].push_back(y);
	voisins[y].push_back(x);
	arrete++;
      }
      else{
	m--;
      }
      x=rand()%n;
      y=rand()%n;
    }
  }
}
void AffichageGraphique(int n, int point[][2], vector<int> voisins[])       // Cree le fichier Exemple.ps qui affiche
                                                                     // les points et l'arbre de Kruskal.
{ofstream output;                           
 output.open("Tp3.ps",ios::out);
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
 for(int i=0;i<n-1;i++){
   while(!(voisins[i].empty())){
       output << point[i][0] << " " << point[i][1] 
	     << " moveto" << endl;
       output << point[voisins[i].back()][0] << " " << point[voisins[i].back()][1]
	      << " lineto" << endl;
       output << "stroke" << endl;
       output << endl;
       voisins[i].pop_back();
       }
   }
}
void AffichageGraphiqueParcours(int n, int point[][2],int pere[])       // Cree le fichier Exemple.ps qui affiche
                                                                     // les points et l'arbre de Kruskal.
{ofstream output;                           
 output.open("Tp3Parcours.ps",ios::out);
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
       output << point[i][0] << " " << point[i][1] 
	     << " moveto" << endl;
       output << point[pere[i]][0] << " " << point[pere[i]][1]
	      << " lineto" << endl;
       output << "stroke" << endl;
       output << endl;
   }
}
///////////////////////////////////////////////////EXAM////////////////////////
int niveauMax(int niveau[],int n){
  int max=0;
  for(int i=0;i<n;i++){
    if(niveau[i]>max){
      max=niveau[i];
    }
  }
  return max;
}
////////////////////////////////////////////////////////////////////////



int main(){
  int n;             //Le nombre de sommets.
  int m;             // Le nombre d'aretes.
  int seuil;
  cout << "Entrer le nombre de sommets: ";
  cin >> n;
  // cout<< "Entrer un seuil"<<endl;
  //cin>>seuil;
  cout << "Entrer le nombre d'aretes: ";
  cin >> m;
  vector<int> voisins[n];	// Les listes des voisins. 
  vector<int> voisinsRandom[n];
  int pere[n];            // L'arbre en largeur.
  int ordre[n];           // L'ordre de parcours.
  int niveau[n];          // Le niveau du point.
  int debut[2*n];
  int fin[2*n];
  
  voisinstrandom(n,m,voisins);
  //parcourslargeur(n,voisins,niveau,ordre,pere);
  //affichageParcoursEnLargeur(pere,n);
  parcoursProfondeur(n,voisins,niveau,pere,debut,fin);
  //ecritureniveaux(n,niveau);
  
  //////////////////////////////////EXAM
  cout<<"Affichage niveau max"<<endl;
  cout<<niveauMax(niveau,n)<<endl;
  cout<<"Le niveau théorique minimum qu'on pourrait avoir est de 2 si pour tout les sommets alors il existe une unique arrete  
  //////////////////////////////////

  /////Pour aller plus loin
  //m=n*(n-1)/2;
  //int point[n][2];
  //pointrandom(n,point);
  //voisinsRandomGrille(n,m,voisins,seuil,point);
  //AffichageGraphique(n,point,voisins);
  //parcourslargeur(n,voisins,niveau,ordre,pere);
  //affichageParcoursEnLargeur(pere,n);
  //AffichageGraphiqueParcours(n,point,pere);

return 0;
}
