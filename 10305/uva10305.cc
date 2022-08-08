// UVA :: 10305 :: Ordering Tasks
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Digraph {
    int nodeCount{0};
    vector<vector<int>> adj;
    deque<bool> visited;
    deque<int> revPost;

    Digraph(int n) {
        nodeCount = n;
        adj = vector<vector<int>>(nodeCount+1, vector<int>());
        visited = deque<bool>(nodeCount+1, false);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void reversePostOrder(int u) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                reversePostOrder(v);
            }
        }
        revPost.push_front(u);
    }

    deque<int> solve() {
        revPost.clear();
        for (int u{1}; u <= nodeCount; u++) {
            if (!visited[u]) {
                reversePostOrder(u);
            }
        }
        return revPost;
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int nodeCount{0}, edgeCount{0};
    cin >> nodeCount >> edgeCount;
    while (nodeCount && edgeCount) {
        // Read graph.
        Digraph graph(nodeCount);
        for (int i{0}; i < edgeCount; i++) {
            int u{0}, v{0};
            cin >> u >> v;
            graph.addEdge(u, v);
        }
        deque<int> rp{graph.solve()};
        for (size_t i{0}; i < rp.size(); i++) {
            if (i) {
                cout << " ";
            }
            cout << rp[i];
        }
        cout << "\n";
        cin >> nodeCount >> edgeCount;
    }
    return EXIT_SUCCESS;
}
