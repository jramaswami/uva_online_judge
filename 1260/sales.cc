// UVA :: 1260 :: Sales
// https://onlinejudge.org/external/12/1260.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int T{0};
    cin >> T;
    while (T--) {
        int N{0};
        cin >> N;
        multiset<int> A;
        size_t soln{0};
        for (int i{0}; i < N; ++i) {
            int x{0};
            cin >> x;
            auto it = A.upper_bound(x);
            soln += distance(A.begin(), it);
            A.insert(x);
        }
        cout << soln << endl;
    }
    return EXIT_SUCCESS;
}
