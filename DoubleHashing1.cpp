#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include <cmath>
using namespace std;

vector<int> hashTable;
int occuped_space;
int size;
int hit_insert;
int miss_insert;

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

//Function that initializate the hash table to the desired size
void initHashTable(){
	hashTable.resize(size, -1);
}

//Function that prints the whole hash table
void print(){
	cout << "Hash Table:" << endl;
	for(int k = 0; k<size; k++){
		cout << " [ " << k << " ] : " << hashTable[k] << endl;
	}
}

//First Hash function
int hash_f1(int key){ // Hash function 1
	return (2*key+3)%size;
}

//Second Hash function
int hash_f2(int key, int j){ // Hash function 2
	return (j*(key))%size;
}

//Hashing Function Jenkins
int jenkins(int key){
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

//Function that given a key search if it is or not in the hash table
bool search(int key){
	return false;
}

//Function that inserts a key into the hash table using double hashing
bool insert(int key){
	if(occuped_space != size){
		int valuef1 = (jenkins(key))%size; // We calculate position given by 1st Hash Function
		if(hashTable[valuef1] != -1){	// Hash position not empty
			miss_insert++;
			int j = 0;
			int valuef2 = hash_f2(key, j); // We calculate position given by 2nd Hash Function
			if(hashTable[valuef2] == key) return true;
			while(hashTable[valuef2] != -1){
				miss_insert++;
				j++;
				valuef2 = hash_f2(key, j);
				cout << "que pasa; " << j << endl;
			}
			//No colition function 2
			if(hashTable[valuef2] == key) return true;
			hashTable[valuef2] = key;
			occuped_space++;
			hit_insert++;
			return true;
		}
		else{ // No colition function 1
			if(hashTable[valuef1] == key) return true;
			hashTable[valuef1] = key;
			occuped_space++;
			hit_insert++;
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
	miss_insert = 0;
	hit_insert = 0;

	initHashTable();

	cout << "Insert Hash values to insert: " << endl;
	int key;
	while(cin >> key){
		bool result = insert(key);
		if(!result) break;
		cout << "insert next:" << endl;
	}

	print();
	cout << "[ Insert ]= HITS: " << hit_insert << " MISSES: " << miss_insert << endl;
}