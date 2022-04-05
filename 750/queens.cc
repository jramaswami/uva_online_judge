// UVA :: 750 :: 8 Queens Chess Problem
// https://onlinejudge.org/external/7/750.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Board {
    const vector<pair<int, int>> offsets{
        {0, 1}, {0, -1}, {1, 0}, {-1, 0},
        {1, 1}, {-1, 1}, {1, -1}, {-1, -1}
    };

    vector<int> queens;
    int soln{1};

    Board(int r, int c) {
        queens.resize(9);
        fill(queens.begin(), queens.end(), -1);
        queens[c] = r;
    }

    bool queenAt(int r, int c) {
        return queens[c] == r;
    }

    bool inbounds(int r, int c) {
        return r >= 1 && r <= 8 && c >= 1 && c <= 8;
    }

    bool valid(int r, int c) {
        for (auto off : offsets) {
            int r0{r}, c0{c}, dr{off.first}, dc{off.second};
            while (inbounds(r0, c0)) {
                if (queenAt(r0, c0)) {
                    return false;
                }
                r0 += dr;
                c0 += dc;
            }
        }
        return true;
    }

    void solve(int c) {
        if (c == 9) {
            // Print solution.
            if (soln < 10) {
                cout << " ";
            }
            cout << soln << "      ";
            for (int c0{1}; c0 <= 8; c0++) {
                cout << queens[c0];
                if (c0 < 8) {
                    cout << " ";
                }
            }
            cout << endl;
            soln++;
            return;
        }

        if (queens[c] >= 0) {
            solve(c+1);
        }

        for (int r{1}; r <= 8; r++) {
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
    int T{0}; cin >> T;
    while (T) {
        int r{0}, c{0};
        cin >> r >> c;
        Board board(r, c);

        // Print header.
        cout << "SOLN       COLUMN" << endl;
        cout << " #      1 2 3 4 5 6 7 8" << endl;
        cout << endl;

        board.solve(1);

        T--;
        if (T) {
            cout << endl;
        }
    }

    return EXIT_SUCCESS;
}
