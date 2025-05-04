// Create hashtable for telephone book db and search for data in it.
// We will use linearprobing and chaining here.
// LinearProbing is done via looking for the next empty slot
// For chaining we'll use a linked list (list<>)

#include <bits/stdc++.h>
using namespace std;


const int TABLE_SIZE = 30;

struct client{
	string name;
	long long num;
};

int hashFunc(long long num){
	return num % TABLE_SIZE;
}


class HashTableLinear{
	vector<client> table;
	vector<bool> taken;

	public:
	int comparisons = 0;
	HashTableLinear(){
		table.resize(TABLE_SIZE);
		taken.assign(TABLE_SIZE, false);
	}

	void insert(string name, long long num){
		int ind = hashFunc(num);
		int start = ind;

		while(taken[ind]){
			ind = (ind + 1)%TABLE_SIZE;
			if(ind == start){
				cout<<"Table is full!\n";
				return;
			}
		}
		table[ind] = {name, num};
		start = ind;
	}

	bool search(long long num){
		int ind = hashFunc(num);
		int start = ind;

		while(taken[ind]){
			++comparisons;
			if(table[ind].num == num){
				return true;
			}
			ind = (ind + 1)%TABLE_SIZE;
			if(ind == start)return false;

		}

		return false;

	}

};



class HashTableChain{
	vector<list<client>> table;
	public:
	int comparisons = 0;

	HashTableChain(){
		table.resize(TABLE_SIZE);
	}

	void insert(string name, long long num){
		int ind = hashFunc(num);
		table[ind].push_back({name, num});
	}

	bool search(long long num){
		int ind = hashFunc(num);
		for(auto &client : table[ind]){
			++comparisons;
			if(client.num == num)return true;
		}

		return false;
	}

};



int32_t main(){

	return 0;
}


