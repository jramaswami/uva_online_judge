// UVA :: 10812 :: Beat the Spread!
// https://onlinejudge.org/external/108/10812.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    for (int t{0}; t < testCases; ++t) {
        long long sum{0}, absDiff{0};
        cin >> sum >> absDiff;

        // Let x be the smaller score.
        // y = absDiff + x
        // and
        // x + y = sum
        // x + (absDiff + x) = sum
        // 2x + absDiff = sum
        // 2x = sum - absDiff
        // x = (sum - absDiff) / 2
        long long x{(sum - absDiff) / 2LL};
        long long y{sum - x};
        if (x + y == sum && y - x == absDiff && x >= 0LL && y >= 0LL && y >= x) {
            assert(y >= x);
            assert((y - x) == absDiff);
            cout << y << " " << x << endl;
        } else {
            cout << "impossible" << endl;
        }
    }

    return EXIT_SUCCESS;
}
