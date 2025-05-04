// Create hashtable for telephone book db and search for data in it.
// We will use linearprobing and chaining here.
// LinearProbing is done via looking for the next empty slot
// For chaining we'll use a linked list (list<>)

#include <bits/stdc++.h>
using namespace std;

const int TABLE_SIZE = 20;

struct client{
	string name;
	long long number;
};

int hashFunc(long long n){
	return n % TABLE_SIZE;
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

	void insert(string name, long long number){
		int ind = hashFunc(number);
		int start = ind;

		while(taken[ind]){
			ind = (ind + 1)%TABLE_SIZE;
			if(ind == start){
				cout<<"Table is full!\n";
				return;
			}
		}
		table[ind] = {name, number};
		taken[ind] = true;
	}

	bool search(long long number){
		int ind = hashFunc(number);
		int start = ind;

		while(taken[ind]){
			++comparisons;
			if(table[ind].number == number){
				return true;
			}
			ind = (ind + 1)%TABLE_SIZE;
			if(ind == start)return false;
		}
		return false;
	}

	void display(){
		for(int i = 0; i < TABLE_SIZE; i++){
			if(taken[i]){
				cout<<"Name: "<<table[i].name<<", Phone: "<<table[i].number<<"\n";
			}
		}
	}

};


class HashTableChain{
	vector<list<client>> table;
	public:
	int comparisons = 0;

	HashTableChain(){
		table.resize(TABLE_SIZE);
	}

	void insert(string name, long long number){
		int ind = hashFunc(number);
		table[ind].push_back({name, number});
	}

	bool search(long long number){
		int ind = hashFunc(number);

		for(auto &client : table[ind]){
			++comparisons;
			if(client.number == number)return true;
		}

		return false;
	}

};



int32_t main(){

	cout<<"Enter number of clients: ";
	int n; cin>>n;

	while(n > TABLE_SIZE){
		cout<<"Maximum size allowed is: "<<TABLE_SIZE<<", Please enter again\n";
		cin>>n;
	}

	HashTableLinear linear;
	HashTableChain chained;
	for(int i = 0; i < n; i++){
		cout<<"Enter "<<i+1<<"'th client's details: \n";
		cout<<"Name: ";
		string name; cin>>name;
		cout<<"Phone: ";
		long long number; cin>>number;
		chained.insert(name, number);
		linear.insert(name, number);
	}

	cout<<"\n";
	while(true){
		cout<<"1) Enter 0 to exit\n";
		cout<<"2) Enter 1 to search for a number\n";

		int ch; cin>>ch;
		if(ch == 0){
			cout<<"Quitting...\n";
			break;
		}
		if(ch != 1){
			cout<<"Wrong choice!\n";
			continue;
		}

		long long number; cin>>number;

		linear.search(number) ? cout<<"Found number in "<<linear.comparisons<<" comparisons using linear probing\n" : cout<<"Number not found using linear probing\n";
		chained.search(number) ? cout<<"Found number in "<<chained.comparisons<<" comparisons using chaining\n" : cout<<"Number not found using chaining\n";

	}

	return 0;
}
