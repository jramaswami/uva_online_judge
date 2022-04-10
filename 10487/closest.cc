// UVA :: 10487 :: Closest Sums
// https://onlinejudge.org/external/104/10487.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const int INF{INT_MAX};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0}, caseNo{1};
    cin >> N;
    while (N) {
        vector<int> A;
        A.reserve(N);
        copy_n(istream_iterator<int>(cin), N, back_inserter(A));
        set<int> S;
        for (int i{0}; i < N; ++i) {
            for (int j{i+1}; j < N; ++j) {
                S.insert(A[i] + A[j]);
            }
        }
        cout << "Case " << caseNo << ":" << endl;
        int Q{0};
        cin >> Q;
        for (int q{0}; q < Q; ++q) {
            int k{0};
            cin >> k;
            auto it = S.upper_bound(k);
            int x{INF}, y{INF};
            if (it != S.end()) {
                y = *(it);
            }
            if (it != S.begin()) {
                it--;
                x = *(it);
            }
            int dx{abs(x - k)}, dy{(y - k)}, soln{0};
            if (dy < dx) {
                soln = y;
            } else {
                soln = x;
            }
            cout << "Closest sum to " << k << " is " << soln << "." << endl;
        }
        cin >> N;
        caseNo++;
    }
    return EXIT_SUCCESS;
}
