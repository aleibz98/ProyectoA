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

int Tmida;

int num_hashes;

int primers[] = {503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719};

int total_inserts,total_inserts2;

int falsPositiu, falsPositiu2;

int singleHash(int key, int n){
    return (key%primers[n])%Tmida;
}

int singleHashDist(int key, int n) {
    return ((key%primers[n])%(Tmida/num_hashes)) + (n*Tmida/num_hashes);
}


/*formula aproximada de la probabilitat de que hi hagi un fals positiu en una cerca*/
double prob_fals_positiu(){
  double exp = -num_hashes*total_inserts/double(Tmida);
  return pow(1 - pow(e,exp), double(num_hashes));
}

double prob_fals_positiu_dist(){
    double tmp = pow(1-(1.0/Tmida),num_hashes*total_inserts2);
    return pow(1-tmp,num_hashes);
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


void insert(vector<bool>&Tabla, int i, bool dist){
    if(dist) ++total_inserts;
    else ++total_inserts2;
  
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
  
  

void search(vector<bool>&Tabla, int paraula, bool inserted, bool dist){
  
  int midav = Tabla.size();
  
  vector<int> hashes = hashKey(paraula, num_hashes);
/*
              for (int i = 0; i < hashes.size(); ++i){
                  cout << hashes[i] << " ";
              }
              cout << endl;
*/

  bool a = true;
  for(int i = 0; i < num_hashes; ++i){
      if(not Tabla[hashes[i]]) {
          a = false;
          break;
      }
  }
    // a == true -> si que està a la taula

  //cout << ((a) ? "Sí" : "No") << endl;
    if (a and not inserted){
        if (dist) falsPositiu++;
        else falsPositiu2++;
    /*
    if ((not a) and inserted){
        cout << "EEEEEEEPPPPPPPPPPAAAAAAA WTF" << endl;
        for (int i = 0; i < num_hashes; ++i){
            cout << hashes[i] << " " << Tabla[hashes[i]] << endl;
        }
    */
    }

    //if (not a) cout << "no esta a la taula" << endl;
    //else cout << "està a la taula" << endl;
}


int main(){
    falsPositiu = falsPositiu2 = 0;
    total_inserts = total_inserts2 = 0;

    cin >> num_hashes;

  cin >> Tmida;
  
  vector<bool> Tabla(Tmida,false);
  vector<bool> tabla2(3*(Tmida/3 + 1),false);

  int key;
  cin >> key;
  
  while(key != 0){
    insert(Tabla,key,false);
    insert(tabla2,key,true);
    cin >> key;
  }
  
  do{
      cin >> key;
      search(Tabla,key,true, false);
      search(tabla2,key,true, true);
  } while(key != 0);

  //cout << "-----------------------------------------------" << endl;

  do {
      cin >> key;
      search(Tabla,key, false, false);
      search(tabla2,key,false, true);
  } while(key != 0);
  
  /*
  cout << "Miss: " << miss << endl;
  cout << "Hit: " << hit << endl;
  cout << "Hits parcials: " << hit_parcial << endl;
  */

  cout << "Nombre: Bloom Filter" << endl;
  cout << "Nombre de funcions de Hash: " << num_hashes << endl;

  cout << "Colisions de les funcions de hash: " << colisions << endl;
  cout << "Probabilitat aproximada de un fals positiu: " << prob_fals_positiu() << endl;
  cout << "Probabilitat fals positiu empirica: " << float(falsPositiu)/total_inserts << endl;

  cout << "Probabilitat aproximada de fals positiu a taula distribuida: " << prob_fals_positiu_dist() << endl;
  cout << "Probabilitat de fals positiu empirica a taula distribuida: " << float(falsPositiu2)/total_inserts2 << endl;
  
}
  
