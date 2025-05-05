/*Convert given binary tree into threaded binary tree. Analyze time and space complexity of the algorithm.*/
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    bool isThreaded;
    Node(int v)
      : data(v), left(nullptr), right(nullptr), isThreaded(false) {}
};

void populateThreads(Node* curr, Node*& prev) {
    if (!curr) return;

    populateThreads(curr->left, prev);

    if (prev && prev->right == nullptr) {
        prev->right = curr;
        prev->isThreaded = true;
    }
    prev = curr;

    if (!curr->isThreaded)
        populateThreads(curr->right, prev);
}

Node* createThreaded(Node* root) {
    Node* prev = nullptr;
    populateThreads(root, prev);
    return root;
}
void inorderTBT(Node* root) {
    Node* curr = root;
    while (curr && curr->left)
        curr = curr->left;
    while (curr) {
        cout << curr->data << " ";

        if (curr->isThreaded) {
            curr = curr->right;
        }
        else {
            curr = curr->right;
            while (curr && curr->left)
                curr = curr->left;
        }
    }
}

int main() {
    // build this tree:
    //       4
    //      / \
    //     2   6
    //    / \ / \
    //   1  3 5  7
    Node* root = new Node(4);
    root->left = new Node(2);
    root->right = new Node(6);
    root->left->left  = new Node(1);
    root->left->right = new Node(3);
    root->right->left  = new Node(5);
    root->right->right = new Node(7);

    createThreaded(root);
    inorderTBT(root);  // prints: 1 2 3 4 5 6 7
    cout << "\n";
    return 0;
}
