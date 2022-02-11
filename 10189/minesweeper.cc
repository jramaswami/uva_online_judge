// UVA :: 10189 :: Minesweeper
// https://onlinejudge.org/external/101/10189.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;


class Grid {
        vector<vector<int>> grid;
        vector<pair<int, int>> offsets {
            {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
            {1, 0}, {1, -1}, {0, -1}, {-1, -1}
        };

    public:
        int rowCount;
        int colCount;

        Grid (int r, int c) {
            rowCount = r;
            colCount = c;
            grid = vector<vector<int>>(rowCount, vector<int>(colCount, 0));
        }

        bool inbounds(int r, int c) {
            return r >= 0 && r < rowCount && c >= 0 && c < colCount;
        }

        vector<pair<int, int>> neighbors(int r, int c) {
            vector<pair<int, int>> result;
            result.reserve(8);
            for (auto off : offsets) {
                int r0 = r + off.first;
                int c0 = c + off.second;
                if (inbounds(r0, c0)) {
                    result.emplace_back(r0, c0);
                }
            }
            return result;
        }

        vector<int>& operator[](int r) {
            return grid[r];
        }

        const vector<int>& operator[](int r) const {
            return grid[r];
        }
};

ostream& operator<<(ostream& os, const Grid &grid) {
    for (int r{0}; r < grid.rowCount; ++r) {
        for (int c{0}; c < grid.colCount; ++c) {
            if (grid[r][c] == -1) {
                os << '*';
            } else {
                os << grid[r][c];
            }
        }
        os << endl;
    }
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int rowCount, colCount;
    string line;
    cin >> rowCount >> colCount;
    int fieldNumber{1};
    while (rowCount && colCount) {
        getline(cin, line); // Read the trailing newline.
        Grid grid(rowCount, colCount);
        for (int r{0}; r < rowCount; ++r) {
            getline(cin, line);
            for (int c{0}; c < colCount; ++c) {
                if (line.at(c) == '*') {
                    // Mark mines with -1.
                    grid[r][c] = -1;
                    // Now add to mine count of all neighbors.
                    for (auto neighbor : grid.neighbors(r, c)) {
                        int r0 = neighbor.first;
                        int c0 = neighbor.second;
                        if (grid[r0][c0] >= 0) {
                            grid[r0][c0]++;
                        }
                    }
                }
            }
        }
        if (fieldNumber > 1) {
            cout << endl;
        }
        cout << "Field #" << fieldNumber << ":" << endl << grid;
        cin >> rowCount >> colCount;
        fieldNumber++;
    }
    return EXIT_SUCCESS;
}
