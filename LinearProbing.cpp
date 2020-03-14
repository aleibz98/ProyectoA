#include <iostream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

vector<pair <int, double> > hashTable;
int size;
int colisionsInsert, colisionsSearch, colisionsErase, totalInsert, totalSearch, totalErase;


void initHashTable(){
  hashTable.resize(size, make_pair(0,0));
}

int HashFunction(int key){
  //Get position from AUXILIAR hash function
  //Shall we use MD5 or SHA?
  return key%size;
}

//FUNCIÓN DE INSERCIÓN - Inserta en la tabla el conjunto clave-valor que se pasa como parámetro según la descripción del hashing de "Linear Probing"
bool insert(int key, double value){
  totalInsert++;
  int position = HashFunction(key);
  for(int i = 0; i < size; ++i){
    if(hashTable[(position + i)%size].first == 0){
      hashTable[(position + i)%size].second = value;
      hashTable[(position + i)%size].first = key;
      return true;
    } else colisionsInsert++;
  }
  return false;
}

//FUNCIÓN DE BÚSQUEDA - Devuelve el valor asociado a la clave que se pasa como parámetro, o 0 si esta clave no aparece en la tabla.
double search(int key){
  totalSearch++;
  int position = HashFunction(key);
  for(int i = 0; i < size; ++i){
    if(hashTable[(position + i)%size].first == key){
      return hashTable[(position + i)%size].second;
    } else colisionsSearch++;
  }
  return 0;
}

//FUNCIÓN DE ELIMINACIÓN - Elimina la clave y su valor asociado en la tabla y retorna TRUE. Si no se puede encontrar la clave retorna FALSO.
bool erase(int key){
  totalErase++;
  int position = HashFunction(key);
  for(int i = 0; i < size; ++i){
    if(hashTable[(position + i)%size].first == key){
      hashTable[position].first = 0;
      hashTable[position].second = 0;
      return true;
    } else colisionsErase++;
  }
  return false;
}

//FUNCIÓN DE INSTRUCCIONES - Muestra por la salida estándar las Instrucciones para el correcto uso del programa.
void instrucciones(){
  cout << "GUÍA PARA EL USO DE LINEAR PROBING" << endl;
  cout << "En primer lugar introduzca el tamaño de la tabla que desea crear" << endl;
  cout << "Las claves deben ser enteros mayores que 0" << endl;
  cout << "Para insertar, introduzca 1 seguido de la clave y el valor." << endl;
  cout << "Para buscar, introduzca 2 seguido de la clave" << endl;
  cout << "Para eliminar, introduzca 3 seguido de la clave" << endl;
  cout << "Para mostrar todos los huecos ocupados de la tabla con su correspondiente clave-valor, introduzca 4" << endl;
}

//FUNCIÓN DE EJECUCIÓN - Función que lleva a cabo el uso principal del programa.
void ejecucion(){
  //cout << "Introduzca el tamaño de la tabla" << endl;
  cin >> size;
  initHashTable();
  int comando;
  //cout << "Inserte caso" << endl;
  while (cin >> comando){
    switch (comando){
      case 1:{
        int key;
        double value;
        cin >> key >> value;
        bool result = insert(key,value);
        //cout << (result) ? "OK" : "Error en la inserción";
        //cout << result;
        //cout << endl;
        break;
      }
      case 2:{
        int key;
        cin >> key;
        double result = search(key);
        //cout << (result != 0) ? to_string(result) : "Not Found";
        //cout << result;
        //cout << endl;
        break;
      }
      case 3:{
        int key;
        cin >> key;
        bool result = erase(key);
        //cout << result;
        //cout << "OK" << endl;
        break;
      }
      case 4:{
        for(int i = 0; i < size; ++i){
          if(hashTable[i].first != 0) cout << i << " " << hashTable[i].first << " " << hashTable[i].second << endl;
          break;
        }
      }
      default: cout << "Comando erróneo" << endl;
    }
    //cout << "Inserte caso" << endl;
  }
}

int main(){
  //instrucciones();
  colisionsSearch = colisionsErase = colisionsInsert = totalErase = totalInsert = totalSearch = 0;
  ejecucion();

  /*
  cout << "Colisions Insert: " << colisionsInsert << endl;
  cout << "Colisions Search: " << colisionsSearch << endl;
  cout << "Colisions Erase: " << colisionsErase << endl;
  cout << "Colisions Totals: " << colisionsErase + colisionsInsert + colisionsSearch << endl;

  cout << "Total Insert: " << totalInsert << endl;
  cout << "Total Search: " << totalSearch << endl;
  cout << "Total Erase: " << totalErase << endl;
  cout << "Total comandes: " << totalErase + totalInsert + totalSearch << endl;
  */
}
