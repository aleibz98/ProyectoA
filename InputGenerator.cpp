#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

/*
 * FUNCIONAMIENTO
 * Se deben insertar 3 enteros:
 *      - La semilla para generar los números aleatorios
 *      - El tamaño de la tabla
 *      - El ratio de ocupación deseado (en tanto por ciento, es decir, 1 < ratio < 100;
 *
 * El programa genera una linea de 'size' números naturales aleatorios terminada en 0;
 * y una segunda linea de 'size'/3 números que han sido printados en la linea anterior, finalizada también en 0.
 */


int main(){
    int seed,size;
    double ratio;
    cin >> seed >> size >> ratio;
    ratio = ratio / 100;
    vector<int> keys = vector<int> (int(size*ratio),-1);

    //print size
    cout << size << endl;

    //print inserts
    for(int i = 0; i < int(size * ratio); ++i){
        int a = rand();
        cout << a << " ";
        keys[i] = a;
    }

    //print separator insert-search
    cout << "0" << endl;

    //print searches previously inserted
    for(int i = 0; i < 2 * int(size * ratio); ++i){
        int a = rand() % int(size*ratio);
        cout << keys[a] << " ";
    }

    //print separator
    cout << "0" << endl;

    //print searches not inserted
    for(int i = 0; i < 2 * int(size*ratio); ++i) {
        cout << rand() << " ";
    }

    //print end of file
    cout << "0" << endl;
}