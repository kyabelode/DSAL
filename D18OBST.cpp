// The Things given are keys with probability you have to find the cost and the root matrix
#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vf = vector<float>;
int main()
{
    int n;
    cout << "Enter the number of keys\n";
    cin >> n;
    vi keys(n);
    vf pro(n);
    cout << "Enter the keys\n";
    for (int i = 0; i < n; i++)
        cin >> keys[i];

    sort(keys.begin(), keys.end());
    cout << "Enter the pro\n";
    for (int i = 0; i < n; i++)
        cin >> pro[i];

    // to find the minimum cost we have to use dynamic programming approach
    // therefore the req cost will be cost[1][n];
    // to find the cost at first we have to set some values
    // for that lets create two 2D matrix with the help of vector

    vector<vector<float>> cost(n + 2, vector<float>(n + 1, 0));
    // the reason for why we took cost[n+2][n+1] matrix
    // here we are travelling from i = 0 to i<=n
    // the first 0 coloumn will always be zero

    vector<vector<int>> root(n + 1, vector<int>(n + 1, 0));
    // the reason for why we took root[n+1][n+1]
    // its simple we will traverse from i = 1 to i<=n

    for (int i = 1; i <= n; i++)
    {
        cost[i][i - 1] = 0; // lower triangular matrix
        cost[i][i] = pro[i - 1];
        root[i][i - 1] = 0; // lower triangular matrix
        root[i][i] = i;
    }
    cost[n + 1][n] = 0; // it is the first column of the matrix that is always zero

    // here we will the cost
    for (int diagonal = 1; diagonal <= n - 1; diagonal++)
    {
        for (int i = 1; i <= n - diagonal; i++)
        {
            int j = i + diagonal; // cost will be visible above the diagonal
            cost[i][j] = INT_MAX;

            float sum = 0;
            for (int k = i - 1; k < j; k++)
                sum += pro[k];

            for (int k = i; k <= j; k++)
            {
                float cst = cost[i][k - 1] + cost[k + 1][j] + sum;
                if (cst < cost[i][j])
                {
                    cost[i][j] = cst;
                    root[i][j] = k;
                }
            }
        }
    }
    for (auto c : cost)
    {
        for (auto(i) : c)
        {
            cout << i << " ";
        }
    }
    return 0;
}
