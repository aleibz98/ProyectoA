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
int hit_search1;
int miss_search1;
int hit_search2;
int miss_search2;

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
	cout << "::::::::::::::::::::::::::::::" << endl;
	cout << "Hash Table:" << endl;
	for(int k = 0; k<size; k++){
		cout << " [ " << k << " ] : " << hashTable[k] << endl;
	}

	cout << "::::::::::::::::::::::::::::::" << endl;
	//HITS & MISSES
	cout << "[INSERT]= HITS: " << hit_insert << " MISSES: " << miss_insert << endl;
	cout << "[SEARCH1]= HITS: " << hit_search1 << " MISSES: " << miss_search1 << endl;
	cout << "[SEARCH2]= HITS: " << hit_search2 << " MISSES: " << miss_search2 << endl;
	cout << "[SEARCH TOTAL]= HITS: " << hit_search1+hit_search2 << " MISSES: " << miss_search1+miss_search2 << endl;	
	cout << "[TOTAL]= HITS: " << hit_insert+hit_search1+hit_search2 << " MISSES: " << miss_insert+miss_search1+miss_search2 << endl;

	//OCCUPED SPACE
	cout << "[OCCUPED_SPACE]= " << occuped_space << endl;
}

//First Hash function
int hash_f1(int key){ // Hash function 1
	return key;
}

//Hashing Function Jenkins one at a time
int joaat(int key){
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
}

//Function that given a key search if it is or not in the hash table
//return (1) CORRECT     (2) FULL     (3) CAN'T J>SIZE
bool search(int key, int round){
	int j = 0;
	int valuef1 = hash_f1(key); // We calculate position given by 1st Hash Function
	int valuef2 = joaat(key); // We calculate position given by 2nd Hash Function
	int dhval = (valuef1+valuef2*j)%size; //Double hashing value j=0
	while(hashTable[dhval] != key){	// Hash position not empty
		if(j == size) return false;	//if j too big return "can't insert"
		if(round == 1) miss_search1++;
		else miss_search2++;
		j++;
		dhval = (valuef1+valuef2*j);
		cout << "bucle; " << j << "val f1: " << valuef1 << " val f2: " << valuef2 << endl;
	}
	//Found an empty position
	if(round == 1) hit_search1++;
	else hit_search2++;
	return true;
}

//Function that inserts a key into the hash table using double hashing
//return (1) CORRECT     (2) FULL     (3) CAN'T J>SIZE
int insert(int key){
	if(occuped_space != size){
		int j = 0;
		int valuef1 = hash_f1(key); // We calculate position given by 1st Hash Function
		int valuef2 = joaat(key); // We calculate position given by 2nd Hash Function
		int dhval = (valuef1+valuef2*j)%size; //Double hashing value j=0
		while(hashTable[dhval] != -1){	// Hash position not empty
			if(j == size) return 3;	//if j too big return "can't insert"
			if(hashTable[dhval] == key){	//if we find the same key we wanted to insert
				hit_insert++;
				return 1;
			}
			miss_insert++;
			j++;
			dhval = (valuef1+valuef2*j);
			//cout << "bucle; " << j << "val f1: " << valuef1 << " val f2: " << valuef2 << endl;
		}
		//Found an empty position
		hashTable[dhval] = key;
		occuped_space++;
		hit_insert++;
		return 1;
	}
	return 2;
}

int main(){
	cout << "Insert Hash size: " << endl;
	cin >> size;
	occuped_space = 0;
	miss_insert = 0;
	hit_insert = 0;
	miss_search1 = 0;
	hit_search1 = 0;
	miss_search2 = 0;
	hit_search2 = 0;

	initHashTable();

	cout << "Insert Hash values to insert: (! End with a 0)" << endl;
	int key;
	cin >> key;
	while(key != 0){ //INSERT
		int result = insert(key);
		if(result == 2) { //Hashtable already full
			cout << "Hash Table is full!" << endl;
			break;
		}
		else if(result == 3) { // Can't insert that value
			cout << "Can't insert " << key << " in the HashTable." << endl;
		}
		cin >> key;
	}
	cout << "Search1: (! End with a 0)" << endl;
	cin >> key;
	while(key != 0){ //SEARCH
		bool result = search(key,1);
		if(!result) cout << "Key NOT found!" << endl;
		else cout << "Key found!" << endl;
		cin >> key;
	}
	cout << "Search2: (! End with a 0)" << endl;
	cin >> key;
	while(key != 0){ //SEARCH
		bool result = search(key,2);
		if(!result) cout << "Key NOT found!" << endl;
		else cout << "Key found!" << endl;
		cin >> key;
	}
	print(); //PRINT
}