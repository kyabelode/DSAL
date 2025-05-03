/*Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list to perform BFS.
 Use *the map of the area around the college as the graph. Identify the prominent land marks as nodes and perform DFS and BFS on that */

#include <bits/stdc++.h>
using namespace std;
// No of vertices
const int N = 6;
// run bfs and dfs on the graph

vector<string> abc = {"A", "B", "C", "D", "E", "F"};
int adjMatrix[N][N] = {
    {0, 1, 0, 0, 0, 1}, // A
    {1, 0, 1, 0, 0, 0}, // B
    {0, 1, 0, 1, 0, 0}, // C
    {0, 0, 1, 0, 1, 0}, // D
    {0, 0, 0, 1, 0, 1}, // E
    {1, 0, 0, 0, 1, 0}  // F
};

vector<vector<int>> adjList = {
    {1, 5},
    {0, 2},
    {1, 3},
    {2, 4},
    {3, 5},
    {0, 4}};
void DFS(int v, vector<bool> &visited)
{
    visited[v] = true;
    cout << "Visited: " << abc[v] << "\n";
    for (int i : adjList[v])
    {
        if (!visited[i])
        {
            DFS(i, visited);
        }
    }
}
void BFS(int v)
{
    vector<bool> d(N, false);
    d[v] = true;
    queue<int> q;
    q.push(v);
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        cout << "Visited :" << abc[curr] << "\n";
        for (int u : adjList[curr])
        {
            if (d[u] != true)
            {
                d[u] = true;
                q.push(u);
            }
        }
    }
}
int main()
{
    cout << "DFS traversal : \n";
    vector<bool> visited(N, false);
    DFS(0, visited);
    cout << "\n";
    cout << "BFS traversal : \n";
    BFS(0);
    cout << "\n";
    return 0;
}
