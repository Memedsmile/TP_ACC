#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <time.h>

using namespace std;
void grapherandom(int n, int m, int edge[][2]){
  srand(time(NULL));
    for(int i=0;i<m;i++){
      edge[i][0]=rand()%n;
      edge[i][1]=rand()%n;
    }
}
void composantesAmeliore(int n, int m, int edge[][2],int comp[]){
    vector<int> vect[n];
    for(int i=0; i<n; i++){
        comp[i] = i;
        vect[i].push_back(i);
    }
    for(int i=0;i<m;i++){
        int x = edge[i][0];
        int y = edge[i][1];

        if(comp[x] != comp[y]){
	  int aux;  ///comp[x]
	  int aux2; ///comp[y]
	  int val;  ///valeur voisin sortant 
	  if(comp[x]>comp[y]){
	    aux=comp[x];
	    aux2=comp[y];
            while(vect[aux].size() != 0){
	      val = vect[aux].back();
	      vect[aux].pop_back();
	      vect[comp[aux2]].push_back(val);
	      comp[val] = comp[aux2];
            }
	  }
        }
    }
}

void afficherComposante(int n,int comp[]){
  for(int i=0;i<n;i++){
    cout<<"Le numero de composante de "<<i<<" est "<<comp[i]<<endl;
  }
}

int main(){
  //Exercice 1
  int n;  //Le nombre de points.
  int m;
  cout << "Entrer le nombre de points: ";
  cin >> n;
  cout << "Entrer le nombre d'aretes: "; //Le nombre d'arrète
  cin >> m;
  int edge[m][2]; // Tableau des aretes.
  int comp[n];
  grapherandom(n,m,edge);
  composantesAmeliore(n,m,edge,comp);
  afficherComposante(n,comp);
  //La complexité est de: O(m+n)

  //Excercice 4


  return 0;
}
