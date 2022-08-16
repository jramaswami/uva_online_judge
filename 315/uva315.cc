// UVA :: 315 :: Network
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Tarjan {
    int nodeCount, timer{0};
    vector<unordered_set<int>> adj;
    vector<int> disc, low, parent, children;
    deque<bool> articulation;

    Tarjan(int n) {
        nodeCount = n;
        adj = vector<unordered_set<int>>(nodeCount+1, unordered_set<int>());
        disc = vector<int>(nodeCount+1, -1);
        low = vector<int>(nodeCount+1, -1);
        parent = vector<int>(nodeCount+1, -1);
        children = vector<int>(nodeCount+1, 0);
        articulation = deque<bool>(nodeCount+1, false);
    }

    void addEdge(int u, int v) {
        adj[u].insert(v);
        adj[v].insert(u);
    }

    void dfs(int u) {
        disc[u] = low[u] = timer++;
        for (int v : adj[u]) {
            if (disc[v] == -1) {
                children[u]++;
                parent[v] = u;
                dfs(v);
                if (low[v] >= disc[u]) {
                    articulation[u] = true;
                }
                low[u] = min(low[u], low[v]);
            } else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    size_t countArticulationPoints() {
        for (int r{1}; r <= nodeCount; r++) {
            if (disc[r] == -1) {
                dfs(r);
                articulation[r] = (children[r] > 1);
            }
        }
        return count_if(
            articulation.begin(), articulation.end(),
            [](int t) { return t; }
        );
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int nodeCount{0};
    cin >> nodeCount;
    while (nodeCount) {
        // Read graph into adjacency matrix.
        Tarjan tarjan(nodeCount);
        string line;
        getline(cin, line);  // Read trailing newline.
        getline(cin, line);
        while (line != "0") {
            istringstream iss(line);
            int u{0};
            iss >> u;
            int v{0};
            while (iss >> v) {
                tarjan.addEdge(u, v);
            }
            getline(cin, line);
        }
        cout << tarjan.countArticulationPoints() << "\n";
        cin >> nodeCount;
    }
    return EXIT_SUCCESS;
}
