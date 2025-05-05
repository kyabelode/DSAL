/*
Read for the formulas in propositional calculus. Write a function that reads such a formula and creates its binary tree representation. What is the complexity of your function?  create a simplest code that is understandale with simplest algorithm
*/
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    char val;
    Node *left, *right;
    Node(char s, Node *l = nullptr, Node *r = nullptr)
        : val(s), left(l), right(r) {}
};
Node *parse(const string &f)
{
    stack<Node *> st;
    for (int i = 0; i < f.size(); i++)
    {
        char c = f[i];
        if (isalpha(c))
        {
            st.push(new Node(c));
        }
        else if ((c == '|' || c == '&' || c == '^' || c == '!') && !st.empty())
        {
            Node *left = st.top();
            st.pop();
            if (i + 1 < f.size() && isalpha(f[i + 1]))
            {
                Node *right = new Node(f[++i]);
                st.push(new Node(c, left, right));
            }
            else
            {
                st.push(left);
            }
        }
    }
    return (st.empty() ? nullptr : st.top());
}
void printInfix(Node *n)
{
    if (!n)
        return;
    if (n->left)
        cout << "(";
    printInfix(n->left);
    cout << n->val;
    printInfix(n->right);
    if (n->right)
        cout << ")";
}
int main()
{
    string formula = "p|q&r^s!t";
    Node *tree = parse(formula);
    printInfix(tree);
    cout << "\n";
}
