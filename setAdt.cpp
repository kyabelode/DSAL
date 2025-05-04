/*
To create ADT that implements the "set" concept.
a. Add (new Element) -Place a value into the set
b. Remove (element) Remove the value
c. Contains (element) Return true if element is in
 collection
d. Size () Return number of values in collection Iterator () Return an iterator used to loop over collection
e. Intersection of two sets
f. Union of two sets
g. Difference between two sets
h. Subset
*/

#include <bits/stdc++.h>
using namespace std;


class Set{
	vector<int> elems;

	public:
	void add(int n){
		if(!contains(n)){
			elems.push_back(n);
		}
	}

	void remove(int n){
		if(!contains(n))return;
		auto it = find(elems.begin(), elems.end(), n);
		elems.erase(it);
	}

	bool contains(int n){
		for(auto &i : elems){
			if(i == n)return true;
		}
		return false;
	}

	int size(){
		return elems.size();
	}

	vector<int>::iterator begin() { return elems.begin(); }
	vector<int>::iterator end() { return elems.end(); }

	Set Union(Set &other){
		for(auto &i : other){
			this->add(i);
		}
		return *this;
	}

	Set Difference(Set &other){
		Set ans;
		for(auto &i : elems){
			if(!other.contains(i)){
				ans.add(i);
			}
		}
		return ans;
	}

	bool subset(Set &other){
		for(auto &i : elems){
			if(!other.contains(i))return false;
		}
		return true;
	}
	void print(){
		cout<<"{";
		for(int i = 0; i < elems.size(); i++){
			cout<<elems[i];
			if(i != elems.size() - 1)cout<<", ";
		}
		cout<<"}\n";
	}

};


int32_t main(){

	Set myset;
	while(true){
		cout<<"1) Print the current set\n";
		cout<<"2) Add to set\n";
		cout<<"3) Remove from set\n";
		cout<<"4) Check if element is in set\n";
		cout<<"5) Exit\n";

		int ch; cin>>ch;
		if(ch == 5){
			break;
		}
		if(ch == 1)myset.print();
		if(ch == 2){
			cout<<"Enter element to add: ";
			int n; cin>>n;
			myset.add(n);
		}
		if(ch == 3){
			cout<<"Enter element to remove: ";
			int n; cin>>n;
			myset.remove(n);
		}
		if(ch == 4){
			cout<<"Enter element to check: ";
			int n; cin>>n;
			myset.contains(n) ? cout<<"Present\n" : cout<<"Not present\n";
		}

	}

	return 0;
}
