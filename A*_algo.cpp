#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <limits>
#include <algorithm>

using namespace std;

const int NODES = 10; 
const int INF = numeric_limits<int>::max();
//H values in map
map<char, int> hValue = { {'A', 15}, {'B', 13}, {'C', 13}, {'D', 12}, {'E', 10}, 
                          {'F', 9}, {'G', 7}, {'H', 6}, {'I', 5}, {'J', 0} };

int graph[NODES][NODES] = {
    {0, 6, 3, 1, 0, 0, 0, 0, 0, 0},
    {6, 0, 2, 6, 3, 4, 0, 0, 0, 0},
    {3, 2, 0, 0, 4, 5, 0, 0, 0, 0},
    {1, 6, 0, 0, 7, 8, 9, 0, 0, 0},
    {0, 3, 4, 7, 0, 6, 9, 9, 0, 0},
    {0, 4, 5, 8, 6, 0, 8, 9, 0, 0},
    {0, 0, 0, 9, 9, 8, 0, 11, 12, 14},
    {0, 0, 0, 0, 9, 9, 11, 0, 14, 15},
    {0, 0, 0, 0, 0, 0, 12, 14, 0, 0},
    {0, 0, 0, 0, 0, 0, 14, 15, 0, 0}
};

//function to get the index of a node from its character
int getIndex(char c) {
    return c - 'A';
}


void printPath(vector<int> &parent, int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    cout << (char)('A' + j) << " ";
}

//DFS implementation without cost
void DFS(int start) {
    vector<bool> visited(NODES, false);
    stack<int> s;
    s.push(start);

    cout << "DFS Traversal: ";
    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            cout << (char)('A' + node) << " ";
            visited[node] = true;
        }

        for (int i = 0; i < NODES; i++) {
            if (graph[node][i] != 0 && !visited[i]) {
                s.push(i);
            }
        }
    }
    cout << endl;
}

// Breadth First Search (BFS) implementation
void BFS(int start) {
    vector<bool> visited(NODES, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << (char)('A' + node) << " ";

        for (int i = 0; i < NODES; i++) {
            if (graph[node][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

// Best First Search implementation
void BestFirstSearch(int start) {
    vector<bool> visited(NODES, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    cout << "Best First Search Traversal: ";
    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();

        if (!visited[node]) {
            cout << (char)('A' + node) << " ";
            visited[node] = true;
        }

        for (int i = 0; i < NODES; i++) {
            if (graph[node][i] != 0 && !visited[i]) {
                pq.push({graph[node][i], i});
            }
        }
    }
    cout << endl;
}

bool DLS(int node, int target, int depth, vector<bool> &visited, vector<int> &path, vector<vector<int>> &allPaths) {
    path.push_back(node);  // Add current node to the path

    if (depth == 0) {
        if (node == target) {
            allPaths.push_back(path);  // Store path if target is found
        }
        path.pop_back();  // Remove node after checking
        return node == target;  // Return whether target is found
    }

    bool found = false;
    if (depth > 0) {
        visited[node] = true;
        for (int i = 0; i < NODES; i++) {
            if (graph[node][i] != 0 && !visited[i]) {
                if (DLS(i, target, depth - 1, visited, path, allPaths)) {
                    found = true;  // Continue to find more paths
                }
            }
        }
    }
    
    path.pop_back();  // Remove node if no successful path
    return found;
}

void IDDFS(int start, int target) {
    int depth = 1;
    vector<int> path;
    vector<vector<int>> allPaths;

    while (depth <= NODES) {
        vector<bool> visited(NODES, false);
        allPaths.clear();  // Clear previous paths

        DLS(start, target, depth, visited, path, allPaths);

        if (!allPaths.empty()) {
            cout << "Paths at depth " << depth << ": ";
            for (const auto& p : allPaths) {
                for (int node : p) {
                    cout << (char)('A' + node) << " ";
                }
                cout << endl;
            }
            cout << endl;
            return;  // Exit after printing paths for the current depth
        }

        depth++;
    }
    cout << "Target not reachable" << endl;
}

// Beam Search implementation
void BeamSearch(int start, int width) {
    vector<bool> visited(NODES, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    cout << "Beam Search Traversal: ";
    while (!pq.empty()) {
        vector<pair<int, int>> level;
        for (int i = 0; i < width && !pq.empty(); i++) {
            level.push_back(pq.top());
            pq.pop();
        }

        for (auto &p : level) {
            int node = p.second;

            if (!visited[node]) {
                cout << (char)('A' + node) << " ";
                visited[node] = true;

                for (int i = 0; i < NODES; i++) {
                    if (graph[node][i] != 0 && !visited[i]) {
                        pq.push({graph[node][i], i});
                    }
                }
            }
        }
    }
    cout << endl;
}


// A* Search implementation
void AStarSearch(int start, int target) {
    vector<int> g(NODES, INF);
    vector<int> parent(NODES, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    g[start] = 0;
    pq.push({hValue[(char)('A' + start)], start});
    
    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();
        
        if (node == target) {
            cout << "A* Path: ";
            printPath(parent, target);
            cout << endl;
            return;
        }
        
        for (int i = 0; i < NODES; i++) {
            if (graph[node][i] != 0) {
                int newG = g[node] + graph[node][i];
                int fCost = newG + hValue[(char)('A' + i)];
                
                if (newG < g[i]) {
                    g[i] = newG;
                    pq.push({fCost, i});
                    parent[i] = node;
                }
            }
        }
    }
    cout << "No path found" << endl;
}

int main() {
    char startNode = 'A';
    char targetNode = 'J';
    int choice;

    do {
        cout << "\n--- Graph Traversal Menu ---\n";
        cout << "1. Depth First Search without cost\n";
        cout << "2. Breadth First Search without cost\n";
        cout << "3. Best First Search considering only h value\n";
        cout << "4. Iterative Deepening Depth First Search\n";
        cout << "5. Beam Search (Width=2)\n";
        cout << "6. A* Search\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                DFS(getIndex(startNode));
                break;
            case 2:
                BFS(getIndex(startNode));
                break;
            case 3:
                BestFirstSearch(getIndex(startNode));
                break;
            case 4:
                IDDFS(getIndex(startNode), getIndex(targetNode));
                break;
            case 5:
                BeamSearch(getIndex(startNode), 2);
                break;
            case 6:
                AStarSearch(getIndex(startNode), getIndex(targetNode));
                break;
            case 7:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}
