// UVA :: 11085 :: Back to the 8-Queens
// https://onlinejudge.org/external/110/11085.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> solutions;
vector<int>acc(8, -1);
bitset<16> rows, negDiag, posDiag;

void precompute(int c) {
    if (c >= 8) {
        solutions.push_back(vector<int>());
        copy(acc.begin(), acc.end(), back_inserter(solutions.back()));
    } else {
        for (int r{0}; r < 8; r++) {
            int pd = r + c;
            int nd = 7 + r - c;
            if (rows.test(r) || posDiag.test(pd) || negDiag.test(nd)) {
                continue;
            }
            acc[c] = r;
            rows.set(r);
            posDiag.set(pd);
            negDiag.set(nd);
            precompute(c + 1);
            negDiag.reset(nd);
            posDiag.reset(pd);
            rows.reset(r);
            acc[c] = -1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // There are only 92 ways to place 8 queens.
    // Precompute them and then find the closest
    // for each query.
    precompute(0);
    assert(solutions.size() == 92);

    // Solution code.
    string line;
    int testCase{1};
    while(getline(cin, line)) {
        istringstream iss(line);
        vector<int> rows; rows.reserve(8);
        copy_n(istream_iterator<int>(iss), 8, back_inserter(rows));
        int minMoves{INT_MAX};
        for (auto soln : solutions) {
            int moves{0};
            for (int i{0}; i < 8; i++) {
                // Note: solutions is zero-based, test cases are one-based.
                if (soln[i] + 1 != rows[i]) {
                    moves++;
                }
            }
            minMoves = min(minMoves, moves);
        }
        cout << "Case " << testCase << ": " << minMoves << endl;
        testCase++;
    }
    return EXIT_SUCCESS;
}
