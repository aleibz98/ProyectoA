#include<iostream>
#include <vector>
#include <cmath>
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

int total_inserts = 0;


int hash1 (int i,int mida){
  
  /*Escribir aqui nueva funcion de hash*/
  
  
}

int hash2 (int i,int mida){
  
  /*Escribir aqui nueva funcion de hash*/
  
  
}

int hash3 (int i,int mida){
  
  /*Escribir aqui nueva funcion de hash*/
  
  
}

/*formula aproximada de la probabilitat de que hi hagi un fals positiu en una cerca*/
double prob_fals_positiu(int mida){
  
  int exp = -3*total_inserts/mida;
  return pow(1 - pow(e,exp), 3);
  
  
}

bool hi_ha_iguals(int key1, int key2, int key3){
  
  return (key1 == key2 or key2 == key3 or key3 == key1);
  
}




void insert(vector<bool>&Tabla, int i){
    ++total_inserts;
  
    int midav = Tabla.size();
    
    int key1 = hash1(i,midav);
    int key2 = hash2(i,midav);
    int key3 = hash3(i,midav);
    
    if(hi_ha_iguals(key1,key2,key3)) ++colisions;
    
    int comp = 0;
    if(Tabla[key1])++comp;
    else Tabla[key1] = true;
    
    if(Tabla[key2])++comp;
    else Tabla[key2] = true;
    
    if(Tabla[key3])++comp;
    else Tabla[key3] = true;
    
    if(comp == 3) ++miss;
    else if(comp == 0) ++hit;
    else ++hit_parcial;
    
    
    

}
  
  

void search(vector<bool>&Tabla, int paraula){
  
  int midav = Tabla.size();
  
    int key1 = hash1(paraula, midav);
    int key2 = hash2(paraula, midav);
    int key3 = hash3(paraula, midav);
  
  
  if(not Tabla[key1] or not Tabla[key2] or not Tabla[key3]) cout << "NO es troba a la taula" << endl;
  
  else cout << "El element probablement es troba a la taula" << endl;
    
  
  
}




int main(){  
  
  int Tmida;
  cin >> Tmida;
  
  vector<bool> Tabla(Tmida);
  
  
  
  int key;
  cin >> key;
  
  while(key != 0){
    insert(Tabla,key);
    cin >> key;
    
  }
  
  
  cin >> key;
  
  while(key != 0){
    search(Tabla,key);
    cin >> key;
    
  }
  
    cin >> key;
  
  while(key != 0){
    search(Tabla,key);
    cin >> key;
    
  }
  
  
  cout << "Miss: " << miss << endl;
  cout << "Hit: " << hit << endl;
  cout << "Hits parcials: " << hit_parcial << endl;
  cout << "Colisions de les funcions de hash: " << colisions << endl;
  cout << "Probabilitat aproximada de un fals positiu: " << prob_fals_positiu(Tmida) << endl;
  
  
}
  
