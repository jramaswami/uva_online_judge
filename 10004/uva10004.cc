// UVA :: 10004 :: Bicoloring
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const int NONE{-1};
const int WHITE{0};
const int BLACK{1};

int otherColor(int color) {
    if (color == WHITE) {
        return BLACK;
    }
    return WHITE;
}

struct Graph {
    int nodeCount;
    vector<vector<int>> adj;
    vector<int> color;
    bool isBipartite{true};

    Graph(int N) {
        nodeCount = N;
        adj = vector<vector<int>>(nodeCount, vector<int>());
        color = vector<int>(nodeCount, NONE);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void paintNodes(int r) {
        queue<int> Q;
        color[r] = WHITE;
        Q.push(r);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            int nextColor = otherColor(color[u]);
            for (int v : adj[u]) {
                if (color[v] == NONE) {
                    color[v] = nextColor;
                    Q.push(v);
                } else if (color[v] == color[u]) {
                    isBipartite = false;
                    return;
                }
            }
        }
    }

    void solve() {
        for (int r{0}; r < nodeCount; r++) {
            if (color[r] == NONE) {
                paintNodes(r);
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    cin >> N;
    while (N) {
        // Read graph.
        Graph graph(N);
        int M{0};
        cin >> M;
        for (int i{0}; i < M; i++) {
            int u{0}, v{0};
            cin >> u >> v;
            graph.addEdge(u, v);
        }

        graph.solve();
        if (graph.isBipartite) {
            cout << "BICOLORABLE.\n";
        } else {
            cout << "NOT BICOLORABLE.\n";
        }

        cin >> N;
    }
    return EXIT_SUCCESS;
}
