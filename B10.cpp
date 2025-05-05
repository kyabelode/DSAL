/*Consider threading a binary tree using preorder threads rather than inorder threads. Design an algorithm for traversal without using stack and analyze its complexity. _*/
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int v): data(v), left(nullptr), right(nullptr) {}
};

void Preorder(Node* root) {
    Node* curr = root;
    while (curr) {
        if (!curr->left) {
            cout << curr->data << " ";                     
            curr = curr->right;                           
        } else {
            Node* pred = curr->left;
            while (pred->right && pred->right != curr)
                pred = pred->right;

            if (!pred->right) {
                // Create temporary thread and visit
                pred->right = curr;                         
                cout << curr->data << " ";                     
                curr = curr->left;                          
            } else {
                // Thread exists: remove it and go right
                pred->right = nullptr;                      
                curr = curr->right;                         
            }
        }
    }
}

int main() {
    // Example tree:
    //      1
    //     / \
    //    2   3
    //   / \   \
    //  4   5   6
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);

    Preorder(root);  // Output: 1 2 4 5 3 6
    cout << "\n";
    return 0;
}
