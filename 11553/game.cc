// UVA :: 11553 :: Grid Game
// https://onlinejudge.org/external/115/11553.pdf
// jramaswami

// The order that Alice chooses the rows does not matter.
// All that matters is which column Bob should choose from
// each row in order to minimize the number of candies Alice
// takes from him.

#include <bits/stdc++.h>

using namespace std;
using grid_t = vector<vector<int>>;
using row_t = vector<int>;

int solve0(int acc, size_t r, bitset<8> xcols, const grid_t &grid) {
    // Base case.
    if (xcols.count() == grid.size()) {
        return acc;
    }

    int bestScore{INT_MAX};
    for (size_t c{0}; c < grid.size(); ++c) {
        if (!xcols.test(c)) {
            xcols.set(c);
            bestScore = min(
                bestScore,
                solve0(grid[r][c] + acc, r + 1, xcols, grid)
            );
            xcols.reset(c);
        }
    }
    return bestScore;
}

int solve(const grid_t &grid) {
    bitset<8> xcols;
    return solve0(0, 0, xcols, grid);
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
