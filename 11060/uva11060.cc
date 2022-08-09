// UVA :: 11060 :: Beverages
// jramaswami

#include <bits/stdc++.h>

using namespace std;


struct Digraph {
    int nodeCount;
    vector<vector<int>> adj;

    Digraph() {
        nodeCount = 0;
    };

    Digraph(int n) {
        nodeCount = n;
        adj = vector<vector<int>>(nodeCount, vector<int>());
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
};

struct GraphOrder {
    Digraph graph;
    vector<int> reversePostorder;
    vector<int> postorder;
    vector<int> preorder;
    deque<bool> visited;

    GraphOrder(Digraph &g) {
        graph = g;
        visited = deque<bool>(graph.nodeCount, false);
        for (int r{0}; r < graph.nodeCount; r++) {
            if (!visited[r]) {
                dfs(r);
            }
        }
        reverse(reversePostorder.begin(), reversePostorder.end());
    }

    void dfs(int u) {
        visited[u] = true;
        preorder.push_back(u);
        for (int v : graph.adj[u]) {
            if (!visited[v]) {
                dfs(v);
            }
        }
        postorder.push_back(u);
        reversePostorder.push_back(u);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    int caseNo{1};
    while (cin >> N) {
        // Map beverage name onto on id.
        map<string, int> beverageIds;
        vector<string> beverages;
        for (int i{0}; i < N; i++) {
            string beverage;
            cin >> beverage;
            beverageIds[beverage] = i;
            beverages.push_back(beverage);
        }
        // Read graph.
        Digraph graph(N);
        int M{0};
        cin >> M;
        string line;
        getline(cin, line); // Read trailing newline.
        for (int i{0}; i < M; i++) {
            getline(cin, line);
            // Split on the first space.
            auto it = find(line.begin(), line.end(), ' ');
            string left(line.begin(), it);
            string right(it+1, line.end());
            int u = beverageIds[left];
            int v = beverageIds[right];
            graph.addEdge(u, v);
        }

        // Topological sort to get the order of the beverages.
        GraphOrder order(graph);
        auto topologicalSort = order.reversePostorder;
        cout << "Case #" << caseNo << ": "
             << "Dilbert should drink beverages in this order:";
        for (int u : topologicalSort) {
            cout << " " << beverages[u];
        }
        cout << ".\n\n";

        caseNo++;
    }
    return EXIT_SUCCESS;
}
