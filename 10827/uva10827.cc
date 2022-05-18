// UVA :: 10827 Maximum sum on a torus
// https://onlinejudge.org/external/108/10827.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Solver {
    int N{0};
    vector<vector<int>> torus;
    vector<vector<int>> prefix;

    Solver(int _n) {
        N = _n;
        torus = vector<vector<int>>(2*N, vector<int>());
        prefix = vector<vector<int>>(2*N, vector<int>(2*N, 0));
    }

    void readTorus() {
        for (int i{0}; i < N; ++i) {
            torus[i].reserve(2*N);
            torus[i+N].reserve(2*N);
            copy_n(istream_iterator<int>(cin), N, back_inserter(torus[i]));
            copy_n(torus[i].begin(), N, back_inserter(torus[i]));
            copy(torus[i].begin(), torus[i].end(), back_inserter(torus[i+N]));
        }
    }

    int getPrefix(int r, int c) {
        if (r < 0 || c < 0) {
            return 0;
        }
        return prefix[r][c];
    }

    void precompute() {
        for (int r{0}; r < 2*N; ++r) {
            for (int c{0}; c < 2*N; ++c) {
                prefix[r][c] = (
                    getPrefix(r-1, c) +
                    getPrefix(r, c-1) -
                    getPrefix(r-1, c-1) +
                    torus[r][c]
                );
            }
        }
    }

    int solve() {
        int soln{INT_MIN};
        for (int left{0}; left < N; ++left) {
            for (int right{left}; right < left+N; ++right) {
                for (int top{0}; top < N; ++top) {
                    for (int bottom{top}; bottom < top+N; ++bottom) {
                        int total{
                            getPrefix(bottom, right) -
                            getPrefix(top-1, right) -
                            getPrefix(bottom, left-1) +
                            getPrefix(top-1, left-1)
                        };
                        soln = max(soln, total);
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
        int N{0};
        cin >> N;
        Solver solver(N);
        solver.readTorus();
        solver.precompute();
        cout << solver.solve() << endl;
    }
    return EXIT_SUCCESS;
}
