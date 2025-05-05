/*Tree Height Balanace AVL delete insert left rotate right rotate*/
#include <iostream>
#include <string>
using namespace std;

struct Node {
    string key;      
    string meaning;  
    Node* left;
    Node* right;
    int height;

    Node(string k, string m) : key(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;


    int height(Node* N) {
        return N ? N->height : 0;
    }

    int getBalance(Node* N) {
        return N ? height(N->left) - height(N->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, string key, string meaning) {
     
        if (!node)
            return new Node(key, meaning);

        if (key < node->key)
            node->left = insert(node->left, key, meaning);
        else if (key > node->key)
            node->right = insert(node->right, key, meaning);
        else {
           
            cout << "Duplicate key \"" << key << "\" not inserted.\n";
            return node;
        }


        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        // Balance the tree
        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    // Find the node with minimum key value
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    // Delete a node
    Node* deleteNode(Node* root, string key) {
        // Perform standard BST delete
        if (!root)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            // Node with only one child or no child
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;

                // No child case
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp; // One child case

                delete temp;
            } else {
                // Node with two children
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        // If the tree had only one node
        if (!root)
            return root;

        // Update height
        root->height = 1 + max(height(root->left), height(root->right));

        // Get balance factor
        int balance = getBalance(root);

        // Balance the tree
        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // Search for a key
    Node* search(Node* root, string key) {
        if (!root || root->key == key)
            return root;
        if (key < root->key)
            return search(root->left, key);
        return search(root->right, key);
    }

    void inOrder(Node* root) {
        if (root) {
            inOrder(root->left);
            cout << root->key << ": " << root->meaning << endl;
            inOrder(root->right);
        }
    }

    void reverseInOrder(Node* root) {
        if (root) {
            reverseInOrder(root->right);
            cout << root->key << ": " << root->meaning << endl;
            reverseInOrder(root->left);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    // Insert a key-meaning pair
    void insert(string key, string meaning) {
        root = insert(root, key, meaning);
    }

    // Delete a key
    void deleteKey(string key) {
        root = deleteNode(root, key);
    }
    void update(string key, string newMeaning) {
        Node* node = search(root, key);
        if (node) {
            node->meaning = newMeaning;
            cout << "Updated \"" << key << "\" with new meaning.\n";
        } else {
            cout << "Key \"" << key << "\" not found.\n";
        }
    }

    void searchKey(string key) {
        Node* node = search(root, key);
        if (node) {
            cout << key << ": " << node->meaning << endl;
        } else {
            cout << "Key \"" << key << "\" not found.\n";
        }
    }

    // Display dictionary in ascending order
    void displayAscending() {
        cout << "Dictionary in ascending order:\n";
        inOrder(root);
    }

    // Display dictionary in descending order
    void displayDescending() {
        cout << "Dictionary in descending order:\n";
        reverseInOrder(root);
    }
};

// Main function to demonstrate the AVL Tree dictionary
int main() {
    AVLTree dict;

    // Inserting entries
    dict.insert("apple", "A fruit");
    dict.insert("banana", "Another fruit");
    dict.insert("car", "A vehicle");
    dict.insert("dog", "An animal");
    dict.insert("elephant", "A large animal");

    // Display in ascending order
    dict.displayAscending();

    // Search for a key
    dict.searchKey("car");

    // Update a key
    dict.update("car", "A road vehicle");

    // Delete a key
    dict.deleteKey("banana");

    // Display in descending order
    dict.displayDescending();

    return 0;
}
