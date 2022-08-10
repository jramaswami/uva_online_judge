// UVA :: 872 :: Ordering
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Solver {

    vector<int> indegree;
    bitset<26> ready;
    vector<vector<char>> graph;
    vector<string> soln;
    string order;
    bool isDAG{true};
    vector<char> color;
    vector<char> parent;

    Solver(string &letters) {
        indegree = vector<int>(26, -1);
        graph = vector<vector<char>>(26, vector<char>());
        color = vector<char>(26, 0);
        parent = vector<char>(26, -1);
        for (size_t i{0}; i < letters.size(); i += 2) {
            indegree[letters.at(i) - 'A'] = 0;
        }
    };

    void addConstraint(char a, char b) {
        indegree[b - 'A']++;
        graph[a - 'A'].push_back(b - 'A');
    }

    void solve0() {
        int t{0};
        for (char u{0}; u < 26; u++) {
            if (indegree[u] == 0) {
                // Recurse
                for (char v : graph[u]) {
                    indegree[v]--;
                }
                order.push_back(u + 'A');
                indegree[u] = -1;
                solve0();
                for (char v : graph[u]) {
                    indegree[v]++;
                }
                order.pop_back();
                indegree[u] = 0;
            } else if (indegree[u] == -1) {
                t++;
            }
        }
        if (t == 26) {
            soln.push_back("");
            for (size_t i{0}; i < order.size(); i++) {
                if (i) {
                    soln.back().push_back(' ');
                }
                soln.back().push_back(order[i]);
            }
        }
    }

    bool dfs(char u) {
        color[u] = 1;
        for (char v : graph[u]) {
            if (color[v] == 0) {
                parent[v] = u;
                if (dfs(v)) {
                    isDAG = false;
                    return true;
                }
            } else if (color[v] == 1) {
                isDAG = false;
                return true;
            }
        }
        color[u] = 2;
        return false;
    }

    void solve() {
        for (char u{0}; u < 26; u++) {
            if (color[u] == 0 && dfs(u)) {
                break;
            }
        }
        if (isDAG) {
            solve0();
            sort(soln.begin(), soln.end());
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int T{0};
    cin >> T;
    string line;
    getline(cin, line);  // Read trailing newline.
    while (T--) {
        getline(cin, line);  // Read blank line.
        getline(cin, line);  // Read the letters.
        Solver solver(line);
        getline(cin, line);  // Read the constraints.
        for (size_t i{0}; i < line.size(); i += 4) {
            solver.addConstraint(line.at(i), line.at(i+2));
        }
        solver.solve();
        if (solver.isDAG) {
            copy(solver.soln.begin(), solver.soln.end(), ostream_iterator<string>(cout, "\n"));
            cout << "\n";
        } else {
            cout << "NO\n\n";
        }
    }
    return EXIT_SUCCESS;
}
