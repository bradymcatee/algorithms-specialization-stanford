using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>

long int primsMST(vector<pair<int, int>> adj[], int s, int V){

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> key(V+1, 100000000);
    vector<bool> inMST(V+1, false);
    vector<int> parent(V+1, -1);

    key[s] = 0;
    pq.push(make_pair(0, s));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (const auto& neighbor : adj[u]) {
            int v = neighbor.first, weight = neighbor.second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    key[0] = 0;
    long int totalWeight = 0;
    for (int i = 0; i < V+1; i++) {
        totalWeight += key[i];
    }
    return totalWeight;
}

void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt){


	adj[u].push_back(make_pair(v, wt));
	adj[v].push_back(make_pair(u, wt));

}
void printGraph(vector<pair<int,int> > adj[], int V)
{
    int v, w;
    for (int u = 0; u < V+1; u++)
    {
        cout << "Node " << u << " makes an edge with \n";
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++)
        {
            v = it->first;
            w = it->second;
            cout << "\tNode " << v << " with edge weight ="
                 << w << "\n";
        }
        cout << "\n";
    }
}
int main(){
	int numNodes, numEdges;
	ifstream infile("edges.txt");
	infile >> numNodes >> numEdges;

	vector<pair<int, int>> adj[numNodes + 1];


	int u, v, wt;
	if (!infile.is_open()) {
		cout << "Failed to open the file." << endl;
        	return 1;
	}

	while (infile >> u >> v >> wt){
	       addEdge(adj, u, v, wt);
	}

	printGraph(adj, numNodes);


        long int totalWeight = primsMST(adj,1,numNodes);
     	
	cout << "total weight: " << totalWeight << endl;	
	return 0;

}

