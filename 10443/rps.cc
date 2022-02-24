// UVA :: 10443 :: Rock, Scissors, Paper
// https://onlinejudge.org/external/104/10443.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

typedef vector<char> row_t;
typedef vector<row_t> grid_t;

const vector<pair<int, int>> neighborOffsets{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool inbounds(int r, int c, const grid_t &grid) {
    return r >= 0 && r < static_cast<int>(grid.size()) &&
           c >= 0 && c < static_cast<int>(grid[r].size());
}

vector<pair<int, int>> getNeighbors(int r, int c, const grid_t &grid) {
    vector<pair<int, int>> neighbors;
    for (auto off : neighborOffsets) {
        int r0{r + off.first};
        int c0{c + off.second};
        if (inbounds(r0, c0, grid)) {
            neighbors.emplace_back(r0, c0);
        }
    }
    return neighbors;
}

bool attackerWins(char attacker, char defender) {
    if (attacker == 'R' && defender == 'S') {
        return true;
    } else if (attacker == 'S' && defender == 'P') {
        return true;
    } else if (attacker == 'P' && defender == 'R') {
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while (testCases) {

        int rowCount{0}, colCount{0}, stopDay{0};
        cin >> rowCount >> colCount >> stopDay;

        string line;
        getline(cin, line);   // Read trailing newline.

        grid_t currDay(rowCount, row_t(colCount, 'x'));
        grid_t nextDay(rowCount, row_t(colCount, 'x'));

        // Read grid.
        for (int r{0}; r < rowCount; ++r) {
            getline(cin, line);
            for (int c{0}; c < colCount; ++c) {
                currDay[r][c] = line[c];
            }
        }

        // Tick through days.
        for (int d{0}; d < stopDay; ++d) {
            // Copy current status to next day.
            for (int r{0}; r < rowCount; ++r) {
                for (int c{0}; c < colCount; ++c) {
                    nextDay[r][c] = currDay[r][c];
                }
            }

            // Make changes
            for (int r{0}; r < rowCount; ++r) {
                for (int c{0}; c < colCount; ++c) {
                    char attacker{currDay[r][c]};
                    for (auto neighbor : getNeighbors(r, c, currDay)) {
                        char defender{currDay[neighbor.first][neighbor.second]};
                        if (attackerWins(attacker, defender)) {
                            nextDay[neighbor.first][neighbor.second] = attacker;
                        }
                    }
                }
            }
            swap(currDay, nextDay);
        }

        // Write final day to cout.
        for (auto row : currDay) {
            copy(row.begin(), row.end(), ostream_iterator<char>(cout, ""));
            cout << endl;
        }
        if (testCases > 1) {
            cout << endl;
        }

        testCases--;
    }

    return EXIT_SUCCESS;
}
