// UVA :: 10487 :: Closest Sums
// https://onlinejudge.org/external/104/10487.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

const number_t INF{LLONG_MAX};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    number_t N{0}, caseNo{1};
    cin >> N;
    while (N) {
        set<number_t> A;
        for (int i{0}; i < N; ++i) {
            number_t x{0};
            cin >> x;
            A.insert(x);
        }
        set<number_t> S;
        for (auto i = A.begin(); i != A.end(); ++i) {
            for (auto j = next(i); j != A.end(); ++j) {
                S.insert((*i) + (*j));
            }
        }
        cout << "Case " << caseNo << ":" << endl;
        int Q{0};
        cin >> Q;
        for (int q{0}; q < Q; ++q) {
            number_t k{0};
            cin >> k;
            auto it = S.upper_bound(k);
            number_t x{INF}, y{INF};
            if (it != S.end()) {
                y = *(it);
            }
            if (it != S.begin()) {
                it--;
                x = *(it);
            }
            number_t dx{abs(x - k)}, dy{(y - k)}, soln{0};
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
