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
        vector<int> graph(nodeCount+1, -1);
        for (int i{0}; i < nodeCount; i++) {
            int u{0}, v{0};
            cin >> u >> v;
            graph[u] = v;
        }

        // Find any cycles and cache their size.
        vector<int> pathIndex(nodeCount + 1, -1);
        vector<int> cache(nodeCount + 1, -1);
        for (int u{1}; u <= nodeCount; u++) {
            if (pathIndex[u] >= 0) {
                continue;
            }
            vector<int> stack;
            stack.push_back(u);
            int pi{0};
            pathIndex[u] = pi;
            bool ok{true};
            while (ok) {
                int v = graph[stack.back()];
                if (pathIndex[v] >= 0) {
                    // We have visited this node before.
                    int p{pathIndex[v]};
                    if (p <= pi && stack[p] == v) {
                        // If the node is in the stack, then this is a cycle.
                        // Cache the length of the cycle for all members of
                        // cycle, removing them from the stack.
                        int cycleLength = pi - pathIndex[v] + 1;
                        while (stack.back() != v) {
                            cache[stack.back()] = cycleLength;
                            stack.pop_back();
                        }
                        cache[stack.back()] = cycleLength;
                        stack.pop_back();
                        ok = false;
                    } else {
                        // If the node is not in our stack then we have run
                        // into a cached node.
                        ok = false;
                    }
                    // Any nodes on the stack are connected to a cached node.
                    while(!stack.empty()) {
                        // Cache me + the number of children for my child.
                        cache[stack.back()] = 1 + cache[graph[stack.back()]];
                        stack.pop_back();
                    }
                } else {
                    stack.push_back(v);
                    pi++;
                    pathIndex[v] = pi;
                }
            }
        }

        // Find the best node.
        int bestNode{-1};
        int maxChildren{-1};
        for (int u{1}; u <= nodeCount; u++) {
            if (cache[u] > maxChildren) {
                bestNode = u;
                maxChildren = cache[u];
            }
        }
        cout << "Case " << t << ": " << bestNode << "\n";
    }
    return EXIT_SUCCESS;
}