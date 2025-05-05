/*Beginning with an empty binary search tree, Construct binary search tree by inserting the values in the order given. After constructing a binary tree - i. Insert new node, ii. Find number of nodes in longest path from root, iii. Minimum data value found in the tree, iv. Change a tree so that the roles of the left and right pointers are swapped at every node, v. Search a value*/
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int data;
    Node *left, *right;
    Node(int k)
    {
        data = k;
        left = right = nullptr;
    }
};
Node *insertRec(Node *root, int key)
{
    if (root == NULL)
    {
        return new Node(key);
    }
    if (key > root->data)
    {
        root->right = insertRec(root->right, key);
    }
    else if (key < root->data)
    {
        root->left = insertRec(root->left, key);
    }
    return root;
}
void insert(Node *&root, int key)
{
    root = insertRec(root, key);
}
Node *search(Node *root, int key)
{
    if (root == NULL || root->data == key)
    {
        return root;
    }
    else if (key > root->data)
    {
        return search(root->right, key);
    }
    else
    {
        return search(root->left, key);
    }
}
int find_the_longest_path(Node *root)
{
    if (!root)
    {
        return 0;
    }

    int lh = find_the_longest_path(root->left);
    int rh = find_the_longest_path(root->right);
    return max(lh, rh) + 1;
}
void traversal(Node *root, vector<int> &arr)
{
    if (!root)
        return;
    arr.push_back(root->data);
    traversal(root->left, arr);
    traversal(root->right, arr);
}
void mirror(Node *root, Node **mm)
{
    if (!root)
    {
        *mm = NULL;
        return;
    }
    *mm = new Node(root->data);
    mirror(root->left, &((*mm)->right));
    mirror(root->right, &((*mm)->left));
}
void printreee(Node *root)
{
    vector<int> arr;
    traversal(root, arr);
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << '\n';
}
void printminelement(vector<int> arr)
{
    if (arr.empty())
    {
        cout << "NILL\n";
    }
    cout << *min_element(arr.begin(), arr.end()) << '\n';
}
int main()
{
    Node *root = NULL;

    // Insert nodes into the BST
    insert(root, 10);
    insert(root, 5);
    insert(root, 20);
    insert(root, 15);

    // Find the longest path (height of the tree)
    cout << "Height of the tree: " << find_the_longest_path(root) << endl;

    // Search for a key in the BST
    int key_to_search = 15;
    Node *search_result = search(root, key_to_search);
    if (search_result)
        cout << "Key " << key_to_search << " found in the BST.\n";
    else
        cout << "Key " << key_to_search << " not found in the BST.\n";

    // Print the tree elements (preorder traversal)
    cout << "Tree elements (preorder traversal): ";
    printreee(root);

    // Find and print the minimum element in the tree
    vector<int> tree_elements;
    traversal(root, tree_elements);
    cout << "Minimum element in the tree: ";
    printminelement(tree_elements);

    // Create and print the mirror of the tree
    Node *mirrored_tree = NULL;
    mirror(root, &mirrored_tree);
    cout << "Mirrored tree elements (preorder traversal): ";
    printreee(mirrored_tree);

    return 0;
}
