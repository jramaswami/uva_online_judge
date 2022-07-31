// UVA :: 12442 :: Forwarding Emails
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Digraph {
    int N;
    vector<vector<int>> graph, rgraph;

    Digraph() {
        Digraph(0);
    }

    Digraph(int n) {
        N = n;
        graph = vector<vector<int>>(N+1, vector<int>());
    }

    void addEdge(int u, int v) {
        graph[u].push_back(v);
    }

    Digraph reverse() {
        Digraph graph0(N);
        for (int u{1}; u <= N; u++) {
            for (int v : graph[u]) {
                graph0.addEdge(v, u);
            }
        }
        return graph0;
    }
};

struct Order {
    Digraph graph;
    vector<int> revPost;
    deque<bool> visited;

    Order(Digraph &g) {
        graph = g;
        visited = deque<bool>(graph.N+1);
        for (int u{1}; u <= graph.N; u++) {
            if (!visited[u]) {
                dfs(u);
            }
        }
    }

    void dfs(int u) {
        visited[u] = true;
        for (int v : graph.graph[u]) {
            if (!visited[v]) {
                dfs(v);
            }
        }
        revPost.push_back(u);
    }
};

struct Kosaraju {
    Digraph graph;
    int count{1};
    vector<int> id, size;
    deque<bool> visited;

    Kosaraju() {
    }

    Kosaraju(Digraph &g) {
        graph = g;
        Digraph rgraph = graph.reverse();
        id = vector<int>(graph.N+1);
        size = vector<int>{0};
        vector<int> rorder = Order(rgraph).revPost;
        for (int u : rorder) {
            if (!visited[u]) {
                size.push_back(0);
                dfs(u);
                count++;
            }
        }
    }

    void dfs(int u) {
        visited[u] = true;
        id[u] = count;
        size[count]++;
        for (int v : graph.graph[u]) {
            if (!visited[v]) {

            }
        }
    }

    Digraph condense() {
        Digraph graph0(count);
        for (int u{1}; u <= graph.N; u++) {
            for (int v : graph.graph[u]) {
                if (id[u] != id[v]) {
                    graph0.addEdge(id[u], id[v]);
                }
            }
        }
        return graph0;
    }
};

struct Solver {
    Digraph graph, condensed;
    Kosaraju kosaraju;
    deque<bool> visited;

    Solver(Digraph &g) {
        graph = g;
        kosaraju = Kosaraju(graph);
        condensed = kosaraju.condense();
        visited = deque<bool>(condensed.N+1, false);
    }

    int dfs(int u) {
        visited[u] = true;
        int result = kosaraju.size[u];
        for (int v : condensed.graph[u]) {
            if (!visited[v]) {
                result += dfs(v);
            }
        }
        return result;
    }

    int solve() {
        int maxChildren{0};
        int bestNode{1};
        for (int u{1}; u <= condensed.N; u++) {
            fill(visited.begin(), visited.end(), false);
            int children = dfs(u);
            if (children > maxChildren) {
                maxChildren = children;
                bestNode = u;
            }
        }
        return bestNode;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    for (int t{0}; t < testCases; t++) {
        int nodeCount{0};
        cin >> nodeCount;
        Digraph graph(nodeCount);
        for (int i{0}; i < nodeCount; i++) {
            int u{0}, v{0};
            cin >> u >> v;
            graph.addEdge(u, v);
        }
        int soln = Solver(graph).solve();
        cout << "Case " << t << ": " << soln << "\n";
    }
    return EXIT_SUCCESS;
}
