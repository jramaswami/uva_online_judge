// UVA :: 12655 :: Trucks
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4384

#include <bits/stdc++.h>

using namespace std;

// UNION FIND
struct UnionFind {
    vector<int> link;
    vector<int> size;

    UnionFind(int N) {
        link.resize(N);
        size.resize(N);
        iota(link.begin(), link.end(), 0);
        fill(size.begin(), size.end(), 1);
    }

    // Find with path compression.
    int find(int x) {
        if (x == link[x]) {
            return x;
        }
        return link[x] = find(link[x]);
    }

    // Connect components of a and b (by size).
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (size[a] < size[b]) {
            swap(a, b);
        }
        size[a] += size[b];
        link[b] = a;
    }

    // Return true if a and b are in the same component.
    bool same(int a, int b) {
        return find(a) == find(b);
    }
};

// KRUSKAL
using adjacency_t = vector<vector<pair<int, int>>>;

struct Edge {
    int u{0};
    int v{0};
    int wt{0};
    
    Edge() {}
    Edge(int u_, int v_, int w): u{u_}, v{v_}, wt{w} { }

};

bool operator< (const Edge &lhs, const Edge &rhs) {
    return lhs.wt < rhs.wt;
}

bool operator> (const Edge &lhs, const Edge &rhs) {
    return lhs.wt > rhs.wt;
}

adjacency_t kruskal(vector<Edge> &edges, int nodeCount) {
    adjacency_t adj(nodeCount);
    // Greater in this case because we want the max spanning tree.
    sort(edges.begin(), edges.end(), greater<Edge>());
    UnionFind uf(nodeCount);
    for (auto edge : edges) {
        if (!uf.same(edge.u, edge.v)) {
            uf.unite(edge.u, edge.v);
            adj[edge.u].emplace_back(edge.v, edge.wt);
            adj[edge.v].emplace_back(edge.u, edge.wt);
        }
    }
    return adj;
}


const int INF{numeric_limits<int>::max()};

// Tree for LCA using Binary Lifting
struct Tree {
    int N;
    int D;  // Max depth for binary lifting table.
    vector<vector<int>> par;  // Binary lifting table for parent [node][level].
    vector<vector<int>> mns;  // Binary lifting table for maxes.
    vector<int> level;

    Tree(int root, const vector<vector<pair<int, int>>> &adj) {
        N = static_cast<int>(adj.size());
        D = static_cast<int>(ceil(log2(N)));
        par = vector<vector<int>>(adj.size(), vector<int>(D+1, -1));
        mns = vector<vector<int>>(adj.size(), vector<int>(D+1, INF));
        level.resize(adj.size());
        dfs(root, root, INF, 0, adj);
    }

    void dfs(int node, int parent, int wt, int lvl, const vector<vector<pair<int, int>>> &adj) {
        // Set parent of current node.
        par[node][0] = parent;
        mns[node][0] = wt;
        level[node] = lvl;
        // Fill in the rest of the bl table for node.
        for (int i{1}; i <= D; ++i) {
            par[node][i] = par[par[node][i-1]][i-1];
            mns[node][i] = min(mns[node][i-1], mns[par[node][i-1]][i-1]);
        }
        // Recurse on DFS.
        for (auto edge : adj[node]) {
            auto neighbor = edge.first;
            auto wt0 = edge.second;
            if (neighbor != parent) {
                dfs(neighbor, node, wt0, lvl+1, adj);
            }
        }
    }

    int min_query(int u, int v) {
        int soln{INF};

        // Make sure that v is the node deeper in the tree.
        if (level[u] > level[v]) {
            swap(u, v);
        }

        // Move v up until it is at the same depth as v.
        int delta = level[v] - level[u];
        while (delta) {
            // Determine the length of the jump.
            int i = static_cast<int>(log2(delta));
            // Update max with value from jump.
            soln = min(soln, mns[v][i]);
            // Make jump.
            v = par[v][i];
            delta -= (1 << i);
        }

        // Find lca(u, v).
        while (u != v) {
            // Biggest jump possible.
            int i = static_cast<int>(log2(level[u]));
            // Find lowest jump where the different are the same.
            while (i > 0 && par[u][i] == par[v][i]) {
                i--;
            }
            // Update solution.
            soln = min(soln, mns[u][i]);
            soln = min(soln, mns[v][i]);
            // Make jumps.
            u = par[u][i];
            v = par[v][i];
        }
        return soln;
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (1) {
        int nodeCount, edgeCount, queryCount;
        cin >> nodeCount;
        if (cin.eof()) {
            break;
        }
        cin >> edgeCount >> queryCount;
        vector<Edge> edges;
        edges.reserve(edgeCount);
        for (int i{0}; i < edgeCount; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back(Edge(u, v, w));
        }

        // First, transform graph into maximum spanning tree.
        adjacency_t adj = kruskal(edges, nodeCount+1);
        // Make tree for binary lifting.
        Tree tree(1, adj);

        for (int i{0}; i < queryCount; ++i) {
            int u, v;
            cin >> u >> v;
            cout << tree.min_query(u, v) << "\n";
        }
    }
    return EXIT_SUCCESS;
}
