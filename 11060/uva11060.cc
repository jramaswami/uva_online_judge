// UVA :: 11060 :: Beverages
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    int caseNo{1};
    while (cin >> N) {
        // Read beverages
        vector<string> bs;
        bs.reserve(N);
        map<string, int> bid;
        for (int i{0}; i < N; i++) {
            string b;
            cin >> b;
            bs.push_back(b);
            bid[b] = i;
        }
        // Read graph.
        int M{0};
        cin >> M;
        string line;
        getline(cin, line); // Read trailing newline.
        vector<vector<int>> graph(N, vector<int>());
        vector<int> indegree(N, 0);
        for (int i{0}; i < M; i++) {
            getline(cin, line);
            // Split on the first space.
            auto it = find(line.begin(), line.end(), ' ');
            string a(line.begin(), it);
            string b(it+1, line.end());
            int u{bid[a]};
            int v{bid[b]};
            graph[u].push_back(v);
            indegree[v]++;
        }

        vector<int> soln;
        for (int i{0}; i < N; i++) {
            auto it = find(indegree.begin(), indegree.end(), 0);
            int u = static_cast<int>(distance(indegree.begin(), it));
            soln.push_back(u);
            indegree[u] = -1;
            for (int v : graph[u]) {
                indegree[v]--;
            }
        }

        cout << "Case #" << caseNo << ": "
             << "Dilbert should drink beverages in this order:";
        for (size_t i{0}; i < soln.size(); i++) {
            cout << " " << bs[soln[i]];
        }
        cout << ".\n\n";

        caseNo++;
    }
    return EXIT_SUCCESS;
}
