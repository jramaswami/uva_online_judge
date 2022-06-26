// UVA :: 10943 :: How do you add?
// jramaswami

#include <bits/stdc++.h>

using namespace std;
const int MOD{1000000};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0}, K{0};
    cin >> N >> K;
    while (N || K) {
        // dp[term count][term sum] = number of ways
        vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));
        // Initialize
        dp[0][0] = 1;
        for (int termCount{0}; termCount < K; termCount++) {
            for (int prevSum{0}; prevSum <= N; ++prevSum) {
                for (int term{0}; term <= N; ++term) {
                    int nextSum{prevSum + term};
                    if (nextSum <= N) {
                        dp[termCount+1][nextSum] = (dp[termCount+1][nextSum] + dp[termCount][prevSum]) % MOD;
                    }
                }
            }
        }
        cout << dp[K][N] << "\n";
        cin >> N >> K;
    }
    return EXIT_SUCCESS;
}
