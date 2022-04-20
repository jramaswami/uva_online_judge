// UVA :: 1262 :: Password
// https://onlinejudge.org/external/12/1262.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using letter_set_t = bitset<26>;
const int N_ROWS{6};
const int N_COLS{5};

struct Solver {
    int target{0}, found{0};
    string soln, acc;
    vector<letter_set_t> intersections;

    Solver(int k, vector<letter_set_t> i): target{k}, intersections{i} {
        acc = string(N_COLS, ' ');
    }

    bool solve(int index) {
        if (index >= N_COLS) {
            // Base case.
            found++;
            if (found == target) {
                soln = string(acc);
                return true;
            }
            return false;
        } else {
            for (char c{'A'}; c <= 'Z'; ++c) {
                if (intersections[index].test(c - 'A')) {
                    acc[index] = c;
                    if (solve(index + 1)) {
                        return true;
                    }
                    acc[index] = ' ';
                }
            }
            return false;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases;
    cin >> testCases;
    while (testCases--) {
        int k;
        cin >> k;
        string line;
        getline(cin, line); // Read trailing newline.
        vector<vector<letter_set_t>> cols(N_COLS, vector<letter_set_t>(2));
        for (int i{0}; i < 2; ++i) {
            for (int r{0}; r < N_ROWS; ++r) {
                getline(cin, line);
                for (int c{0}; c < N_COLS; ++c) {
                    cols[c][i].set(line.at(c) - 'A');
                }
            }
        }
        vector<letter_set_t> intersections(N_COLS);
        transform(
            cols.begin(), cols.end(), intersections.begin(),
            [](vector<letter_set_t> T) {
                return T[0] & T[1];
            }
        );

        Solver solver(k, intersections);
        if (solver.solve(0)) {
            cout << solver.soln << endl;
        } else {
            cout << "NO" << endl;
        }

    }
    return EXIT_SUCCESS;
}
