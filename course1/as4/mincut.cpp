using namespace std;
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include <random>

void merge(int u, int v);
void removeLoops();

void contractEdge(std::vector<std::list<int>>& adjList, int u, int v) {
    // Step 1: Merge the adjacency list of v into the adjacency list of u
    adjList[u].splice(adjList[u].end(), adjList[v]);

    // Step 2: Remove the adjacency list for v
    // Instead of erasing the list, clear it and mark it as "deleted" with a special value
    adjList[v].clear();
    adjList[v].push_back(-1);  // -1 signifies a deleted vertex

    // Step 3: Remove any self-loops in the adjacency list of u
    adjList[u].remove(u);
    adjList[u].remove(v);

    // Step 4: Update any references to v in the other adjacency lists
    for(auto &neighbors : adjList) {
        neighbors.remove_if([v](int neighbor) { return neighbor == v; });
        for(auto &neighbor : neighbors) {
            if(neighbor > v) neighbor--;
        }
    }
}

pair<int, int> selectRandomEdge(const vector<list<int>>& adjList) {
    random_device rd;
    mt19937 gen(rd());

    int randomVertex = -1;
    do {
        uniform_int_distribution<> disVertex(0, adjList.size() - 1);
        randomVertex = disVertex(gen);
    } while(adjList[randomVertex].size() == 1 && adjList[randomVertex].front() == -1);

    int randomNeighbor = -1;
    do {
        uniform_int_distribution<> disNeighbor(0, adjList[randomVertex].size() - 1);
        auto it = adjList[randomVertex].begin();
        advance(it, disNeighbor(gen));
        randomNeighbor = *it;
    } while(randomNeighbor == -1);

    return make_pair(randomVertex, randomNeighbor);
}

void karger(vector<list<int>>& adjList){
    int vertices = adjList.size();

    // Create a random number generator outside the loop
    random_device rd;
    mt19937 gen(rd());

    while (vertices > 2){
        // Select a random edge
        uniform_int_distribution<> disVertex(0, adjList.size() - 1);
        int randomVertex = disVertex(gen);

        if(adjList[randomVertex].size() == 0) { // check if the vertex has no edges left
            continue; // skip to the next iteration if no edges left
        }

        // Select a random neighbor from the adjacency list of the selected vertex
        uniform_int_distribution<> disNeighbor(0, adjList[randomVertex].size() - 1);
        auto it = adjList[randomVertex].begin();
        advance(it, disNeighbor(gen));
        int randomNeighbor = *it;

        contractEdge(adjList, randomVertex, randomNeighbor);

        for(int i = 0; i < adjList.size(); ++i) {
            adjList[i].remove_if([randomNeighbor](int vertex){ return vertex == randomNeighbor; });
            for(auto& vertex : adjList[i]) {
                if(vertex > randomNeighbor) --vertex;
            }
        }

        vertices = adjList.size();
    }
}


int findMinCut(std::vector<std::list<int>> adjList, int iterations) {
    int minCut = INT_MAX;

    for (int i = 0; i < iterations; ++i) {
        std::vector<std::list<int>> adjListCopy = adjList;

        karger(adjListCopy);

        int cutSize = 0;
        for(const auto& list : adjListCopy) {
            if(list.size() > 1 || (list.size() == 1 && list.front() != -1)) {
                cutSize += list.size();
            }
        }

        if (cutSize < minCut) {
            minCut = cutSize;
        }
    }

    return minCut;
}


std::vector<std::list<int>> readGraphFromFile(const std::string &fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Could not open the file - '" << fileName << "'" << std::endl;
        return {};
    }

    std::vector<std::list<int>> adjList(1); // Start with a size of 1 to account for 1-based indexing

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int node, adjacentNode;
        iss >> node;

        std::list<int> adjacency;
        while (iss >> adjacentNode) {
            adjacency.push_back(adjacentNode - 1); // Adjust for 1-based indexing
        }

        adjList.push_back(adjacency);
    }

    return adjList;
}

int main(){
    string filename = "kargerMinCut.txt";
    auto adjList = readGraphFromFile(filename);

    int iterations = adjList.size(); // or you can choose any number of iterations

    // find the minimum cut
    int minCut = findMinCut(adjList, iterations);

    cout << "The minimum cut found by Karger's algorithm is: " << minCut << endl;



}