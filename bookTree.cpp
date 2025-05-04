/*
A book consists of chapters, chapters consist of sections
and sections consist of subsections. Construct a tree and print the nodes. Find the time and
space requirements of your method
*/
#include <bits/stdc++.h>
using namespace std;

const int max_cap = 1001;

struct Node{
	string data;
	int ccount;
	Node *child_arr;

	Node(string d){
		data = d;
		ccount = 0;
	}
	Node(){
		data = "";
		ccount = 0;
	}
	~Node(){
		if(child_arr){
			delete[] child_arr;
		}
	}

	void add_child(string d){
		if(!child_arr){
			child_arr = new Node[max_cap];
		}
		Node toadd(d);
		child_arr[ccount++] = toadd;
	}

};

void display(Node *root, int level = 0){
	for(int i = 0; i < level; i++){
		cout<<"  ";
	}
	cout<<root->data<<"\n";
	for(int i = 0; i < root->ccount; i++){
		display(&root->child_arr[i], level + 1);
	}
}



int32_t main(){

	return 0;
}
