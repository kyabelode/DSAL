#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    string key, meaning;
    Node* left;
    Node* right;
    int height;

    Node(string k, string m) : key(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

class AVL {
private:
    Node* root;

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int getBalance(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
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
        if (!node) return new Node(key, meaning);

        if (key < node->key)
            node->left = insert(node->left, key, meaning);
        else if (key > node->key)
            node->right = insert(node->right, key, meaning);
        else {
            cout << "Duplicate key. Updating meaning.\n";
            node->meaning = meaning;
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        // Left Left
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, string key) {
        if (!root) return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            }

            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->key);
        }

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        // Rebalance if needed
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " : " << node->meaning << "\n";
        inorder(node->right);
    }

    void reverseInorder(Node* node) {
        if (!node) return;
        reverseInorder(node->right);
        cout << node->key << " : " << node->meaning << "\n";
        reverseInorder(node->left);
    }

    Node* search(Node* node, string key, int& comparisons) {
        while (node) {
            comparisons++;
            if (key == node->key)
                return node;
            else if (key < node->key)
                node = node->left;
            else
                node = node->right;
        }
        return nullptr;
    }

public:
    AVL() : root(nullptr) {}

    void insert(string key, string meaning) {
        root = insert(root, key, meaning);
    }

    void deleteKeyword(string key) {
        root = deleteNode(root, key);
    }

    void update(string key, string newMeaning) {
        int comparisons = 0;
        Node* found = search(root, key, comparisons);
        if (found) {
            found->meaning = newMeaning;
            cout << "Updated successfully.\n";
        } else {
            cout << "Key not found.\n";
        }
    }

    void displayAscending() {
        cout << "\n--- Dictionary in Ascending Order ---\n";
        inorder(root);
    }

    void displayDescending() {
        cout << "\n--- Dictionary in Descending Order ---\n";
        reverseInorder(root);
    }

    void searchKeyword(string key) {
        int comparisons = 0;
        Node* found = search(root, key, comparisons);
        if (found)
            cout << "Found: " << found->key << " = " << found->meaning << " | Comparisons: " << comparisons << "\n";
        else
            cout << "Key not found. Comparisons made: " << comparisons << "\n";
    }

    int maxComparisons() {
        return height(root); // worst-case: tree height = max comparisons
    }
};

int main() {
    AVL dict;
    dict.insert("Apple", "A fruit");
    dict.insert("Banana", "Another fruit");
    dict.insert("Cat", "An animal");
    dict.insert("Dog", "Another animal");

    dict.displayAscending();
    dict.displayDescending();

    dict.searchKeyword("Cat");
    dict.searchKeyword("Zebra");

    dict.update("Banana", "Yellow fruit");
    dict.deleteKeyword("Apple");

    dict.displayAscending();

    cout << "Maximum comparisons required for any keyword (tree height): " << dict.maxComparisons() << "\n";

    return 0;
}
