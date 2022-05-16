// UVA :: 10755 :: Garbage Heap
// https://onlinejudge.org/external/107/10755.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

struct Solver {
    int rows{0}, columns{0}, tables{0};
    vector<vector<vector<number_t>>> cube;
    vector<vector<vector<number_t>>> prefix;

    Solver(int _t, int _r, int _c) {
        tables = _t;
        rows = _r;
        columns = _c;

        cube.reserve(tables);
        prefix.reserve(tables);
        for (int t{0}; t < tables; ++t) {
            cube.push_back(vector<vector<number_t>>(rows, vector<number_t>(columns, 0)));
            prefix.push_back(vector<vector<number_t>>(rows, vector<number_t>(columns, 0)));
        }
    }

    void readGrid(istream &is) {
        for (int t{0}; t < tables; ++t) {
            for (int r{0}; r < rows; ++r) {
                for (int c{0}; c < columns; ++c) {
                    is >> cube[t][r][c];
                }
            }
        }
    }

    number_t getPrefix(int t, int r, int c) {
        if (r < 0 || c < 0) {
            return 0;
        }
        return prefix[t][r][c];
    }

    number_t getPrefixSum(int t, int r1, int c1, int r2, int c2) {
        return (
            getPrefix(t, r2, c2) -
            getPrefix(t, r1-1, c2) -
            getPrefix(t, r2, c1-1) +
            getPrefix(t, r1-1, c1-1)
        );
    }

    void prepare() {
        // Compute prefix sums for grid.
        for (int t{0}; t < tables; ++t) {
            for (int r{0}; r < rows; ++r) {
                for (int c{0}; c < columns; ++c) {
                    prefix[t][r][c] = (
                        getPrefix(t, r-1, c) +
                        getPrefix(t, r, c-1) -
                        getPrefix(t, r-1, c-1) +
                        cube[t][r][c]
                    );
                }
            }
        }
    }

     number_t solve() {
        number_t soln{LLONG_MIN};
        for (int r1{0}; r1 < rows; ++r1) {
            for (int c1{0}; c1 < columns; ++c1) {
                for (int r2{r1}; r2 < rows; ++r2) {
                    for (int c2{c1}; c2 < columns; ++c2) {
                        // Kadanes algorithm.
                        number_t currSum{0};
                        number_t maxSum{LLONG_MIN};
                        for (int t{0}; t < tables; ++t) {
                            number_t currValue{getPrefixSum(t, r1, c1, r2, c2)};
                            currSum = max(currValue, currSum + currValue);
                            maxSum = max(maxSum, currSum);
                        }
                        soln = max(soln, maxSum);
                    }
                }
            }
        }
        return soln;
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while (testCases--) {
        int A{0}, B{0}, C{0};
        cin >> A >> B >> C;
        Solver solver(A, B, C);
        solver.readGrid(cin);
        solver.prepare();
        cout << solver.solve() << endl;
        if (testCases) {
            cout << endl;
        }
    }
    return EXIT_SUCCESS;
}
