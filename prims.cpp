/*
You have a business with several offices; you want to
lease phone lines to connect them up with each other; and the phone company charges
different amounts of money to connect different pairs of cities. You want a set of lines that
connects all your offices with a minimum total cost. Solve the problem by suggesting
appropriate data structures.
*/
#include <bits/stdc++.h>
using namespace std;


class Graph{
	int V;
	vector<vector<pair<int, int>>> adj;

public:
	Graph(int v){
		V = v;
		adj.resize(v);
	}

	void addEdge(int u, int v, int cost){
		adj[u].push_back({cost, v});
		adj[v].push_back({cost, u});
	}

	int primMST(int start = 0){
		vector<bool> visited(V, false);
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

		pq.push({0, start});
		int cost = 0;

		while(!pq.empty()){
			auto [price, u] = pq.top();
			pq.pop();
			if(visited[u])continue;
			visited[u] = true;
			cost += price;

			cout<<"Included office "<<u<<" with connection cost: "<<price<<"\n";
			for(auto [edge, v] : adj[u]){
				if(!visited[v]){
					pq.push({edge, v});
				}
			}
		}
		return cost;
	}

};



int32_t main(){

	int offices = 5; // Number of offices
    Graph g(offices);

    // Add phone line costs between offices
    g.addEdge(0, 1, 10); // Office 0 - Office 1
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 6);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 8);
    g.addEdge(2, 4, 12);

    int cost = g.primMST();
    cout << "Minimum total cost to connect all offices: " << cost << "\n";


	return 0;
}
