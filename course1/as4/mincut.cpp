#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <map>

using namespace std;

void contractEdge(vector<list<int>>& adjList, vector<bool>& isValid, int u, int v) {
    // Merge the adjacency list of v into the adjacency list of u
    adjList[u].splice(adjList[u].end(), adjList[v]);

    // Mark vertex v as invalid
    isValid[v] = false;

    // Remove any self-loops in the adjacency list of u
    adjList[u].remove(u);
    adjList[u].remove(v);

    // Update any references to v in the other adjacency lists
    for(int i = 0; i < adjList.size(); ++i) {
        if(i != u && isValid[i]) {
            for(int &node : adjList[i]) {
                if(node == v) {
                    node = u;
                }
            }
        }
    }
}

pair<int, int> selectRandomEdge(const vector<list<int>>& adjList, const vector<bool>& isValid) {
    random_device rd;
    mt19937 gen(rd());

    // Select a random vertex
    uniform_int_distribution<> disVertex(0, adjList.size() - 1);
    int u;
    do {
        u = disVertex(gen);
    } while(!isValid[u] || adjList[u].empty());

    // Select a random neighbor
    uniform_int_distribution<> disNeighbor(0, adjList[u].size() - 1);
    auto it = adjList[u].begin();
    advance(it, disNeighbor(gen));
    int v = *it;

    return make_pair(u, v);
}

void karger(vector<list<int>>& adjList) {
    int vertices = adjList.size();
    vector<bool> isValid(vertices, true);
    while (vertices > 2) {
        pair<int, int> edge = selectRandomEdge(adjList, isValid);
        contractEdge(adjList, isValid, edge.first, edge.second);
        vertices--;
    }
}

int findMinCut(vector<list<int>> adjList, int iterations) {
    int minCut = 1000000;
    for (int i = 0; i < iterations; ++i) {
        vector<list<int>> adjListCopy = adjList;
        karger(adjListCopy);
        for(auto& list: adjListCopy) {
            if(!list.empty()) {
                int cutSize = list.size();
                if (cutSize < minCut) {
                    minCut = cutSize;
                }
                break;
            }
        }
    }
    return minCut;
}

vector<list<int>> readGraphFromFile(const string &fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Could not open the file - '" << fileName << "'" << endl;
        return {};
    }
    vector<list<int>> adjList;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int u, v;
        iss >> u;
        list<int> neighbors;
        while (iss >> v) {
            neighbors.push_back(v-1); // Adjust for 1-based indexing
        }
        adjList.push_back(neighbors);
    }
    return adjList;
}

int main() {
    string filename = "kargerMinCut.txt";
    auto adjList = readGraphFromFile(filename);
    int iterations = 1000; // Set as desired
    int minCut = findMinCut(adjList, iterations);
    cout << "The minimum cut found by Karger's algorithm is: " << minCut << endl;
    return 0;
}
