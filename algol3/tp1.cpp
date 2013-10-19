 #include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;
void grapherandom(int n, int m, int edge[][2]){
  srand(time(NULL));
    for(int i=0;i<m;i++){
      edge[i][0]=rand()%n;
      edge[i][1]=rand()%n;
    }
}
void composantes(int n, int m, int edge[][2], int comp[]){
  int aux;
  int autre;
  for(int i=0;i<n;i++){
    comp[i]=i;
  }
  for(int i=0;i<m;i++){
    if(comp[edge[i][0]] != comp[edge[i][1]]){
      aux = comp[edge[i][0]];
       if(comp[edge[i][0]] > comp[edge[i][1]]){
	aux = comp[edge[i][0]];
	autre =comp[edge[i][1]];
      }
      else{
	aux = comp[edge[i][1]];
	autre = comp[edge[i][0]];
	}
      for(int j=0;j<n;j++){
	if(aux == comp[j]){
	  comp[j]=autre;
	}
      }
    }
  }
}
void composantes2(int n,int m, int edge[][2], int comp[]){
  int aux;
  int autre;
  int par;
  int vect[n];
  for(int i=0;i<n;i++){
    comp[i]=i;
    vect[i]=i;
  }
  for(int i=0;i<m;i++){
    aux=comp[edge[i][0]];
    par=comp[edge[i][0]];
    autre=comp[edge[i][1]];
    if(comp[edge[i][0]] != comp[edge[i][1]]){
      while(vect[par] != aux){
	comp[par]=autre;
	par=vect[par];
      }
      comp[par]=autre;
      vect[par]=vect[edge[i][1]];
      vect[edge[i][1]]=aux;
    }
  }
}
void composantesAmeliore(int n, int m, int edge[][2],int comp[]){
    vector<int> vect[n];
    int taille[n];
    for(int i=0; i<n; i++){
        comp[i] = i;
        vect[i].push_back(i);
	taille[comp[i]]=1;
    }
    for(int i=0;i<m;i++){
        int x = edge[i][0];
        int y = edge[i][1];

        if(comp[x] != comp[y]){
	  int aux;  ///comp[x]
	  int aux2; ///comp[y]
	  int val;  ///valeur voisin sortant 
	  if(taille[comp[x]]>taille[comp[y]]){
	    int ech=y;
	    y=x;
	    x=ech;
	  }
	  aux=comp[x];
	  aux2=comp[y];
	  taille[aux2]=taille[aux2]+taille[aux];
            while(vect[aux].size() != 0){
                val = vect[aux].back();
                vect[aux].pop_back();
                vect[comp[aux2]].push_back(val);
                comp[val] = comp[aux2];
            }
        }
    }
}


void ecrituretailles(int n, int m, int comp[]){
  int T[n];
  int T2[n];
  int nbC;
  for(int i=0;i<n;i++){
    T[i]=0;
    T2[i]=0;
  }
  for(int i=0;i<n;i++){
    T[comp[i]]++;
  }
  for(int i=0;i<n;i++){
    T2[T[i]-1]++;
  }
  for(int i=0;i<n;i++){
    if(T2[i] != 0){
      cout<<"Il y a  "<<T2[i] <<" composantes de taille "<<i+1<<endl;
      }
  }
}

int main(){ 
    int n;     // Nombre de sommets.	
    int m;     // Nombre d'aretes.	
    cout << "Entrer le nombre de sommets:";
    cin >> n;
    cout << "Entrer le nombre d'aretes:";
    cin >> m;
    int edge[m][2]; // Tableau des aretes.
    int comp[n];
    grapherandom(n,m,edge);
    composantes(n,m,edge,comp);
    /* for(int i=0;i<m;i++){
      cout<<"["<<edge[i][0]<<","<<edge[i][1]<<"]"<<endl;
    }
    for(int i=0;i<n;i++){
      cout<<comp[i]<<endl;
      }*/
    ecrituretailles(n,m,comp);

    
      





    return 0;
}
//EXERCICE 5
// Avec n= 10000 et m = 5000 on obtient un moyenne de 3600 et avec n=m= 10000 on obtient une moyenne de 1300

//P(x soit sommet isolé)=((n-1)/n)^2m=(1-1/n)^2m ~ (1-1/n)^2n = e^-2
