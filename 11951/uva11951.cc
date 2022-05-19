// UVA :: 11951 :: Area
// https://onlinejudge.org/external/119/11951.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

struct Solver {
    int N{0}, M{0}, solnArea{0};
    number_t K{0}, solnCost{0};
    vector<vector<number_t>> matrix;
    vector<vector<number_t>> prefix;

    Solver(int _n, int _m, number_t _k) {
        N = _n; M = _m; K = _k;
        matrix = vector<vector<number_t>>(N, vector<number_t>());
        prefix = vector<vector<number_t>>(N, vector<number_t>(M));
    }

    void readMatrix() {
        for (int r{0}; r < N; ++r) {
            matrix[r].reserve(M);
            copy_n(istream_iterator<number_t>(cin), M, back_inserter(matrix[r]));
        }
    }

    number_t getPrefix(int r, int c) {
        if (r < 0 || c < 0) {
            return 0LL;
        }
        return prefix[r][c];
    }

    void precompute() {
        for (int r{0}; r < N; ++r) {
            for (int c{0}; c < M; ++c) {
                prefix[r][c] = (
                    getPrefix(r-1, c) +
                    getPrefix(r, c-1) -
                    getPrefix(r-1, c-1) +
                    matrix[r][c]
                );
            }
        }
    }

    number_t getSum(int r1, int c1, int r2, int c2) {
        return (
            getPrefix(r2, c2) -
            getPrefix(r1-1, c2) -
            getPrefix(r2, c1-1) +
            getPrefix(r1-1, c1-1)
        );
    }

    void solve() {
        for (int r1{0}; r1 < N; ++r1) {
            for (int r2{r1}; r2 < N; ++r2) {
                for (int c1{0}; c1 < M; ++c1) {
                    for(int c2{0}; c2 < M; ++c2) {
                        number_t cost = getSum(r1, c1, r2, c2);
                        if (cost <= K) {
                            int area = (r2 - r1 + 1) * (c2 - c1 + 1);
                            if (area == solnArea) {
                                solnCost = min(solnCost, cost);
                            } else if (area > solnArea) {
                                solnArea = area;
                                solnCost = cost;
                            }
                        }
                    }
                }
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    for (int t{1}; t <= testCases; ++t) {
        int N{0}, M{0};
        number_t K{0};
        cin >> N >> M >> K;
        Solver solver(N, M, K);
        solver.readMatrix();
        solver.precompute();
        solver.solve();
        cout << "Case #" << t << ": " << solver.solnArea
             << " " << solver.solnCost << endl;
    }
    return EXIT_SUCCESS;
}
