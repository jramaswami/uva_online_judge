// UVA :: 108 :: Maximum Sum
// https://onlinejudge.org/external/1/108.pdf
// jramaswami

// TODO: Testing!!

#include <bits/stdc++.h>

using namespace std;

struct Solver {

    int N{0};
    vector<vector<int>> matrix;
    vector<vector<int>> prefix;

    Solver(int _n) {
        N = _n;
        matrix = vector<vector<int>>(N, vector<int>());
        prefix = vector<vector<int>>(N, vector<int>());
    }

    void readMatrix() {
        for (int i{0}; i < N; ++i) {
            matrix[i].reserve(N);
            copy_n(istream_iterator<int>(cin), N, back_inserter(matrix[i]));
        }
    }

    void precompute() {
        for (int i{0}; i < N; ++i) {
            prefix[i].reserve(N);
            partial_sum(matrix[i].begin(), matrix[i].end(), back_inserter(prefix[i]));
        }
    }

    // Return the sum of row from c1 to c2, inclusive.
    int getSum(int r, int c1, int c2) {
        if (c1 - 1 < 0) {
            return prefix[r][c2];
        }
        return prefix[r][c2] - prefix[r][c1-1];
    }

    int solve() {
        int soln{INT_MIN};
        for (int left{0}; left < N; ++left) {
            for (int right{left}; right < N; ++right) {
                // Non-empty Kadanes
                int bestSum{INT_MIN};
                int currSum{0};
                for (int r{0}; r < N; ++r) {
                    int currValue = getSum(r, left, right);
                    currSum = max(currValue, currSum + currValue);
                    bestSum = max(bestSum, currSum);
                }
                soln = max(soln, bestSum);
            }
        }
        return soln;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    while(cin >> N) {
        Solver solver(N);
        solver.readMatrix();
        solver.precompute();
        cout << solver.solve() << endl;
    }
    return EXIT_SUCCESS;
}
