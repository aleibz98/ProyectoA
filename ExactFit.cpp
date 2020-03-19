#include<iostream>
#include <vector>
#include<map>
using namespace std;



int miss = 0;
int hit = 0;



int hash (int i,int mida){
  
  return i%mida;
  
  
}


void insert(vector<map<int,bool> > &Tabla, int i){
  
    int midav = Tabla.size();
    
    int key = hash(i,midav);
    
    if(Tabla[key].empty()) ++hit;
    else ++miss;
    
    Tabla[key].insert ( pair<int,bool>(i,true));

}
  
  

void search(vector<map<int,bool> > &Tabla, int paraula){
  
  int midav = Tabla.size();
  
  int key = hash(paraula,midav);
  
  if(Tabla[key].empty()) cout << "NO es troba a la taula" << endl;
  
  else{
    
    if(Tabla[key][paraula]) cout << "El element es troba a la taula" << endl;
    else cout << "NO es troba a la taula" << endl;
    
    
    
  }
  
}




int main(){  
  
  int Tmida;
  cin >> Tmida;
  
  vector<map<int,bool> > Tabla(Tmida);
  
  
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
  
  
  cout << "miss: " << miss << endl;
  cout << "hit: " << hit << endl;
  
}