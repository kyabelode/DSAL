/*Tour operator organizes guided bus trips across the Maharashtra. Tourists may have different preferences. Tour operator offers a choice from many different routes. Every day the bus moves from starting city S to another city F as chosen by client. On this way, the tourists can see the sights alongside the route travelled from S to F. Client may have preference to choose route. There is a restriction on the routes that the tourists may choose from, the bus has to take a short route from S to F or a route having one distance unit longer than the minimal distance. Two routes from S to F are considered different if there is at least one road from a city A to a city B which is part of one route, but not of the other route.*/
#include <bits/stdc++.h>
using namespace std;

const int N = 5;
vector<string> cities = {"Mumbai", "Pune", "Nashik", "Nagpur", "Panvel"};
vector<pair<int, int>> adjList[N];
void addEdge(int u, int v, int dist)
{
    adjList[u].push_back({v, dist});
    adjList[v].push_back({u, dist});
}
void dijkstra(int start)
{
    vector<int> d(N, INT_MAX);
    vector<bool> visited(N, false);
    d[start] = 0;
    for (int i = 0; i < N; i++)
    {
        int u = -1;
        for (int j = 0; j < N; j++)
        {
            if (!visited[j] && (u == -1 || d[j] < d[u]))
            {
                u = j;
            }
        }
        visited[u] = true;
        for (auto [v, weight] : adjList[u])
        {
            if (!visited[v] && d[u] + weight < d[v])
            {
                d[v] = d[u] + weight;
            }
        }
    }
    cout << "Shortest distance from " << cities[start] << ":\n";
    for (int i = 0; i < N; i++)
    {
        cout << "To " << cities[i] << " = " << d[i] << " km\n";
    }
}
int main()
{
    addEdge(0, 1, 150); // Mumbai - Pune
    addEdge(0, 2, 180); // Mumbai - Nashik
    addEdge(1, 4, 120); // Pune - Panvel
    addEdge(2, 3, 500); // Nashik - Nagpur
    addEdge(3, 4, 300); // Nagpur - Panvel
    dijkstra(0);
    return 0;
}
