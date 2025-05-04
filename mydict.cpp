#include <bits/stdc++.h>
using namespace std;


struct Node{
	string key;
	string value;
	Node *left;
	Node *right;

	Node(string k, string val){
		key = k;
		value = val;
		left = right = nullptr;
	}

};

// The bst class

class Dictionary{

private:
	Node *root;

	Node *insert(Node *node, string key, string val){
		if(node == nullptr){
			return new Node(key, val);
		}

		if(key < node->key){
			node->left = insert(node->left, key, val);
		}else if(key > node->key){
			node->right = insert(node->right, key, val);
		}
		return node;
	}

	Node *search(Node *node, string key){
		if(node == nullptr || node->key == key){
			return node;
		}

		if(key < node->key){
			return search(node->left, key);
		} else return search(node->right, key);
	}


public:
	Dictionary(){
		root = nullptr;
	}

	void insert(string key, string val){
		if(root == nullptr){
			root = new Node(key, val);
			return;
		}
		root = insert(root, key, val);
	}

	string search(string key){
		Node *node = search(root, key);
		if(node == nullptr){
			return "Key not found!";
		}else return node->value;
	}

};


int32_t main(){

	Dictionary dict;

	dict.insert("banana", "a long fruit");
	dict.insert("apple", "a round fruit");
	dict.insert("peach", "the ass fruit");

	while(true){
		cout<<"Enter the key to search: ";
		string s; cin>>s;
		cout<<s<<": "<<dict.search(s)<<"\n";
	}

	return 0;
}
