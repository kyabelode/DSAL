/*A Dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry. Provide facility to display whole data sorted in ascending/ Descending order. Also find how many maximum comparisons may require for finding any keyword. Use Height balance tree and find the complexity for finding a keyword*/
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int key;
    char mean;
    Node *left, *right;
    Node(int k, char m)
    {
        key = k;
        mean = m;
        left = right = nullptr;
    }
};
class Dict
{
    Node *root;

public:
    Dict()
    {
        root = NULL;
    }
    Node *insert(Node *root, int k, char c)
    {
        Node *head = new Node(k, c);
        Node *curr = root;
        if (root == NULL)
        {
            return head;
        }
        if (curr->key > k)
        {
            curr->left = insert(curr->left, k, c);
        }
        else
        {
            curr->right = insert(curr->right, k, c);
        }
        return curr;
    }
    void insert(int k, char c)
    {
        root = insert(root, k, c);
    }
    // traversal Decsending
    void preorder(Node *temp)
    {
        if (temp == NULL)
        {
            return;
        }
        cout << temp->key << " ";
        preorder(temp->left);
        preorder(temp->right);
    }

    // traversal ascending
    void inorder(Node *temp)
    {
        if (temp == NULL)
        {
            return;
        }
        inorder(temp->left);
        cout << temp->key << " ";
        inorder(temp->right);
    }
    // searching a key
    bool Search(int key)
    {
        Node *curr = root;
        while (curr != NULL)
        {
            if (curr->key == key)
            {
                return true;
            }
            if (curr->key > key)
            {
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
        }
        return false;
    }
    void update(int k, char m)
    {
        Node *curr = root;
        while (curr != NULL)
        {
            if (curr->key == k)
            {
                curr->mean = m;
                return;
            }
            if (curr->key > k)
            {
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
        }
        cout << "NOT FOUND\n";
    }
    void displayInorder()
    {
        cout << "Inorder Traversal: ";
        inorder(root);
        cout << endl;
    }
    void displayPreorder()
    {
        cout << "Inorder Traversal: ";
        preorder(root);
        cout << endl;
    }
    Node *deleteNode(Node *look, int key)
    {
        Node *curr = look;
        if (curr == nullptr)
        {
            return curr;
        }
        if (curr->key > key)
        {
            curr->left = deleteNode(curr->left, key);
        }
        else if (curr->key < key)
        {
            curr->right = deleteNode(curr->right, key);
        }
        else
        {
            if (curr->left == NULL && curr->right == NULL)
            {
                delete curr;
                return NULL;
            }
            if (curr->left == NULL)
            {
                Node *temp = curr->right;
                delete curr;
                return temp;
            }
            else if (curr->right == NULL)
            {
                Node *temp = curr->left;
                delete curr;
                return temp;
            }
            Node *temp = findMin(curr->right);
            curr->key = temp->key;
            curr->mean = temp->mean;
            curr->right = deleteNode(curr->right, temp->key);
        }
        return curr;
    }
    void deleteKey(int key)
    {
        root = deleteNode(root, key);
    }
    Node *findMin(Node *head)
    {
        while (head->left != NULL)
        {
            head = head->left;
        }
        return head;
    }
};
int main()
{
    Dict dict;
    dict.insert(10, 'A');
    dict.insert(20, 'B');
    dict.insert(5, 'C');
    dict.insert(15, 'D');

    dict.displayInorder();
    int keytoSearch = 15;
    if (dict.Search(keytoSearch))
    {
        cout << "KEY" << keytoSearch << "FOUND\n";
    }
    else
    {
        cout << "KEY" << keytoSearch << "NOT FOUND\n";
    }
    dict.update(15, 'E');
    dict.displayInorder();

    dict.update(25, 'F');

    dict.deleteKey(15);
    dict.displayInorder();

    dict.deleteKey(25);
    return 0;
}
