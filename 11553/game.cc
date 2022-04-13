// UVA :: 11553 :: Grid Game
// https://onlinejudge.org/external/115/11553.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using grid_t = vector<vector<int>>;
using row_t = vector<int>;
using bs_t = bitset<8>;

// Mutually recursive functions declared ahead of time.
int alice(int acc, bs_t xRows, bs_t xCols, const grid_t &grid);
int bob(int acc, size_t lastRow, bs_t xRows, bs_t xCols, const grid_t &grid);

int alice(int acc, bs_t xRows, bs_t xCols, const grid_t &grid) {
    // Base case: there are no more rows to play.
    if (xRows.count() == grid.size()) {
        return acc;
    }

    // Alice will maximize her score.
    int score = INT_MIN;
    // Alice picks a row that is not crossed out.
    for (size_t r{0}; r < grid.size(); ++r) {
        if (!xRows.test(r)) {
            xRows.set(r);
            score = max(score, bob(acc, r, xRows, xCols, grid));
            xRows.reset(r);
        }
    }
    return score;
}

int bob(int acc, size_t lastRow, bs_t xRows, bs_t xCols, const grid_t &grid) {
    // Bob will minimize his score.
    int score = INT_MAX;
    // Bob will pick a column that is not crossed out.
    for (size_t c{0}; c < grid.size(); ++c) {
        if (!xCols.test(c)) {
            xCols.set(c);
            score = min(score, alice(acc + grid[lastRow][c], xRows, xCols, grid));
            xCols.reset(c);
        }
    }
    return score;
}

int solve(const grid_t &grid) {
    return alice(0, 0, 0, grid);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int T{0};
    cin >> T;
    while (T--) {
        int N{0};
        cin >> N;
        grid_t grid(N, row_t());
        for (int r{0}; r < N; ++r) {
            copy_n(istream_iterator<int>(cin), N, back_inserter(grid[r]));
        }
        int score = solve(grid);
        cout << score << endl;
    }
    return EXIT_SUCCESS;
}
