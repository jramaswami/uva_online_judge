// UVA :: 11517 :: Exact Change
// https://onlinejudge.org/external/115/11517.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while (testCases--) {
        int target{0}, N{0};
        cin >> target >> N;
        vector<int> coins;
        coins.reserve(N);
        copy_n(istream_iterator<int>(cin), N, back_inserter(coins));

        int solnAmount{INT_MAX}, solnCount{INT_MAX};
        // dp[amount] = min coins
        vector<int> prevDp(target, INT_MAX);
        prevDp[0] = 0;
        vector<int> nextDp(target, INT_MAX);
        for (auto coin : coins) {
            for (int prevAmount{0}; prevAmount < target; ++prevAmount) {
                if (prevDp[prevAmount] < INT_MAX) {
                    // Do not choose coin.
                    nextDp[prevAmount] = min(nextDp[prevAmount], prevDp[prevAmount]);

                    // Choose coin.
                    int nextAmount{prevAmount + coin};
                    int nextCount{prevDp[prevAmount] + 1};
                    if (nextAmount < target) {
                        nextDp[nextAmount] = min(nextDp[nextAmount], nextCount);
                    } else {
                        if (nextAmount < solnAmount) {
                            solnAmount = nextAmount;
                            solnCount = nextCount;
                        } else if (nextAmount == solnAmount) {
                            solnCount = min(solnCount, nextCount);
                        }
                    }
                }
            }
            prevDp.swap(nextDp);
            fill(nextDp.begin(), nextDp.end(), INT_MAX);
        }
        cout << solnAmount << " " << solnCount << "\n";

    }
    return EXIT_SUCCESS;
}
