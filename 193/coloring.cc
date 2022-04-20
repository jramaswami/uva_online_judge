// UVA :: 193 :: Graph Coloring
// https://onlinejudge.org/external/1/193.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const int BLACK{1};
const int NONE{0};
const int WHITE{-1};

struct Solver {
    int nodeCount{0}, edgeCount{0};
    size_t maxBlackNodes{0};
    vector<vector<int>> adj;
    vector<int> soln, color;

    Solver(int n, int m) {
        nodeCount = n;
        edgeCount = m;
        adj = vector<vector<int>>(nodeCount + 1, vector<int>());
        color = vector<int>(nodeCount + 1, NONE);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool hasBlackNeighbors(int u) {
        for (auto v : adj[u]) {
            if (color[v] == BLACK) {
                return true;
            }
        }
        return false;
    }

    void solve(int u) {
        if (u > nodeCount) {
            // Base case.
            size_t blackNodes = count_if(
                color.begin(), color.end(),
                [](int c) {
                    return c == BLACK;
                }
            );
            if (blackNodes >= maxBlackNodes) {
                soln.clear();
                for (int i{1}; i <= nodeCount; ++i) {
                    if (color[i] == BLACK) {
                        soln.push_back(i);
                    }
                }
                maxBlackNodes = blackNodes;
            }
        } else {
            // Can this node be black?
            if (!hasBlackNeighbors(u)) {
                color[u] = BLACK;
                solve(u + 1);
                color[u] = NONE;
            }

            // A node can always be white.
            color[u] = WHITE;
            solve(u + 1);
            color[u] = NONE;
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while (testCases--) {
        int nodeCount{0}, edgeCount{0};
        cin >> nodeCount >> edgeCount;
        Solver solver(nodeCount, edgeCount);
        for (int i{0}; i < edgeCount; ++i) {
            int u{0}, v{0};
            cin >> u >> v;
            solver.addEdge(u, v);
        }
        solver.solve(1);
        cout << solver.maxBlackNodes << endl;
        for (size_t i{0}; i < solver.soln.size(); ++i) {
            if (i) {
                cout << " ";
            }
            cout << solver.soln[i];
        }
        cout << endl;
    }
    return EXIT_SUCCESS;
}
