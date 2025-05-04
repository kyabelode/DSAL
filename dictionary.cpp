/*
Dictionary stores keywords & its meanings. Provide
facility for adding new keywords, deleting keywords, updating values of any entry. Provide
facility to display whole data sorted in ascending/ Descending order. Also find how many
maximum comparisons may require for finding any keyword. Use Binary Search Tree for
implementation
*/
// So a dictionary will store a key-value pair
#include <bits/stdc++.h>
using namespace std;
struct Node{
	string key;
	string value;
	Node *left;
	Node *right;

	Node(string k, string v){
		key = k;
		value = v;
		left = right = nullptr;
	}
};

// This is a BST

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
		if(node->key < key){
			return search(node->right, key);
		}else{
			return search(node->left, key);
		}

	}
public:
	Dictionary(){
		root = nullptr;
	}
	void insert(string key, string value){
		root = insert(root, key, value);
	}
	string search(string key){
		Node *node = search(root, key);
		if(node != nullptr){
			return node->value;
		}else return "Key not found!";
	}

};


int32_t main(){

	Dictionary dict;

	dict.insert("Banana", "Long fruit");
	dict.insert("Apple", "Round fruit");
	dict.insert("Peach", "Ass-like fruit");

	while(1){
		cout<<"Enter string to search: ";
		string s; cin>>s;
		cout<<s<<": "<<dict.search(s)<<"\n";
	}

	return 0;
}
