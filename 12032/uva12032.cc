// UVA :: 12032 :: The Monkey and the Oiled Bamboo
// https://onlinejudge.org/external/120/12032.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

bool canClimb(number_t k, const vector<number_t> &rungHeights) {
    number_t prevHeight{0};
    for (auto rungHeight : rungHeights) {
        number_t dist{rungHeight - prevHeight};
        if (k < dist) {
            return false;
        } else if (k == dist) {
            k--;
        }
        prevHeight = rungHeight;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    for (int t{1}; t <= testCases; ++t) {
        int rungCount{0};
        cin >> rungCount;
        vector<number_t> rungHeights;
        rungHeights.reserve(rungCount);
        copy_n(istream_iterator<number_t>(cin), rungCount, back_inserter(rungHeights));
        // Binary search for the answer.
        // This is where the mistake is: accumulate is causing an overflow.
        // hi should be the maximum distance rung, which is rungHeight.back().
        number_t lo{0}, hi{accumulate(rungHeights.begin(), rungHeights.end(), 0)};
        cerr << "lo=" << lo << " hi=" << hi << endl;
        number_t soln{hi};
        while (lo <= hi) {
            number_t k{lo + ((hi - lo) / 2)};
            cerr << "lo=" << lo << " hi=" << hi << " k=" << k << endl;
            if (canClimb(k, rungHeights)) {
                soln = min(soln, k);
                hi = k - 1;
            } else {
                lo = k + 1;
            }
        }
        cout << "Case " << t << ": " << soln << endl;
    }
    return EXIT_SUCCESS;
}
