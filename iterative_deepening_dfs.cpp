#include <iostream>
#include <vector>

using namespace std;

class Graph {
int v;
    vector<vector<int>> adjlist;

public:
    Graph(int v) {
        this->v = v;
        adjlist = vector<vector<int>>(v);
    }

    void addedge(int u, int v) {
        adjlist[u].push_back(v);
        adjlist[v].push_back(u); 
    }

    void display() {
        for (int i = 0; i < v; i++) {
            cout << "Vertex " << i << " :";
            for (int j : adjlist[i]) {
                cout << " -> " << j;
            }
            cout << endl;
        }
    }

    void dfsrec(int node, vector<bool> &visited, int depth) {
        if (depth == 0) return;  // Exit condition when depth limit is reached

        visited[node] = true;
        cout << node << " ";

        for (int i : adjlist[node]) {
            if (!visited[i]) {
                dfsrec(i, visited, depth - 1);  // Reduce depth on each recursive call
            }
        }
    }

    void iddfs(int start, int max_depth) {
        for (int depth = 1; depth <= max_depth; depth++) {
            vector<bool> visited(v, false);
            cout << "\nDFS with depth " << depth << ": ";
            dfsrec(start, visited, depth);
            cout << endl;
        }
    }
};
int main() {
    Graph g(21);  
    g.addedge(0, 1);
    g.addedge(0, 2);
    g.addedge(1, 3);
    g.addedge(1,8);
    g.addedge(2, 4);
    g.addedge(2, 5);
    g.addedge(3, 6);
    g.addedge(3,7);
    g.addedge(4, 7);
    g.addedge(5, 8);
    g.addedge(6, 9);
    g.addedge(7, 10);
    g.addedge(8, 11);
    g.addedge(9, 12);
    g.addedge(10, 13);
    g.addedge(11, 14);
    g.addedge(12, 15);
    g.addedge(13, 16);
    g.addedge(14, 17);
    g.addedge(15,17);
    g.addedge(15, 18);
    g.addedge(16, 19);
    g.addedge(17, 20);
    

    cout << "Display:\n";
    g.display();

    cout << "\nIterative Deepening DFS starting from vertex 0 with depth from 1 to 3:\n";
    g.iddfs(0, 3);

    return 0;
}
