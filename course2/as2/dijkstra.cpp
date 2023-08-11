using namespace std;
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

const int n = 200;
vector<int> X;

vector<bool> visited(n, false);

vector<int> dijkstra(vector<vector<pair<int, int>>> graph, int s) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> A(n, 1000000);

    A[s] = 0;

    pq.push(make_pair(0, s));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first, weight = neighbor.second;

            if (A[u] + weight < A[v]) {
                A[v] = A[u] + weight;

                pq.push(make_pair(A[v], v));
            }
        }
    }
    return A;
}

vector<vector<pair<int, int>>> readGraph(const string& filename) {
    // Create an initial graph with 201 empty slots (we start from index 1)
    vector<vector<pair<int, int>>> graph(201);

    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);

        int node;
        ss >> node;  // read the node number

        string edge;
        while (getline(ss, edge, '\t')) {  // split by tab
            istringstream edge_ss(edge);
            pair<int, int> edge_info;
            string part;

            // check if there is valid node data before the comma
            if (!getline(edge_ss, part, ',')) {
                continue;
            }
            edge_info.first = stoi(part);  // node

            // check if there is valid weight data after the comma
            if (!getline(edge_ss, part)) {
                continue;
            }
            edge_info.second = stoi(part);  // weight

            graph[node].push_back(edge_info);
        }
    }

    return graph;
}

void printGraph(vector<vector<pair<int, int>>> graph) {
    for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        for (int j = 0; j < graph[i].size(); j++) {
            cout << "tail: " << graph[i][j].first << " weight: " << graph[i][j].second << " ";
        }
        cout << endl;
    }
}
int main() {
    vector<vector<pair<int, int>>> graph = readGraph("dijkstra.txt");
    printGraph(graph);

    vector<int> shortestDistances = dijkstra(graph, 1);

    cout << "Shortest Distances: " << endl;

    cout << shortestDistances[7] << "," << shortestDistances[37] << "," << shortestDistances[59] << "," << shortestDistances[82] << "," << shortestDistances[99] << "," << shortestDistances[115] << "," << shortestDistances[133] << "," << shortestDistances[165] << "," << shortestDistances[188] << "," << shortestDistances[197] << "," << endl;
    return 0;
}