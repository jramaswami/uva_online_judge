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

    void precompute() {
        for (int r{0}; r < N; ++r) {
            partial_sum(matrix[r].begin(), matrix[r].end(), prefix[r].begin());
        }
    }

    number_t getSum(int row, int left, int right) {
        if (left - 1 < 0) {
            return prefix[row][right];
        } else {
            return prefix[row][right] - prefix[row][left-1];
        }
    }

    void solve() {
        deque<number_t> window;
        number_t currCost{0};
        for (int left{0}; left < M; ++left) {
            for (int right{left}; right < M; ++right) {
                int width{right - left + 1};
                window.clear();
                currCost = 0;
                for (int row{0}; row < N; ++row) {
                    number_t rowCost{getSum(row, left, right)};
                    currCost += rowCost;
                    window.push_back(rowCost);
                    while (currCost > K) {
                        currCost -= window.front();
                        window.pop_front();
                    }
                    int height = static_cast<int>(window.size());
                    int currArea = width * height;
                    if (currArea == solnArea) {
                        solnCost = min(solnCost, currCost);
                    } else if (currArea > solnArea) {
                        solnCost = currCost;
                        solnArea = currArea;
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
