// UVA :: 11080 :: Place the Guards
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int T{0};
    cin >> T;
    while (T--) {
        // Read graph.
        int nodeCount{0}, edgeCount{0};
        cin >> nodeCount >> edgeCount;
        /* cerr << "nodeCount=" << nodeCount << " edgeCount=" << edgeCount << endl; */
        vector<vector<int>> graph(nodeCount, vector<int>());
        for (int i{0}; i < edgeCount; i++) {
            int u{0}, v{0};
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        // Test bipartiteness.
        bool isBipartite{true};
        vector<int> color(nodeCount, NONE);
        int soln{0};
        for (int r{0}; r < nodeCount; r++) {
            if (color[r] == NONE) {
                int blackGuards{0};
                int whiteGuards{1};
                queue<int> Q;
                Q.push(r);
                color[r] = WHITE;
                while (!Q.empty() && isBipartite) {
                    int u{Q.front()};
                    int nextColor{otherColor(color[u])};
                    Q.pop();
                    for (int v : graph[u]) {
                        if (color[v] == NONE) {
                            color[v] = nextColor;
                            Q.push(v);
                            if (nextColor == BLACK) {
                                blackGuards++;
                            } else {
                                whiteGuards++;
                            }
                        } else if (color[u] == color[v]) {
                            isBipartite = false;
                            break;
                        }
                    }
                }
                // Did we need white and black guards?
                if (whiteGuards && blackGuards) {
                    // Then choose the minimum set.
                    soln = soln + min(whiteGuards, blackGuards);
                } else {
                    // We only needed white guards.
                    soln += whiteGuards;
                }
            }
            if (!isBipartite) {
                break;
            }

        }
        /* cerr << "isBipartite=" << isBipartite << endl; */
        /* copy(color.begin(), color.end(), ostream_iterator<int>(cerr, " ")); */
        /* cerr << endl; */
        if (isBipartite) {
            cout << soln << "\n";
        } else {
            cout << "-1\n";
        }
    }
    return EXIT_SUCCESS;
}
