// UVA :: 11906 :: Knight in War Grid
// jramaswami

// TODO: Change counting to destination not source.

#include <bits/stdc++.h>

using namespace std;

const int UNVISITED{0};
const int WATER{-1};
const int VISITED{1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    for (int testCase{1}; testCase <= testCases; testCase++) {
        int R{0}, C{0}, M{0}, N{0};
        cin >> R >> C >> M >> N;
        vector<vector<int>> visited(R, vector<int>(C, UNVISITED));
        vector<vector<int>> dp(R, vector<int>(C, 0));
        vector<pair<int, int>> offsets{
            {M, N}, {-M, N}, {M, -N}, {-M, -N},
            {N, M}, {-N, M}, {N, -M}, {-N, -M}
        };
        sort(offsets.begin(), offsets.end());
        auto it = unique(offsets.begin(), offsets.end());
        offsets.resize(distance(offsets.begin(), it));
        int W{0};
        cin >> W;
        for (int w{0}; w < W; w++) {
            int r{0}, c{0};
            cin >> r >> c;
            visited[r][c] = WATER;
            dp[r][c] = INT_MIN;
        }
        int oddCells{0}, evenCells{0};
        deque<pair<int, int>> Q;
        if (visited[0][0] != WATER) {
            visited[0][0] = VISITED;
            Q.emplace_back(0, 0);
        }
        while (!Q.empty()) {
            pair<int, int> t = Q.front();
            Q.pop_front();
            int r = t.first;
            int c = t.second;
            int neighbors = 0;
            for (pair<int, int> off : offsets) {
                int r0 = r + off.first;
                int c0 = c + off.second;
                if (r0 >= 0 && r0 < R && c0 >= 0 && c0 < C) {
                    if (visited[r0][c0] != WATER) {
                        neighbors++;
                    }
                    if (visited[r0][c0] == UNVISITED) {
                        visited[r0][c0] = VISITED;
                        Q.emplace_back(r0, c0);
                    }
                }
            }
            if (neighbors % 2) {
                oddCells++;
            } else {
                evenCells++;
            }
        }
        cout << "Case " << testCase << ": " << evenCells << " " << oddCells << "\n";
    }
    return EXIT_SUCCESS;
}
