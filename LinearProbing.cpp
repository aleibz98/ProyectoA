#include <iostream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

vector<int> hashTable;
int size;
int colisionsInsert, colisionsSearch, colisionsErase, totalInsert, totalSearch, totalErase;
int hit, miss;
float ocupacion;


void initHashTable(){
  hashTable.resize(size, 0);
}

int HashFunction(int key){
  //Get position from AUXILIAR hash function
  //Shall we use MD5 or SHA?
  return key%size;
}

//FUNCIÓN DE INSERCIÓN - Inserta en la tabla el conjunto clave-valor que se pasa como parámetro según la descripción del hashing de "Linear Probing"
bool insert(int key){
  totalInsert++;
  int position = HashFunction(key);
  for(int i = 0; i < size; ++i){
    if(hashTable[(position + i)%size] == 0){
      hashTable[(position + i)%size] = key;
      hit++;
      ocupacion += 1 / size;
      return true;
    } else colisionsInsert++; miss++;
  }
  return false;
}

//FUNCIÓN DE BÚSQUEDA - Devuelve el valor asociado a la clave que se pasa como parámetro, o 0 si esta clave no aparece en la tabla.
double search(int key){
  totalSearch++;
  int position = HashFunction(key);
  for(int i = 0; i < size; ++i){
    if(hashTable[(position + i)%size] == key){
      hit++;
      return hashTable[(position + i)%size];
    } else colisionsSearch++; miss++;
  }
  return 0;
}

//FUNCIÓN DE ELIMINACIÓN - Elimina la clave y su valor asociado en la tabla y retorna TRUE. Si no se puede encontrar la clave retorna FALSO.
bool erase(int key){
  totalErase++;
  int position = HashFunction(key);
  for(int i = 0; i < size; ++i){
    if(hashTable[(position + i)%size] == key){
      hashTable[position] = 0;
      hit++;
      ocupacion -= 1 / size;
      return true;
    } else colisionsErase++; miss++;
  }
  return false;
}

//FUNCIÓN DE INSTRUCCIONES - Muestra por la salida estándar las Instrucciones para el correcto uso del programa.
void instrucciones(){
  cout << "GUÍA PARA EL USO DE LINEAR PROBING" << endl;
  cout << "En primer lugar introduzca el tamaño de la tabla que desea crear" << endl;
  cout << "A continuacion las claves que se quieren insertar finalizando con un '0'" << endl;
  cout << "Finalmente las claves que se desea buscar en la tabla, finalizando con un '0'" << endl;
  cout << "Las claves deben ser enteros mayores que 0" << endl;
}

void stats() {
    cout << "Colisions Insert: " << colisionsInsert << endl;
    cout << "Colisions Search: " << colisionsSearch << endl;
    cout << "Colisions Erase: " << colisionsErase << endl;
    cout << "Colisions Totals: " << colisionsErase + colisionsInsert + colisionsSearch << endl;

    cout << "Total Insert: " << totalInsert << endl;
    cout << "Total Search: " << totalSearch << endl;
    cout << "Total Erase: " << totalErase << endl;
    cout << "Total comandes: " << totalErase + totalInsert + totalSearch << endl;

    cout << "Hits: " << hit << endl;
    cout << "Misses: " << miss << endl;
    cout << "Ratio de ocupacion: " << ocupacion << endl;
}

//FUNCIÓN DE EJECUCIÓN - Función que lleva a cabo el uso principal del programa.
void ejecucion(){
  //cout << "Introduzca el tamaño de la tabla" << endl;
  cin >> size;
  initHashTable();
  int key;
  cin >> key;
  while (key != 0){
    bool result = insert(key);
    cin >> key;
  }
  do{
      cin >> key;
      int result = search(key);
  } while (key != 0);
  return;
}

int main(){
  //instrucciones();
  colisionsSearch = colisionsErase = colisionsInsert = totalErase = totalInsert = totalSearch = hit = miss = ocupacion = 0;
  ejecucion();
  stats();
}