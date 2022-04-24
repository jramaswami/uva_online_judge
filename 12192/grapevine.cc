// UVA :: 12192 :: Grapevine
// https://onlinejudge.org/external/121/12192.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;


struct Grid {
    int rowCount{0}, colCount{0};
    vector<vector<int>> grid;

    Grid(int _r, int _c) {
        rowCount = _r;
        colCount = _c;
        grid = vector<vector<int>>(rowCount, vector<int>());
    }

    void readGrid(istream &is) {
        for (int r{0}; r < rowCount; ++r) {
            grid[r].reserve(colCount);
            copy_n(istream_iterator<int>(is), colCount, back_inserter(grid[r]));
        }
    }

    bool inbounds(int r, int c) {
        return r >= 0 && r < rowCount && c >= 0 && c < colCount;
    }

    int query(int rangeMin, int rangeMax) {
        int soln{0};
        for (int r{0}; r < rowCount; ++r) {
            auto it = lower_bound(grid[r].begin(), grid[r].end(), rangeMin);
            int r0{r};
            int c0{static_cast<int>(distance(grid[r].begin(), it))};
            int result{0};
            while (inbounds(r0, c0) && grid[r0][c0] <= rangeMax) {
                result++;
                r0++;
                c0++;
            }
            soln = max(soln, result);
        }
        return soln;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int rowCount{0}, colCount{0};
    cin >> rowCount >> colCount;
    while (rowCount || colCount) {
        Grid grid(rowCount, colCount);
        grid.readGrid(cin);
        int queryCount{0};
        cin >> queryCount;
        for (int q{0}; q < queryCount; ++q) {
            int rangeMin{0}, rangeMax{0};
            cin >> rangeMin >> rangeMax;
            cout << grid.query(rangeMin, rangeMax) << endl;
        }
        cout << "-" << endl;
        cin >> rowCount >> colCount;
    }
    return EXIT_SUCCESS;
}
