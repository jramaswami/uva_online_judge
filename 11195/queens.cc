// UVA ::  11195 :: Another n-Queen Problem
// https://onlinejudge.org/external/111/11195.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const int BAD{-1};

struct Board {
    int N{0};
    int solns{0};
    vector<vector<int>> board;
    vector<int> queens;

    Board(int n) {
        N = n;
        board = vector<vector<int>>(N, vector<int>(N));
        queens = vector<int>(N, -1);
    }

    void makeBad(int r, int c) {
        board[r][c] = BAD;
    }

    void solve() {
        solve(0);
    }

    bool valid(int r, int c) {
        if (board[r][c] == BAD) {
            return false;
        }
        for (int b{0}; b < c; ++b) {
            int q = queens[b];
            if (r == q || abs(r-q) == abs(c-b)) {
                return false;
            }
        }
        return true;
    }

    void solve(int c) {
        if (c >= N) {
            solns++;
            return;
        }

        for (int r{0}; r < N; r++) {
            if (valid(r, c)) {
                queens[c] = r;
                solve(c+1);
                queens[c] = -1;
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0}, C{1};;
    cin >> N;
    string line;
    while (N) {
        getline(cin, line);  // Read trailing newline.
        Board board(N);
        for (int r{0}; r < N; ++r) {
            getline(cin, line);
            for (int c{0}; c < N; ++c) {
                if (line.at(c) == '*') {
                    board.makeBad(r, c);
                }
            }
        }
        board.solve();
        cout << "Case " << C << ": " << board.solns << endl;
        cin >> N;
        C++;
    }
    return EXIT_SUCCESS;
}
