using namespace std;
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
// const int n = 875714;
const int n = 9;

vector<bool> visited(n, false);
vector<int> leader(n, 0);
vector<int> f(n, 0);
int s = 0;
int t = 0;
// iterative depth first search
void DFS(int v, const vector<vector<int>>& graph) {
    stack<int> stk;
    stk.push(v);

    while (!stk.empty()) {
        v = stk.top();
        stk.pop();

        if (visited[v]) continue;

        visited[v] = true;
        leader[v] = s;
        t++;
        f[v] = t;

        for (int i = 0; i < graph[v].size(); i++) {
            if (!visited[graph[v][i]]) {
                stk.push(graph[v][i]);
            }
        }
    }
}
// void DFS(int v, const vector<vector<int>>& graph) {
//     visited[v] = true;
//     leader[v] = s;
//     // cout << v << " ";
//     for (int i = 0; i < graph[v].size(); i++) {
//         if (!visited[graph[v][i]]) {
//             DFS(graph[v][i], graph);
//         }
//     }
//     t++;
//     f[v] = t;
// }
void dfsLoop(vector<vector<int>> graph) {
    for (int i = n; i >= 1; i--) {
        if (!visited[i]) {
            s = i;
            DFS(i, graph);
        }
    }
}

vector<vector<int>> readInAdjList(string fileName, bool reverse) {
    vector<vector<int>> graph(n + 1);

    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        exit(1);
    }

    string line;
    if (!reverse) {
        while (getline(file, line)) {
            istringstream iss(line);
            int tail, head;
            if (!(iss >> tail >> head)) {
                cout << "Invalid line format" << endl;
                break;
            }
            graph[tail].push_back(head);
        }
    } else {
        while (getline(file, line)) {
            istringstream iss(line);
            int tail, head;
            if (!(iss >> head >> tail)) {
                cout << "Invalid line format" << endl;
                break;
            }
            graph[tail].push_back(head);
        }
    }
    return graph;
}

vector<vector<int>> relabelVertices(vector<vector<int>>& graph) {
    vector<vector<int>> newGraph(n + 1);

    for (int i = 1; i <= n; i++) {
        int newLabel = f[i];
        for (int j = 0; j < graph[i].size(); j++) {
            int newChildLabel = f[graph[i][j]];
            newGraph[newLabel].push_back(newChildLabel);
        }
    }
    return newGraph;
}

void printGraph(const vector<vector<int>>& graph) {
    for (int i = 1; i <= n; ++i) {
        cout << i << ": ";
        for (int j = 0; j < graph[i].size(); ++j) {
            cout << graph[i][j] << ' ';
        }
        cout << '\n';
    }
}
void printLargestSCCs() {
    unordered_map<int, int> leaderCounts;
    for (int i = 1; i <= n; i++) {
        leaderCounts[leader[i]]++;
    }

    vector<int> counts;
    for (auto it = leaderCounts.begin(); it != leaderCounts.end(); ++it) {
        counts.push_back(it->second);
    }

    sort(counts.begin(), counts.end(), greater<int>());

    cout << "Sizes of the five largest SCCs: ";
    for (int i = 0; i < min(5, (int)counts.size()); i++) {
        cout << counts[i] << ' ';
    }
    cout << '\n';
}

int main() {
    vector<vector<int>> graph = readInAdjList("scc2.txt", false);
    vector<vector<int>> graphRev = readInAdjList("scc2.txt", true);

    dfsLoop(graphRev);

    vector<vector<int>> newGraph = relabelVertices(graph);

    s = 0;
    t = 0;
    visited.assign(n, false);

    dfsLoop(newGraph);

    printLargestSCCs();

    return 0;
}