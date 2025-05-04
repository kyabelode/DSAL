#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

struct Node {
    char value;
    Node* left;
    Node* right;

    Node(char val) : value(val), left(nullptr), right(nullptr) {}
};

// Function to check if character is operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Convert infix to postfix (Shunting Yard Algorithm)
string infixToPostfix(string infix) {
    stack<char> opStack;
    string postfix;

    for (char ch : infix) {
        if (isspace(ch)) continue;

        if (isalnum(ch)) {
            postfix += ch;
        } else if (isOperator(ch)) {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(ch)) {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(ch);
        }
    }

    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }

    return postfix;
}

// Build expression tree from postfix
Node* buildTreeFromPostfix(const string& postfix) {
    stack<Node*> st;

    for (char ch : postfix) {
        if (isalnum(ch)) {
            st.push(new Node(ch));
        } else if (isOperator(ch)) {
            Node* right = st.top(); st.pop();
            Node* left = st.top(); st.pop();
            Node* root = new Node(ch);
            root->left = left;
            root->right = right;
            st.push(root);
        }
    }

    return st.top();
}

// Inorder traversal (recursive)
void inorder(Node* root) {
    if (!root) return;
    if (isOperator(root->value)) cout << "(";
    inorder(root->left);
    cout << root->value;
    inorder(root->right);
    if (isOperator(root->value)) cout << ")";
}

// Postorder traversal (non-recursive using 2 stacks)
void postorderNonRecursive(Node* root) {
    if (!root) return;
    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* curr = s1.top(); s1.pop();
        s2.push(curr);

        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->value << " ";
        s2.pop();
    }
}

// Delete tree (postorder)
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    string infix = "a-b*c-d/e+f";

    cout << "Infix Expression: " << infix << endl;
    string postfix = infixToPostfix(infix);
    cout << "Postfix Expression: " << postfix << endl;

    Node* exprTree = buildTreeFromPostfix(postfix);

    cout << "\nInorder Traversal (with parentheses): ";
    inorder(exprTree);
    cout << endl;

    cout << "Postorder Traversal (Non-Recursive): ";
    postorderNonRecursive(exprTree);
    cout << endl;

    // Delete tree
    deleteTree(exprTree);
    cout << "Tree deleted successfully." << endl;

    return 0;
}
