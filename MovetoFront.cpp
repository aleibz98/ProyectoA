#include<iostream>
#include <vector>
#include<list>
using namespace std;


int miss = 0;
int hit = 0;



int hash (int i,int mida){
  
  return i%mida;
  
  
}


void insert(vector<list<int> > &Tabla, int i){
  
    int midav = Tabla.size();
    
    int key = hash(i,midav);
    
    if(Tabla[key].empty()) ++hit;
    else ++miss;
    
    Tabla[key].push_back(i);

}
  
  

void search(vector<list<int> > &Tabla, int paraula){
  
  int midav = Tabla.size();
  
  int key = hash(paraula,midav);
  
  
  if(Tabla[key].empty()) cout << "NO es troba a la taula" << endl;
  
  else{
    
    bool trobat = false;
    for (list<int>::iterator it=Tabla[key].begin(); not trobat and it != Tabla[key].end(); ++it){
      if(*it == paraula){
	
	Tabla[key].erase(it);
	Tabla[key].push_front(paraula);
	
	cout << "El element es troba a la taula" << endl;
	trobat = true;
      }
      
    }
    
    if(not trobat) cout << "NO es troba a la taula" << endl;
    
    
    
  }
  
}




int main(){  
  
  int Tmida;
  cin >> Tmida;
  
  vector<list<int> > Tabla(Tmida);
  
  
  
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
  
    
  
  
  