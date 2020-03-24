#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cmath>

using namespace std;

vector<int> hashTable;
int size;
int colisionsInsert, colisionsSearch, totalInsert, totalSearch;
int hit, miss;
float ocupacion;


void initHashTable(){
  hashTable.resize(size, 0);
}

int myXOR(int x, int y){
    int res = 0;
    for (int j = 31; j>=0; j--){
        bool b1 = x & (1<<j);
        bool b2 = y & (1<<j);

        bool xoredBit = (b1&b2) ? 0 : (b1|b2);

        res <<= 1;
        res |= xoredBit;
    }
    return res;
}

//Hashing Function Jenkins
int Jenkins(int key){
    int i=0;
    double pos = 0;
    while(i != size){
        pos += (key / (int)(pow(2.0, i)) )%2;
        pos += pos * pow(2.0, 10.0);
        pos = myXOR(pos, pos / pow(2,6));
        i++;
    }
    pos += pos * pow(2,3);
    pos = myXOR(pos, pos / pow(2,11));
    pos += pos * pow(2,15);
    return pos;
}

int HashFunction(int key){
  //Get position from AUXILIAR hash function
  return Jenkins(key);
}

//FUNCIÓN DE INSERCIÓN - Inserta en la tabla el conjunto clave-valor que se pasa como parámetro según la descripción del hashing de "Linear Probing"
void insert(int key){
  totalInsert++;
  int position = HashFunction(key);
  for(int i = 0; i < size; ++i){
    if(hashTable[(position + i)%size] == 0){
      hashTable[(position + i)%size] = key;
      hit++;
      ocupacion += 1.0 / size;
      return;
    } else colisionsInsert++; miss++;
  }
  return;
}

//FUNCIÓN DE BÚSQUEDA - Devuelve el valor asociado a la clave que se pasa como parámetro, o 0 si esta clave no aparece en la tabla.
int search(int key){
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

//FUNCIÓN DE INSTRUCCIONES - Muestra por la salida estándar las Instrucciones para el correcto uso del programa.
void instrucciones(){
  cout << "GUÍA PARA EL USO DE LINEAR PROBING" << endl;
  cout << "En primer lugar introduzca el tamaño de la tabla que desea crear" << endl;
  cout << "A continuacion las claves que se quieren insertar finalizando con un '0'" << endl;
  cout << "Finalmente las claves que se desea buscar en la tabla, finalizando con un '0'" << endl;
  cout << "Las claves deben ser enteros mayores que 0" << endl;
}

void stats() {
    cout << "Linear Probing" << endl;
    cout << "Colisions Insert " << colisionsInsert << endl;
    cout << "Colisions Search " << colisionsSearch << endl;
    cout << "Colisions Totals " <<  colisionsInsert + colisionsSearch << endl;

    cout << "Total Insert " << totalInsert << endl;
    cout << "Total Search " << totalSearch << endl;
    cout << "Total comandes " <<  totalInsert + totalSearch << endl;

    cout << "Hits " << hit << endl;
    cout << "Misses " << miss << endl;
    cout << "Ratio de ocupacion " << ocupacion << endl;
}

//FUNCIÓN DE EJECUCIÓN - Función que lleva a cabo el uso principal del programa.
void ejecucion(){
  cin >> size;
  initHashTable();
  int key;

  //Inserts
  cin >> key;
  while (key != 0){
      insert(key);
      cin >> key;
  }

  //Searches for already inserted keys
  do{
      cin >> key;
      int result = search(key);
  } while (key != 0);


  //Searches for non inserted keys
  do{
      cin >> key;
      int result = search(key);
  } while (key != 0);
  return;
}

int main(){
  //instrucciones();
  colisionsSearch = colisionsInsert = totalInsert = totalSearch = hit = miss = ocupacion = 0;
  ejecucion();
  stats();
}