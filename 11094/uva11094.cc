// UVA :: 11094 :: Continents
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int rowCount{0}, colCount{0};
    string junk;
    while (cin >> rowCount >> colCount) {
        getline(cin, junk);  // Read trailing newline.
        vector<string> grid(rowCount);
        for (int r{0}; r < rowCount; r++) {
            getline(cin, grid[r]);
        }
        int kingRow{0}, kingCol{0};
        cin >> kingRow >> kingCol;
        char land{grid[kingRow][kingCol]};

        int biggestTarget{0};
        vector<pair<int, int>> offsets{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        vector<deque<bool>> visited(rowCount, deque<bool>(colCount, false));
        for (int r{0}; r < rowCount; r++) {
            for (int c{0}; c < colCount; c++) {
                if (grid[r][c] == land && !visited[r][c]) {
                    bool kingsContinent{false};
                    int continentSize{0};
                    deque<pair<int, int>> queue;
                    queue.emplace_back(r, c);
                    visited[r][c] = true;
                    while (!queue.empty()) {
                        int r0{queue.front().first}, c0{queue.front().second};
                        queue.pop_front();
                        continentSize++;
                        if (r0 == kingRow && c0 == kingCol) {
                            kingsContinent = true;
                        }
                        for (pair<int, int> off : offsets) {
                            int r1{r0 + off.first};
                            if (r1 < 0 || r1 >= rowCount) {
                                continue;
                            }
                            // Columns continue to other side of grid.
                            int c1{(colCount + c0 + off.second) % colCount};
                            // Is the unvisited land?
                            if (grid[r1][c1] == land && !visited[r1][c1]){
                                queue.emplace_back(r1, c1);
                                visited[r1][c1] = true;
                            }
                        }
                    }
                    if (!kingsContinent) {
                        biggestTarget = max(biggestTarget, continentSize);
                    }
                }
            }
        }
        cout << biggestTarget << "\n";
    }
    return EXIT_SUCCESS;
}
