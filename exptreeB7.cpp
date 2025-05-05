/* B7. Construct an expression tree from the given prefix expression eg. +--a*bc/def and
traverse it using post order traversal (non recursive) and then delete the entire tree */
#include <bits/stdc++.h>
using namespace std;

struct Node {
    char c;
    Node* left, *right;
    Node* next; 
    Node(char v) {
        c = v;
        left = nullptr;
        right = nullptr;
        next = nullptr;
    }
};

class Stack {
    Node* head;

public:
    Stack() {
        head = nullptr;
    }

    void push(Node* root) {
        root->next = head;
        head = root;
    }

    void pop() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
        }
    }

    Node* top() {
        return head;
    }

    bool isEmpty() {
        return head == nullptr;
    }
};

void inorder(Node* root) {
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->c << " ";
    inorder(root->right);
}

int main() {
    string s;
    cin >> s;  // Example: *+ab-cd

    Stack stk;
    Node *x, *y, *z;

    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') {
            x = new Node(s[i]);
            y = stk.top(); stk.pop();
            z = stk.top(); stk.pop();
            x->left = y;
            x->right = z;
            stk.push(x);
        } else {
            x = new Node(s[i]);
            stk.push(x);
        }
    }

    cout << "Inorder traversal of expression tree: ";
    inorder(stk.top());
    cout << endl;

    return 0;
}
