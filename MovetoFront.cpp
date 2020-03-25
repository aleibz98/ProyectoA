#include<iostream>
#include <vector>
#include<list>
using namespace std;



  int cinsert = 0;
  int csearch1= 0, csearch2 = 0;
  int tinsert= 0;
  int tsearch1= 0, tsearch2= 0; 



int hash (int i,int mida){
  
  return i%mida;
  
  
}


void insert(vector<list<int> > &Tabla, int i){
  
    int midav = Tabla.size();
    
    int key = hash(i,midav);
    
    if(Tabla[key].empty()) ++cinsert;
    
    Tabla[key].push_back(i);

}
  
  

void search1(vector<list<int> > &Tabla, int paraula){
  
  int midav = Tabla.size();
  
  int key = hash(paraula,midav);
  
  
  if(Tabla[key].empty()) ++csearch1;
  
  else{
    
    bool trobat = false;
    for (list<int>::iterator it=Tabla[key].begin(); not trobat and it != Tabla[key].end(); ++it){
      ++csearch1;
      if(*it == paraula){
	
	Tabla[key].erase(it);
	Tabla[key].push_front(paraula);
	
	
	trobat = true;
      }
      
    }
    
    
    
    
    
  }
  
}





void search2(vector<list<int> > &Tabla, int paraula){
  
  int midav = Tabla.size();
  
  int key = hash(paraula,midav);
  
  
  if(Tabla[key].empty()) ++csearch2;
  
  else{
    
    bool trobat = false;
    for (list<int>::iterator it=Tabla[key].begin(); not trobat and it != Tabla[key].end(); ++it){
      ++csearch2;
      if(*it == paraula){
	
	Tabla[key].erase(it);
	Tabla[key].push_front(paraula);
	
	trobat = true;
      }
      
    }
    
    
    
    
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
    ++tinsert;
    
  }
  
  cin >> key;
  ++tsearch1;
  while(key != 0){
    search1(Tabla,key);
    cin >> key;
    ++tsearch1;
    
  }
  
  cin >> key;
  ++tsearch2;
  while(key != 0){
    search2(Tabla,key);
    cin >> key;
    ++tsearch2;
  }
  int tocupacion = 0;
  for(int i = 0; i < Tmida; ++i){
    
    if(not Tabla[i].empty())++tocupacion;
    
  }
  
  double rocupacion = (double) tocupacion / (double)Tmida;
  
  cout << "Nombre: MovetoFront"<< endl;
  cout << "Colisions Insert:" << cinsert << endl;
  cout << "Colisions Search:" << csearch1+csearch2 << endl;
  cout << "Colisions Totals:" << cinsert+csearch1+csearch2  << endl;
  cout << "Total Insert:" << tinsert << endl;
  cout << "Total Search:" << tsearch1+tsearch2  << endl;
  cout << "Total Comandes:" << tinsert + tsearch1+tsearch2  << endl;
  cout << "Ratio de ocupacion contenedor principal:" << rocupacion << endl;
  cout << "Media probes empírica insertados:" << (double)csearch1/(double)tsearch1 << endl;
  cout << "Media probes empírica no insertados:" << (double)csearch2/(double)tsearch2 << endl;
  
}
  
    
