#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include <cmath>
#include <sstream>
using namespace std;

vector<int> hashTable1;
vector<int> hashTable2;
int occuped_space1;
int occuped_space2;
int size;
int hit_insert;
int miss_insert;
int hit_search;
int miss_search;
int it;

int colisionsInsert;
int colisionsSearch1;
int colisionsSearch2;

int totalInsert;
int totalSearch1;
int totalSearch2;

double ocupacion;

int insert1(int key, int it);

//Function that initializate the hash table to the desired size
void initHashTable(){
	hashTable1.resize(size, -1);
	hashTable2.resize(size, -1);
}

//Function that prints the whole hash table
void print(){
	cout << "Nombre: CuckooHashing" << endl;
    cout << "Colisions Insert: " << colisionsInsert << endl;
    cout << "Colisions Search: " << colisionsSearch1 + colisionsSearch2 << endl;
    cout << "Colisions Totals: " <<  colisionsInsert + colisionsSearch1 + colisionsSearch2 << endl;

    cout << "Total Insert: " << totalInsert << endl;
    cout << "Total Search: " << totalSearch1 + totalSearch2 << endl;
    cout << "Total comandes: " <<  totalInsert + totalSearch1 + totalSearch2 << endl;

    cout << "Ratio de ocupación: " << ocupacion << endl;

    cout << "Media probes teórica: " << 1 << endl;
    cout << "Media probes empírica insertados: " << (colisionsSearch1)/float(totalSearch1) << endl;
    cout << "Media probes empírica no insertados: " << (colisionsSearch2)/float(totalSearch2) << endl;

    return;
}

//First Hash function
int hash_f1(int key){ // Hash function 1
	return (key%503)%size;
}

//Second Hash function
int hash_f2(int key){ // Hash function 1
	return (key)%size;
}

//Function that given a key search if it is or not in the hash tables
//return (1) CORRECT     (2) FULL     (3) CAN'T J>SIZE
bool search(int key, int round){
	int j = 0;
	int valuef1 = hash_f1(key); // We calculate position given by 1st Hash Function
	int valuef2 = hash_f2(key); // We calculate position given by 2nd Hash Function
	if(hashTable1[valuef1] == key || hashTable2[valuef2] == key){
		if (round == 1) colisionsSearch1++;
		else colisionsSearch2++;
		return true;
	}
	else{
		if(round == 1) colisionsSearch1++;
		else colisionsSearch2++;

		return false;
	}
}

//Function that inserts a key into the hash table using CuckooHashing
//return (1) CORRECT     (2) FULL     (3) CAN'T J>SIZE
int insert2(int key, int it){
	if(it == (2*size)) return 3; //Can't insert key in either HashTable
	if(occuped_space2 != size){
		int valuef2 = hash_f2(key)%size; // We calculate position given by 1st Hash Function
		if(hashTable2[valuef2] != -1){ // If hashTable1 pos occuped
			if(hashTable2[valuef2] == key){	//if we find the same key we wanted to insert
				colisionsInsert++;
				return 1;	//Key ya colocada
			}
			colisionsInsert++;
			int oldkey = hashTable2[valuef2]; // Save old key in that pos
			hashTable2[valuef2] = key; //Put new key in place
			it++; //we increase iterator to break infinite loops
			int x = insert1(oldkey, it); //We then try to insert oldkey in HashTable2
			return x;
		}
		colisionsInsert++;
		occuped_space2++;
		//cout << "inserto key: " << key << " en tabla 2 pos: " << valuef2 << endl;
		hashTable2[valuef2] = key;
		return 1;	//Key colocada en posicion LIBRE
	}
	return 2; //One Table is Full
}

//Function that inserts a key into the hash table using CuckooHashing
//return (1) CORRECT     (2) FULL     (3) CAN'T J>SIZE
int insert1(int key, int it){
	//cout << "entro en insert1 con key: " << key << " it: " << it << endl;
	if(it == (2*size)) return 3; //Can't insert key in either HashTable
	if(occuped_space1 != size){
		int valuef1 = hash_f1(key); // We calculate position given by 1st Hash Function
		if(hashTable1[valuef1] != -1){ // If hashTable1 pos occuped
			if(hashTable1[valuef1] == key){	//if we find the same key we wanted to insert
				colisionsInsert++;
				return 1;	//Key ya colocada
			}
			colisionsInsert++;
			int oldkey = hashTable1[valuef1]; // Save old key in that pos
			hashTable1[valuef1] = key; //Put new key in place
			it++; //we increase iterator to break infinite loops
			int x = insert2(oldkey, it); //We then try to insert oldkey in HashTable2
			return x;
		}
		colisionsInsert++;
		occuped_space1++;
		hashTable1[valuef1] = key;
		return 1;	//Key colocada en posicion LIBRE
	}
	return 2; //One Table is Full
}

int main(){
	occuped_space1 = 0;
	occuped_space2 = 0;

	totalInsert = 0;
	totalSearch1 = 0;
	totalSearch2 = 0;
	it = 0;
    cin >> size;

	initHashTable();

	int key;
	cin >> key;
	while(key != 0){ //INSERT
		totalInsert++;
		int result = insert1(key, it);
		if(result == 2) { //Hashtable already full
			break;
		}
		cin >> key;
	}

	cin >> key;
	while(key != 0){ //SEARCH 1
		totalSearch1++;
		bool result = search(key, 1);
		cin >> key;
	}

	cin >> key;
	while(key != 0){ //SEARCH 2
		totalSearch2++;
		bool result = search(key, 2);
		cin >> key;
	}

	ocupacion = (occuped_space1+occuped_space2)/double(size*2);

	print(); //PRINT
}