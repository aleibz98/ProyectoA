#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include <cmath>
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

int insert1(int key, int it);

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
	hashTable1.resize(size, -1);
	hashTable2.resize(size, -1);
}

//Function that prints the whole hash table
void print(){
	cout << "::::::::::::::::::::::::::::::" << endl;
	cout << " HASH TABLE 1:" << '\t' << '\t' << "HASH TABLE 2:"<< endl;
	for(int k = 0; k<size; k++){
		cout << " [ " << k << " ] : " << hashTable1[k] << '\t' << '\t' << "[ " << k << " ] : " << hashTable2[k] << endl;
	}

	cout << "::::::::::::::::::::::::::::::" << endl;
	//HITS & MISSES
	cout << "[INSERT]= HITS: " << hit_insert << " MISSES: " << miss_insert << endl;
	cout << "[SEARCH]= HITS: " << hit_search << " MISSES: " << miss_search << endl;
	cout << "[TOTAL]= HITS: " << hit_insert+hit_search << " MISSES: " << miss_insert+miss_search << endl;

	//OCCUPED SPACE
	cout << "[OCCUPED_SPACE (HashTable1)]= " << occuped_space1 << "      [OCCUPED_SPACE (HashTable2)]= " << occuped_space2 << endl;
	cout << "[OCCUPED TOTAL]= " << occuped_space1+occuped_space2 << endl;
}

//First Hash function
int hash_f1(int key){ // Hash function 1
	return key;
}

//First Hash function
int hash_f2(int key){ // Hash function 1
	return key+1;
}

//Hashing Function Jenkins one at a time
/*int joaat(int key){
	int i=0;
	double pos = 0;
	while(i != size){
		pos += (key / (int)(pow(2, i)) )%2;
		pos += pos * pow(2.0, 10.0);
		pos = myXOR(pos, pos / pow(2,6));
		i++;
	}
	pos += pos * pow(2,3);
	pos = myXOR(pos, pos / pow(2,11));
	pos += pos * pow(2,15);
	return (int)pos;
}*/

//Function that given a key search if it is or not in the hash table
//return (1) CORRECT     (2) FULL     (3) CAN'T J>SIZE
/*bool search(int key){
	int j = 0;
	int valuef1 = hash_f1(key); // We calculate position given by 1st Hash Function
	int valuef2 = joaat(key); // We calculate position given by 2nd Hash Function
	int dhval = (valuef1+valuef2*j)%size; //Double hashing value j=0
	while(hashTable[dhval] != key){	// Hash position not empty
		if(j == size) return false;	//if j too big return "can't insert"
		miss_search++;
		j++;
		dhval = (valuef1+valuef2*j);
		cout << "bucle; " << j << "val f1: " << valuef1 << " val f2: " << valuef2 << endl;
	}
	//Found an empty position
	hit_search++;
	return true;
}*/

//Function that inserts a key into the hash table using CuckooHashing
//return (1) CORRECT     (2) FULL     (3) CAN'T J>SIZE
int insert2(int key, int it){
	//cout << "entro en insert2 con key: " << key << " it: " << it << endl;
	if(it == (2*size)) return 3; //Can't insert key in either HashTable
	if(occuped_space2 != size){
		int valuef2 = hash_f2(key)%size; // We calculate position given by 1st Hash Function
		if(hashTable2[valuef2] != -1){ // If hashTable1 pos occuped
			if(hashTable2[valuef2] == key){	//if we find the same key we wanted to insert
				hit_insert++;
				return 1;	//Key ya colocada
			}
			miss_insert++;
			int oldkey = hashTable2[valuef2]; // Save old key in that pos
			hashTable2[valuef2] = key; //Put new key in place
			it++; //we increase iterator to break infinite loops
			int x = insert1(oldkey, it); //We then try to insert oldkey in HashTable2
			return x;
		}
		hit_insert++; 
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
		int valuef1 = hash_f1(key)%size; // We calculate position given by 1st Hash Function
		if(hashTable1[valuef1] != -1){ // If hashTable1 pos occuped
			if(hashTable1[valuef1] == key){	//if we find the same key we wanted to insert
				hit_insert++;
				return 1;	//Key ya colocada
			}
			miss_insert++;
			int oldkey = hashTable1[valuef1]; // Save old key in that pos
			hashTable1[valuef1] = key; //Put new key in place
			it++; //we increase iterator to break infinite loops
			int x = insert2(oldkey, it); //We then try to insert oldkey in HashTable2
			return x;
		}
		hit_insert++; 
		occuped_space1++;
		hashTable1[valuef1] = key;
		return 1;	//Key colocada en posicion LIBRE
	}
	return 2; //One Table is Full
}

int main(){
	cout << "Insert Hash size: " << endl;
	cin >> size;
	occuped_space1 = 0;
	occuped_space2 = 0;
	miss_insert = 0;
	hit_insert = 0;
	miss_search = 0;
	hit_search = 0;
	it = 0;

	initHashTable();

	cout << "Insert Hash values to insert: (! End with a 0)" << endl;
	int key;
	cin >> key;
	while(key != 0){ //INSERT
		int result = insert1(key, it);
		if(result == 2) { //Hashtable already full
			cout << "Hash Table is full!" << endl;
			break;
		}
		else if(result == 3) { // Can't insert that value
			cout << "Can't insert " << key << " in the HashTables." << endl;
		}
		cin >> key;
	}
	cout << "Any keys you want to search in the HashTable: (! End with a 0)" << endl;
	cin >> key;
	/*while(key != 0){ //SEARCH
		bool result = search(key);
		if(!result) cout << "Key NOT found!" << endl;
		else cout << "Key found!" << endl;
		cin >> key;
	}*/
	print(); //PRINT
}