// UVA :: 10487 :: Closest Sums
// https://onlinejudge.org/external/104/10487.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    number_t N{0}, caseNo{1};
    cin >> N;
    while (N) {
        cout << "Case " << caseNo << ":" << endl;
        vector<number_t> A;
        copy_n(istream_iterator<number_t>(cin), N, back_inserter(A));
        vector<number_t> S;
        for (int i{0}; i < N; ++i) {
            for (int j{i+1}; j < N; ++j) {
                S.push_back(A[i] + A[j]);
            }
        }
        // Sort and remove duplicates.
        sort(S.begin(), S.end());
        auto it = unique(S.begin(), S.end());
        S.resize(distance(S.begin(), it));

        int Q{0};
        cin >> Q;
        for (int q{0}; q < Q; ++q) {
            number_t k{0}, soln{0};
            cin >> k;
            it = upper_bound(S.begin(), S.end(), k);
            if (it == S.begin()) {
                soln = (*it);
            } else if (it == S.end()) {
                auto jt = prev(it);
                soln = (*jt);
            } else {
                auto jt = prev(it);
                number_t x = (*it);
                number_t y = (*jt);
                if (abs(x - k) < abs(y - k)) {
                    soln = x;
                } else {
                    soln = y;
                }
            }
            cout << "Closest sum to " << k << " is " << soln << "." << endl;
        }
        cin >> N;
        caseNo++;
    }
    return EXIT_SUCCESS;
}
