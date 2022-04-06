// UVA ::  11195 :: Another n-Queen Problem
// https://onlinejudge.org/external/111/11195.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Board {
    int N{0};
    int solns{0};
    vector<string> board;
    bitset<30> negDiag;
    bitset<30> posDiag;
    bitset<14> row;

    Board(int n) {
        N = n;
        board.reserve(N);
    }

    void addRow(string row) {
        board.push_back(row);
    }

    void solve(int c) {
        if (c >= N) {
            solns++;
            return;
        }

        for (int r{0}; r < N; r++) {
            if (board[r][c] == '*') {
                continue;
            }
            if (row.test(r)) {
                continue;
            }
            int nd{r - c + N - 1};
            int pd{r + c};
            if (negDiag.test(nd) || posDiag.test(pd)) {
                continue;
            }

            row.set(r); negDiag.set(nd); posDiag.set(pd);
            solve(c+1);
            row.reset(r); negDiag.reset(nd); posDiag.reset(pd);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0}, C{1};
    cin >> N;
    string line;
    while (N) {
        getline(cin, line);  // Read trailing newline.
        Board board(N);
        for (int r{0}; r < N; ++r) {
            string row;
            getline(cin, row);
            board.addRow(row);
        }
        board.solve(0);
        cout << "Case " << C << ": " << board.solns << endl;
        cin >> N;
        C++;
    }
    return EXIT_SUCCESS;
}
