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
 */
int main(){
    int seed, size, ratio;
    vector<int> keys = vector<int> (size);
    cin >> seed >> size >> ratio;
    cout << size << endl;
    for(int i = 0; i < size * ratio/100; ++i){
        int a = rand();
        cout << a << " ";
        keys[i] = a;
    }
    cout << "0" << endl;
    for(int i = 0; i < size * ratio/100 / 3; ++i){
        int a = rand() % size;
        cout << keys[a] << " ";
    }
    cout << "0" << endl;
}