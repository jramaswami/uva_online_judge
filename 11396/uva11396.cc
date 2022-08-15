// UVA :: 11396 :: Claw Decomposition
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const int NONE{-1};
const int WHITE{0};
const int BLACK{1};

int otherColor(int c) {
    if (c == WHITE) {
        return BLACK;
    }
    return WHITE;
}

struct Graph {
    int nodeCount{0};
    vector<vector<int>> adj;
    bool isBipartite{true};
    vector<int> color;

    Graph(int n) {
        nodeCount = n;
        adj = vector<vector<int>>(nodeCount+1, vector<int>());
        color = vector<int>(nodeCount+1, NONE);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void bfs(int r) {
        color[r] = WHITE;
        queue<int> bfsQueue;
        bfsQueue.push(r);
        while (!bfsQueue.empty() && isBipartite) {
            int u{bfsQueue.front()};
            bfsQueue.pop();
            for (int v : adj[u]) {
                if (color[v] == NONE) {
                    color[v] = otherColor(color[u]);
                    bfsQueue.push(v);
                } else if (color[u] == color[v]) {
                    isBipartite = false;
                    return;
                }
            }
        }
    }

    bool solve() {
        for (int r{1}; r <= nodeCount; r++) {
            if (color[r] == NONE) {
                bfs(r);
            }
            if (!isBipartite) {
                break;
            }
        }
        return isBipartite;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int nodeCount{0};
    cin >> nodeCount;
    while (nodeCount) {
        // Read graph.
        Graph graph(nodeCount);
        for(;;) {
            int u{0}, v{0};
            cin >> u >> v;
            if (u == 0 && v == 0) {
                break;
            }
            graph.addEdge(u, v);
        }

        // Is Graph Bipartite?
        bool isBipartite{graph.solve()};
        cout << (isBipartite ? "YES\n" : "NO\n");

        cin >> nodeCount;
    }
    return EXIT_SUCCESS;
}
