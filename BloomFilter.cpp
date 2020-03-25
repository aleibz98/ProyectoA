#include<iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;


#define e 2.718281

//posiciones en el vector sin ocupar
int hit = 0;
//espacio parcialmente ocupado
int hit_parcial = 0;
//espacio ya ocupados
int miss = 0;
//numero de colisions entre les funcions de hash
int colisions = 0;

int num_hashes;

int primers[] = {5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

int total_inserts = 0;

int singleHash(int key, int n){
    return key%primers[n];
}


/*formula aproximada de la probabilitat de que hi hagi un fals positiu en una cerca*/
double prob_fals_positiu(int mida){
  
  int exp = -3*total_inserts/mida;
  return pow(1 - pow(e,exp), 3);
  
  
}

vector<int> hashKey(int key, int n){
    vector <int> hashes(n,0);
    for(int i = 0; i < n; ++i){
        int hash_i = singleHash(key, i);
        if(binary_search(hashes.begin(),hashes.end(), hash_i)) colisions++;
        hashes[i] = hash_i;
    }
    return hashes;
}




void insert(vector<bool>&Tabla, int i){
    ++total_inserts;
  
    int midav = Tabla.size();
    
    vector<int> hashes = hashKey(i, num_hashes);

    int comp = 0;
    for(int i = 0; i < num_hashes; ++i){
        if (Tabla[hashes[i]]) comp++;
        Tabla[hashes[i]] = true;
    }

    if (comp == num_hashes) miss++;
    else if(comp == 0) hit++;
    else hit_parcial++;
}
  
  

void search(vector<bool>&Tabla, int paraula){
  
  int midav = Tabla.size();
  
  vector<int> hashes = hashKey(paraula, num_hashes);

  bool a = true;
  for(int i = 0; i < num_hashes; ++i){
      if(not Tabla[hashes[i]]) {
          a = false;
          break;
      }
  }

  //cout << ((not a) ? "No es troba a la taula" : "Si es troba a la taula") << endl;
    if (not a) cout << "no esta a la taula" << endl;
    else cout << "està a la taula" << endl;
}


int main(){  
  
  int Tmida;
  cin >> Tmida;
  
  vector<bool> Tabla(Tmida);

  num_hashes = 1;

  int key;
  cin >> key;
  
  while(key != 0){
    insert(Tabla,key);
    cin >> key;
  }
  
  do{
      cin >> key;
      search(Tabla,key);
  } while(key != 0);

  cout << "-----------------------------------------------" << endl;

  do {
      cin >> key;
      search(Tabla,key);
  } while(key != 0);
  
  
  cout << "Miss: " << miss << endl;
  cout << "Hit: " << hit << endl;
  cout << "Hits parcials: " << hit_parcial << endl;
  cout << "Colisions de les funcions de hash: " << colisions << endl;
  cout << "Probabilitat aproximada de un fals positiu: " << prob_fals_positiu(Tmida) << endl;
  
}
  
