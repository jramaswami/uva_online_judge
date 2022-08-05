// UVA :: 11953 :: Battleships
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    for (int testCase{1}; testCase <= testCases; testCase++) {
        int soln{0};
        int dim{0};
        cin >> dim;
        vector<string> grid(dim);
        string junk;
        getline(cin, junk); // read trailing newline.
        for (int i{0}; i < dim; i++) {
            getline(cin, grid[i]);
        }

        vector<pair<int, int>> offsets{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        vector<deque<bool>> visited(dim, deque<bool>(dim, false));
        for (int initR{0}; initR < dim; initR++) {
            for (int initC{0}; initC < dim; initC++) {
                if (grid[initR][initC] != '.' && !visited[initR][initC]) {
                    int shipLength{0}, shipHits{0};
                    // BFS to find the ship.
                    deque<pair<int, int>> queue;
                    queue.emplace_back(initR, initC);
                    visited[initR][initC] = true;
                    while (!queue.empty()) {
                        int r{queue.front().first}, c{queue.front().second};
                        shipLength++;
                        if (grid[r][c] == '@') {
                            shipHits++;
                        }
                        queue.pop_front();
                        for (pair<int, int> off : offsets) {
                            int r0{r + off.first}, c0{c + off.second};
                            if (r0 >= 0 && r0 < dim && c0 >= 0 && c0 < dim) {
                                // Inbounds.
                                if (grid[r0][c0] != '.' && !visited[r0][c0]) {
                                    queue.emplace_back(r0, c0);
                                    visited[r0][c0] = true;
                                }
                            }
                        }
                    }
                    if (shipLength > shipHits) {
                        soln++;
                    }
                }
            }
        }
        cout << "Case " << testCase << ": " << soln << "\n";
    }
    return EXIT_SUCCESS;
}
