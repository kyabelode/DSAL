/*You have a business with several offices; you want to lease phone lines to connect them up with each other; and the phone company charges different amounts of money to connect different pairs of cities. You want a set of lines that connects all your offices with a minimum total cost. Solve the problem by suggesting appropriate data structures.*/
#include <bits/stdc++.h>
using namespace std;

const int N = 5;
vector<string> offices = {"Mumbai", "Pune", "Nashik", "Nagpur", "Panvel"};

float adjMatrix[N][N] = {
    {0, 2.0, 2.5, 0, 0}, // Mumbai
    {2.0, 0, 0, 0, 3.0}, // Pune
    {2.5, 0, 0, 1.5, 0}, // Nashik
    {0, 0, 1.5, 0, 2.0}, // Nagpur
    {0, 3.0, 0, 2.0, 0}  // Panvel
};

float Prim()
{
    vector<float> d(N, INT_MAX);  // distances
    vector<bool> inMST(N, false); // visited
    vector<int> parent(N, -1);    // to track edges
    set<int> S;

    d[0] = 0;
    float totalCost = 0;

    while (S.size() < N)
    {
        float x = INT_MAX;
        int v = -1;

        // Find vertex with min d[i] not in S
        for (int i = 0; i < N; i++)
        {
            if (!inMST[i] && d[i] < x)
            {
                x = d[i];
                v = i;
            }
        }

        inMST[v] = true;
        totalCost += d[v];
        S.insert(v);

        // Update neighbors of v
        for (int u = 0; u < N; u++)
        {
            if (adjMatrix[v][u] != 0 && !inMST[u])
            {
                if (d[u] > adjMatrix[v][u])
                {
                    d[u] = adjMatrix[v][u];
                    parent[u] = v;
                }
            }
        }
    }

    // Display selected edges
    cout << "Selected edges in MST:\n";
    for (int i = 1; i < N; i++)
    {
        if (parent[i] != -1)
        {
            cout << offices[parent[i]] << " - " << offices[i]
                 << " : " << adjMatrix[parent[i]][i] << " hrs" << endl;
        }
    }

    return totalCost;
}

int main()
{
    float cost = Prim();
    cout << "\nTotal Minimum Cost to Connect All Offices: " << cost << " hrs" << endl;
    return 0;
}
