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
        int maxChange = accumulate(coins.begin(), coins.end(), 0);
        vector<int> dp(maxChange+1, INT_MAX);
        // $0 is reachable with 0 coins.
        dp[0] = 0;
        int solnAmount{INT_MAX};
        int solnCount{INT_MAX};
        for (auto coin : coins) {
            for (int i{0}; i + coin <= maxChange; ++i) {
                if (dp[i] < INT_MAX) {
                    dp[i+coin] = min(dp[i+coin], dp[i] + 1);
                    if ((target <= i + coin) && (i + coin <= solnAmount)) {
                        solnAmount = min(solnAmount, i + coin);
                        solnCount = min(solnCount, dp[i] + 1);
                    }
                }
            }
        }
        cout << solnAmount << " " << solnCount << "\n";
    }
    return EXIT_SUCCESS;
}
