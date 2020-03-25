#include<iostream>
#include <vector>
#include<map>
#include<cmath>
using namespace std;


  
  int cinsert = 0;
  double csearch1= 0, csearch2 = 0;
  int tinsert= 0;
  int tsearch1= 0, tsearch2= 0; 
  
  



int hash (int i,int mida){
  
  return i%mida;
  
  
}


void insert(vector<map<int,bool> > &Tabla, int i){
  
    int midav = Tabla.size();
    
    int key = hash(i,midav);
    
    Tabla[key].insert ( pair<int,bool>(i,true));

}
  
  

void search1(vector<map<int,bool> > &Tabla, int paraula){
  
  int midav = Tabla.size();
  
  int key = hash(paraula,midav);
  
  if(not Tabla[key].empty())  csearch1 += log2((double)Tabla[key].size());

  

  //si la tabla esta llena tarda log midamap colisiones en encontrarlo
  
  
}

void search2(vector<map<int,bool> > &Tabla, int paraula){
  
  int midav = Tabla.size();
  
  int key = hash(paraula,midav);
  
 if(not Tabla[key].empty()) csearch2 += log2((double)Tabla[key].size());
  
  
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
  
  cout << "Nombre: ExactFit"<< endl;
  cout << "Colisions Insert:" << cinsert << endl;
  cout << "Colisions Search:" << csearch1+csearch2 << endl;
  cout << "Colisions Totals:" << (double)cinsert+csearch1+csearch2 << endl;
  cout << "Total Insert:" << tinsert << endl;
  cout << "Total Comandes:" << tinsert+tsearch1+tsearch2  << endl;
  cout << "Ratio de ocupacion contenedores:" << rocupacion << endl;
  cout << "Media prueba teórica insertados:" << csearch1/(double)tsearch1 << endl;
  cout << "Media prueba teórica no insertados:" << csearch2/(double)tsearch2 << endl;
  
 
  
}