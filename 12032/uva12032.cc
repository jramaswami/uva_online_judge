// UVA :: 12032 :: The Monkey and the Oiled Bamboo
// https://onlinejudge.org/external/120/12032.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

bool canClimb(int k, const vector<int> &rungHeights) {
    int prevHeight{0};
    for (auto rungHeight : rungHeights) {
        int dist{rungHeight - prevHeight};
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
        vector<int> rungHeights;
        rungHeights.reserve(rungCount);
        copy_n(istream_iterator<int>(cin), rungCount, back_inserter(rungHeights));
        // Binary search for the answer.
        int lo{0}, hi{accumulate(rungHeights.begin(), rungHeights.end(), 0)};
        int soln{INT_MAX};
        while (lo <= hi) {
            int k{lo + ((hi - lo) / 2)};
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
