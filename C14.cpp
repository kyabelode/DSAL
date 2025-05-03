/*14 There are flight paths between cities. If there is a flight between city A and city B then there is an edge between the cities. The cost of the edge can be the time that flight take to reach city B from A, or the amount of fuel used for the journey. Represent this as a graph. The node can be represented by airport name or name of the city. Use adjacency list representation of the graph or use adjacency matrix representation of the graph. Check whether the graph is connected or not. Justify the storage representation used*/
#include <bits/stdc++.h>
using namespace std;
const int N = 5;
vector<string> Cities = {"Mumbai", "Pune", "Nashik", "Nagpur", "Panvel"};

// flight time in hours
float adjMatrix[N][N] =
    {
        {0, 2.0, 2.5, 0, 0}, // Mumbai
        {2.0, 0, 0, 0, 3.0}, // Pune
        {2.5, 0, 0, 1.5, 0}, // Nashik
        {0, 0, 1.5, 0, 2.0}, // Nagpur
        {0, 3.0, 0, 2.0, 0}  // Panvel
};
vector<pair<int, float>> adjList[N];
void DFS(int v, vector<bool> &visited)
{
    visited[v] = true;
    for (auto [u, _] : adjList[v])
    {
        if (!visited[u])
        {
            DFS(u, visited);
        }
    }
}
bool isConnected()
{
    vector<bool> visited(N, false);
    DFS(0, visited);
    for (bool v : visited)
    {
        if (!v)
        {
            return false;
        }
    }
    return true;
}
int main()
{
    // Fill the list from the adjMatrix
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (adjMatrix[i][j] != 0)
            {
                adjList[i].push_back({j, adjMatrix[i][j]});
            }
        }
    }
    // Display adjMatrix
    cout << "Display adjMatrix::" << "\n";
    cout << "\t";
    for (int i = 0; i < N; i++)
    {
        cout << Cities[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < N; i++)
    {
        cout << Cities[i] << "\t";
        for (int j = 0; j < N; j++)
        {
            cout << adjMatrix[i][j] << "\t";
        }
        cout << "\n";
    }

    // DFS of the graph
    vector<bool> visited(N, false);
    // Check if the graph is connected or not
    cout << "The graph is Connected or Not : ";
    if (isConnected())
    {
        cout << "True\n";
    }
    else
    {
        cout << "False\n";
    }
    return 0;
}
