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

int colisionsInsert;
int colisionsSearch1;
int colisionsSearch2;

int totalInsert;
int totalSearch1;
int totalSearch2;

double ocupacion;

//Function that initializate the hash table to the desired size
void initHashTable(){
	hashTable.resize(size, -1);
}

//Function that prints the whole hash table
void print(){
	cout << "Nombre: DoubleHashing" << endl;
    /*
	cout << "Colisions Insert: " << colisionsInsert << endl;
    cout << "Colisions Search: " << colisionsSearch1 + colisionsSearch2 << endl;
    cout << "Colisions Totals: " <<  colisionsInsert + colisionsSearch1 + colisionsSearch2 << endl;
    cout << "Total Insert: " << totalInsert << endl;
    cout << "Total Search: " << totalSearch1 + totalSearch2 << endl;
    cout << "Total comandes: " <<  totalInsert + totalSearch1 + totalSearch2 << endl;
	*/
    cout << "Ratio de ocupación: " << ocupacion << endl;

    cout << "Media probes teórica: " << -(1/ocupacion)*log(1-ocupacion)  << endl;
    cout << "Media probes empírica insertados: " << (colisionsSearch1)/float(totalSearch1) << endl;
    cout << "Media probes empírica no insertados: " << (colisionsSearch2)/float(totalSearch2) << endl;

    return;
}

//First Hash function
int hash_f2(int key){ // Hash function 1
	return key%size;
}

//First Hash function
int hash_f1(int key){ // Hash function 1
	return key%509;
}

//Function that given a key search if it is or not in the hash table
//return (1) CORRECT     (2) FULL     (3) CAN'T J>SIZE
bool search(int key, int round){
	int j = 0;
	int valuef1 = hash_f1(key); // We calculate position given by 1st Hash Function
	int valuef2 = hash_f2(key); // We calculate position given by 2nd Hash Function
	int dhval = (valuef1+(valuef2*j))%size; //Double hashing value j=0
	while(hashTable[dhval] != key and hashTable[dhval] !=  -1){	// Hash position not empty
		if(j == size) return false;	//if j too big return "can't insert"
		if(round == 1) miss_search1++;
		else miss_search2++;
		j++;
		dhval = (valuef1+(valuef2*j))%size;
		//cout << "bucle; " << j << "val f1: " << valuef1 << " val f2: " << valuef2 << endl;
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
		int valuef2 = hash_f2(key); // We calculate position given by 2nd Hash Function
		int dhval = (valuef1+valuef2*j)%size; //Double hashing value j=0
		while(hashTable[dhval] != -1){	// Hash position not empty
			if(j == size) return 3;	//if j too big return "can't insert"
			if(hashTable[dhval] == key){	//if we find the same key we wanted to insert
				hit_insert++;
				return 1;
			}
			miss_insert++;
			j++;
			dhval = (valuef1+(valuef2*j))%size;
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
	cin >> size;
	occuped_space = 0;
	miss_insert = 0;
	hit_insert = 0;
	miss_search1 = 0;
	hit_search1 = 0;
	miss_search2 = 0;
	hit_search2 = 0;
	totalInsert = 0;
	totalSearch1 = 0;
	totalSearch2 = 0;

	initHashTable();

	int key;
	cin >> key;
	while(key != 0){ //INSERT
		totalInsert++;
		int result = insert(key);
		if(result == 2) { //Hashtable already full
			break;
		}
		cin >> key;
	}
	//cout << "Search1: (! End with a 0)" << endl;
	cin >> key;
	while(key != 0){ //SEARCH 1
		totalSearch1++;
		bool result = search(key,1);
		cin >> key;
	}
	cin >> key;
	while(key != 0){ //SEARCH 2
		totalSearch2++;
		bool result = search(key,2);
		cin >> key;
	}
	colisionsInsert = miss_insert+hit_insert;
	colisionsSearch1 = miss_search1+hit_search1;
	colisionsSearch2 = miss_search2+hit_search2;
	ocupacion = occuped_space/double(size);

	print(); //PRINT
}