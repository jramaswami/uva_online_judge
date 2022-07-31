// UVA :: 12442 :: Forwarding Emails
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    for (int t{1}; t <= testCases; t++) {
        int nodeCount{0};
        cin >> nodeCount;
        vector<vector<int>> graph(nodeCount+1, vector<int>());
        for (int i{0}; i < nodeCount; i++) {
            int u{0}, v{0};
            cin >> u >> v;
            graph[u].push_back(v);
        }
        // Simplest possible solution.
        int bestNode{1}, maxChildren{0};
        for (int r{1}; r <= nodeCount; r++) {
            deque<bool> visited(nodeCount+1, false);
            deque<int> queue;
            queue.push_back(r);
            visited[r] = true;
            int children{0};
            while (!queue.empty()) {
                int u = queue.front();
                queue.pop_front();
                for (int v : graph[u]) {
                    if (!visited[v]) {
                        children++;
                        visited[v] = true;
                        queue.push_back(v);
                    }
                }
            }
            if (children > maxChildren) {
                maxChildren = children;
                bestNode = r;
            }
        }
        cout << "Case " << t << ": " << bestNode << "\n";
    }
    return EXIT_SUCCESS;
}