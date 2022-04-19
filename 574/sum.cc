// UVA :: 574 :: Sum It Up
// https://onlinejudge.org/external/5/574.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
const int MAXN{100};

struct Solver {
    vector<int> acc;
    int target;
    vector<int> freqs;
    int solns{0};

    Solver(int t) {
        freqs = vector<int>(MAXN+1, 0);
        target = t;
        acc = vector<int>();
    }

    void solve(int sum) {
        /*
        cerr << "solve(" << sum << " [";
        copy(acc.begin(), acc.end(), ostream_iterator<int>(cerr, " "));
        cerr << "], " << target << " ...)" << endl;
        */

        if (sum == target) {
            copy(acc.begin(), acc.end()-1, ostream_iterator<int>(cout, "+"));
            cout << acc.back() << endl;
            solns++;
            return;
        }

        int start = (acc.empty() ? MAXN : acc.back());
        for (int i{start}; i > 0; --i) {
            if (freqs[i] > 0 && sum + i <= target) {
                freqs[i]--;
                acc.push_back(i);
                solve(sum + i);
                acc.pop_back();
                freqs[i]++;
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int T{0}, N{0};
    cin >> T >> N;
    while (T || N) {
        /* cerr << "T=" << T << " N=" << N << endl; */
        // x < 100.
        Solver solver(T);
        for (int i{0}; i < N; ++i) {
            int x{0};
            cin >> x;
            solver.freqs[x] += 1;
        }
        cout << "Sums of " << T << ":" << endl;
        solver.solve(0);
        if (solver.solns == 0) {
            cout << "NONE" << endl;
        }
        cin >> T >> N;
    }

    return EXIT_SUCCESS;
}
