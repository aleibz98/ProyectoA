#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cmath>

using namespace std;

vector<int> hashTable;
int size;
float c1, c2;
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

//FUNCIÓN DE INSERCIÓN - Inserta en la tabla el conjunto clave-valor que se pasa como parámetro según la descripción del hashing de "Quadratic Probing"
void insert(int key){
  totalInsert++;
  int position = HashFunction(key);
  for(int i = 0; i < size; ++i){
    int access = position + c1*i + c2*i*i;
    if(hashTable[access%size] == 0) {
        hashTable[access % size] = key;
        ocupacion += 1.0 / size;
        return;
    } else if (hashTable[access % size] == key){
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
    int access = position + c1*i + c2*i*i;
    if(hashTable[access%size] == key){
      colisionsSearch++;
      return hashTable[access%size];
    } else if(hashTable[access%size] == 0) {
        return 0;
    }else{
        colisionsSearch++;
    }
  }
  return 0;
}

//FUNCIÓN DE INSTRUCCIONES - Muestra por la salida estándar las Instrucciones para el correcto uso del programa.
void instrucciones() {
    cout << "GUÍA PARA EL USO DE LINEAR PROBING" << endl;
    cout << "En primer lugar introduzca el tamaño de la tabla que desea crear" << endl;
    cout << "A continuacion las claves que se quieren insertar finalizando con un '0'" << endl;
    cout << "Finalmente las claves que se desea buscar en la tabla, finalizando con un '0'" << endl;
    cout << "Las claves deben ser enteros mayores que 0" << endl;
}

void stats() {
    cout << "Quadratic Probing" << endl;
    cout << "c1 " << c1 << endl;
    cout << "c2 " << c2 << endl;
    cout << "Colisions Insert " << colisionsInsert << endl;
    cout << "Colisions Search " << colisionsSearch1 + colisionsSearch2 << endl;
    cout << "Colisions Totals " << colisionsInsert + colisionsSearch1 + colisionsSearch2 << endl;

    cout << "Total Inserts " << totalInsert << endl;
    cout << "Total Searches " << totalSearch1 + totalSearch2 << endl;
    cout << "Total comandes " << totalInsert + totalSearch1 + totalSearch2 << endl;

    cout << "Ratio de ocupación " << ocupacion << endl;

    cout << "Media probes teórica: " << 1 - log(1-ocupacion) - ocupacion/2 << endl;
    cout << "Media probes empírica insertados: " << (colisionsSearch1)/float(totalSearch1) << endl;
    cout << "Media probes empírica no insertados: " << (colisionsSearch2)/float(totalSearch2) << endl;

    return;
}

int findNext2Pot(int i){
    //Feísimo el cálculo, pero funciona :)
    int ret = int(pow(2.0,float(int(log(i)/log(2.0)+1))));
    return ret;
}


//FUNCIÓN DE EJECUCIÓN - Función que lleva a cabo el uso principal del programa.
void ejecucion(){
    int i;
    cin >> i;
    size = findNext2Pot(i);
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
      c1 = 0.5;
      c2 = 0.5;
      colisionsSearch1 = colisionsSearch2 = colisionsInsert = totalInsert = totalSearch1 = totalSearch2 = ocupacion = 0;
      ejecucion();
      stats();
}

//TODO ¿Por qué varía el ratio de ocupación cuando modificamos las dos constantes c1 y c2?