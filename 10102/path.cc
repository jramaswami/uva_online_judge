// UVA :: 10102 :: The path in the colored field
// https://onlinejudge.org/external/101/10102.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const int INF{INT_MAX};
const vector<pair<int, int>> offsets{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool inbounds(size_t r, size_t c, const vector<string> &grid) {
    return r < grid.size() && c < grid[r].size();
}

int bfs(int initR, int initC, const vector<string> &grid) {
    queue<pair<int, int>> Q;
    vector<vector<int>> dist(grid.size(), vector<int>(grid.size(), INF));
    Q.emplace(initR, initC);
    dist[initR][initC] = 0;
    // BFS
    while(!Q.empty()) {
        pair<int, int> T = Q.front();
        Q.pop();
        int r{T.first}, c{T.second};
        if (grid[r][c] == '3') {
            return dist[r][c];
        }
        for (auto off : offsets) {
            int r0{r + off.first}, c0{c + off.second};
            if (inbounds(r0, c0, grid) && dist[r][c] + 1 < dist[r0][c0]) {
                dist[r0][c0] = dist[r][c] + 1;
                Q.emplace(r0, c0);
            }
        }
    }
    return INF;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int M{0};
    while (cin >> M) {
        vector<string> grid;
        grid.reserve(M);
        string junk;
        getline(cin, junk); // Read trailing newline.
        for (int r{0}; r < M; ++r) {
            string line;
            getline(cin, line);
            grid.push_back(line);
        }
        auto soln = 0;
        for (int r{0}; r < M; ++r) {
            for (int c{0}; c < M; ++c) {
                if (grid[r][c] == '1') {
                    soln = max(soln, bfs(r, c, grid));
                }
            }
        }
        cout << soln << endl;
    }
    return EXIT_SUCCESS;
}
