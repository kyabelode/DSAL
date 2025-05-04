/*
Represent a given graph using adjacency matrix/ list to
perform DFS and using list to perform BFS. Use the map of the area around the college as the
graph. Identify the prominent land marks as nodes and perform DFS and BFS on that
*/
#include <bits/stdc++.h>
using namespace std;


class Graph{
	int V;
	vector<vector<int>> adj;

public:
	Graph(int V){
		this->V = V;
		adj.resize(V);
	}

	void addEdge(int u, int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void DFSutil(int v, vector<bool> &visited, map<int, string> memo){
		visited[v] = true;
		cout<<memo[v]<<" ";

		for(auto &u : adj[v]){
			if(!visited[u]){
				DFSutil(u, visited, memo);
			}
		}
	}

	void dfs(int start, map<int, string> memo){
		vector<bool> visited(V, false);
		cout<<"DFS traversal starting from "<<memo[start]<<": \n";
		DFSutil(start, visited, memo);
		cout<<"\n";
	}

	void bfs(int start, map<int, string> memo){
		vector<bool> visited(V, false);
		queue<int> que;
		visited[start] = true;
		que.push(start);
		cout<<"BFS traversal starting from "<<memo[start]<<": \n";
		while(!que.empty()){
			int v = que.front();
			que.pop();
			cout<<memo[v]<<" ";
			for(auto &u : adj[v]){
				if(!visited[u]){
					visited[u] = true;
					que.push(u);
				}
			}
		}
		cout<<"\n";
	}

};




int32_t main(){

	Graph g(5);
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(2, 4);
	g.addEdge(3, 2);
	g.addEdge(4, 1);
	map<int, string> memo;
	memo[0] = "College";
	memo[1] = "Bar";
	memo[2] = "Turf";
	memo[3] = "Theatre";
	memo[4] = "Home";
	g.dfs(0, memo);
	g.bfs(0, memo);
	return 0;
}
