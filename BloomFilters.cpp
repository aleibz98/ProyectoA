//
// Created by Alejandro Alarcon on 19/03/2020.
//

#include <iostream>

using namespace std;

vector <bool> filter;
int size;
float falsePositive;

int hashFunction1(int key){
    //returns the index of the bit to be changed by the hashFunction

}

int hashFunction2(int key){
    //returns the index of the bit to be changed by the hashFunction

}

int hashFunction3(int key){
    //returns the index of the bit to be changed by the hashFunction

}

void insertKey(int key){
    int h1 = hashFunction1(key), h2 = hashFunction2(key), h3 = hashFunction3(key);
    filter[h1] = true;
    filter[h2] = true;
    filter[h3] = true;
}

bool checkKey(int key){
    //Checks if the key had been introduced
    int h1 = hashFunction1(key), h2 = hashFunction2(key), h3 = hashFunction3(key);
    if(filter[h1] && filter[h2] && filter[h3]) return true;
    else return false;
}

void stats(){
    //Prints the stats for the execution
}

int main(){
    cin >> size;

    //Initialization of the filter
    filter.resize(size, false);

    //Inserts
    cin >> key;
    while(key != 0){
        insertKey(key);
        cin >> key;
    k

    //Searches
    do{
        cin >> key;
        bool result = checkKey(key);
    } while(key != 0);

    stats();
}