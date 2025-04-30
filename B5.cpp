/*A book consists of chapters, chapters consist of sections and sections consist of subsections.
Construct a tree and print the nodes. Find the time and space requirements of your method.*/
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int data;
    Node *left, *right;
    Node(int d)
    {
        data = d;
        left = right = nullptr;
    }
};
Node *insertNode(int key, Node *root)
{
    if (root == NULL)
    {
        return new Node(key);
    }
    if (key < root->data)
    {
        root->left = insertNode(key, root->left);
    }
    else
    {
        root->right = insertNode(key, root->right);
    }
    return root;
}
void BFS(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        cout << temp->data << " ";
        if (temp->left != NULL)
        {
            q.push(temp->left);
        }
        if (temp->right != NULL)
        {
            q.push(temp->right);
        }
    }
    cout << endl;
}
void DFS(Node *root){
    stack<Node*> s;
    s.push(root);
    while(!s.empty()){
        Node* temp = s.top();
        s.pop();
        cout << temp->data << " ";
        if(temp->right != NULL){
            s.push(temp->right);
        }
        if(temp->left != NULL){
            s.push(temp->left);
        }
    }
    cout << endl;   
}
void inorder(Node *root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Node *root = NULL;
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i = 0;i<n;i++){
        int key;
        cin>>key;
        root = insertNode(key, root);
    }
    cout << "BFS Traversal: ";
    BFS(root);
    cout << endl;
    cout << "Inorder Traversal: ";  
    inorder(root);
    cout << endl;
    cout << "DFS Traversal: ";
    DFS(root);
    cout << endl;
    return 0;
}
