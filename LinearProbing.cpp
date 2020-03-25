#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cmath>

using namespace std;

vector<int> hashTable;
int size;
int colisionsInsert, colisionsSearch1, colisionsSearch2, totalInsert, totalSearch1, totalSearch2;
float ocupacion;


void initHashTable(){
  hashTable.resize(size, 0);
}
/*
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
*/
int HashFunction(int key){
  //Get position from AUXILIAR hash function
  //return Jenkins(key);
  return key%size;
}

//FUNCIÓN DE INSERCIÓN - Inserta en la tabla el conjunto clave-valor que se pasa como parámetro según la descripción del hashing de "Linear Probing"
void insert(int key){
  totalInsert++;
  int position = HashFunction(key);
  for(int i = 0; i < size; ++i){
    if(hashTable[(position + i)%size] == 0) {
        hashTable[(position + i) % size] = key;
        ocupacion += 1.0 / size;
        return;
    } else if (hashTable[(position + i) % size] == key){
        return;
    } else {
        colisionsInsert++;
    }
  }
  return;
}

//FUNCIÓN DE BÚSQUEDA - Devuelve el valor asociado a la clave que se pasa como parámetro, o 0 si esta clave no aparece en la tabla.
int search(int key, int &colisionsSearch, int &totalSearch){
  totalSearch++;
  int position = HashFunction(key);
  for(int i = 0; i < size; ++i){
    if(hashTable[(position + i)%size] == key){
      colisionsSearch++;
      return hashTable[(position + i)%size];
    } else if (hashTable[(position + i)%size] == 0){
         return 0;
    } else {
        colisionsSearch++;
    }
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
    cout << "Nombre: LinearProbing" << endl;
    /*
    cout << "Colisions Insert: " << colisionsInsert << endl;
    cout << "Colisions Search: " << colisionsSearch1 + colisionsSearch2 << endl;
    cout << "Colisions Totals: " <<  colisionsInsert + colisionsSearch1 + colisionsSearch2 << endl;

    cout << "Total Insert: " << totalInsert << endl;
    cout << "Total Search: " << totalSearch1 + totalSearch2 << endl;
    cout << "Total comandes: " <<  totalInsert + totalSearch1 + totalSearch2 << endl;
    */
    cout << "Ratio de ocupación: " << ocupacion << endl;

    cout << "Media probes teórica: " << 0.5 * (1 + 1/(1-ocupacion))  << endl;
    cout << "Media probes empírica insertados: " << (colisionsSearch1)/float(totalSearch1) << endl;
    cout << "Media probes empírica no insertados: " << (colisionsSearch2)/float(totalSearch2) << endl;

    return;
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
      int result = search(key, colisionsSearch1, totalSearch1);
  } while (key != 0);


  //Searches for non inserted keys
  do{
      cin >> key;
      int result = search(key, colisionsSearch2, totalSearch2);
  } while (key != 0);
  return;
}

int main(){
  //instrucciones();
  colisionsSearch1 = colisionsSearch2 = colisionsInsert = totalInsert = totalSearch1 = totalSearch2 = ocupacion = 0;
  ejecucion();
  stats();
}