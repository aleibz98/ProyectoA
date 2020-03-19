#include <vector>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

vector<int> hashTable;
int occuped_space;
int size;
int colitions;

//Function that initializate the hash table to the desired size
void initHashTable(){
	hashTable.resize(size, -1);
}

//Function that prints the whole hash table
void print(){
	cout << "Hash Table:" << endl;
	for(int k = 0; k<size; k++){
		cout << "[ " << k << " ] : " << hashTable[k] << endl;
	}
}

//First Hash function
int hash_f1(int key){ // Hash function 1
	return (2*key+3)%size;
}

//Second Hash function
int hash_f2(int key, int j){ // Hash function 2
	return (j*(7-key*2))%size;
}

//Function that inserts a key into the hash table using double hashing
bool insert(int key){
	if(occuped_space != size){
		int valuef1 = hash_f1(key); // We calculate position given by 1st Hash Function
		if(hashTable[valuef1] != -1){	// Hash position not empty
			colitions++;
			int j = 0;
			int valuef2 = hash_f2(key, j); // We calculate position given by 2nd Hash Function
			if(hashTable[valuef2] == key) return true;
			while(hashTable[valuef2] != -1){
				colitions++;
				j++;
				valuef2 = hash_f2(key, j);
				cout << "que pasa; " << j << endl;
			}
			//No colition function 2
			if(hashTable[valuef2] == key) return true;
			hashTable[valuef2] = key;
			occuped_space++;
			return true;
		}
		else{ // No colition function 1
			if(hashTable[valuef1] == key) return true;
			hashTable[valuef1] = key;
			occuped_space++;
			return true;
		}
		if(hashTable[valuef1] == key) return true;
	}
	return false;
}

int main(){
	cout << "Insert Hash size: " << endl;
	cin >> size;
	occuped_space = 0;
	colitions = 0;

	initHashTable();

	cout << "Insert Hash values to insert: " << endl;
	int key;
	while(cin >> key){
		bool result = insert(key);
		if(!result) break;
		cout << "insert next:" << endl;
	}

	print();
	cout << "Number of Insert Colitions = " << colitions << endl;
}
