#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

int main(){
    int seed, size;
    vector<int> keys = vector<int> (size);
    cin >> seed >> size;
    for(int i = 0; i < size; ++i){
        int a = rand();
        cout << a << " ";
        keys[i] = a;
    }
    cout << "0" << endl;
    for(int i = 0; i < size / 3; ++i){
        int a = rand() % size;
        cout << keys[a] << " ";
    }
    cout << "0" << endl;
}