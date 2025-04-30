/* B7. Construct an expression tree from the given prefix expression eg. +--a*bc/def and
traverse it using post order traversal (non recursive) and then delete the entire tree */
#include <bits/stdc++.h>
using namespace std;
struct Node{    
    char key;
    Node *left,*right;
    Node(char c ){
        key = c;
        left = right = nullptr;
    }
};
void inorder(Node *root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    cout<<root->key<<"";
    inorder(root->right);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin>>s;
    Node *x,*y,*z;
    // we made three nodes for the expression;
    // consider it as root left right
    // now make a stack based on the Node structure;
    stack<Node*>stk;
    
    for(int i = s.length() - 1;i>=0;i--){
        // cause this is the preorder to inorder 
        // when we will go from first to last there will be exception and tree will not get pushed in the stack
        // take y as the left node and z as the right node and x as the root node
        // when +-*/^ will come we have to pop otherwise push becuase its tree we have to consider left and right element 
        if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^'){
            // this are the priority wise 
            x = new Node(s[i]);
            // root node to be pushed 
            // take y as top element 
            y = stk.top();
            // pop it 
            stk.pop();   /* Here we doing pop if its prefix there will be no pop becuase tree is empty cause of this we are travelling from the last end of the array */
            //take top element as z the right node element 
            z = stk.top();
            // we will pop it 
            stk.pop();
            // assign left as y;
            x->left = y;
            // assign right as x;
            x->right = z;
            // push it into stack;
            stk.push(x);
        }   
        else{
            // this one is the common condition
            x = new Node(s[i]);
            stk.push(x);
        }
    }
    cout<<"The expression tree is: \n";
    inorder(x);
    cout<<'\n';
    return 0;
}
