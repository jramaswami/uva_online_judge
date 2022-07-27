// UVA :: 10918 :: Tri Tiling
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Cache results up to N = 30
    // dp[column][state id]
    vector<vector<number_t>> dp(31, vector<number_t>(8, 0));
    // Initialize.
    dp[0][7] = 1;
    for (int i{1}; i < 31; i++) {
        dp[i][0] += dp[i-1][7];

        dp[i][1] += dp[i-1][6];

        dp[i][2] += dp[i-1][5];

        dp[i][3] += dp[i-1][7];
        dp[i][3] += dp[i-1][4];

        dp[i][4] += dp[i-1][3];

        dp[i][5] += dp[i-1][2];

        dp[i][6] += dp[i-1][7];
        dp[i][6] += dp[i-1][1];

        dp[i][7] += dp[i-1][6];
        dp[i][7] += dp[i-1][3];
        dp[i][7] += dp[i-1][0];
    }

    int N{0};
    cin >> N;
    while (N >= 0) {
        cout << dp[N][7] << "\n";
        cin >> N;
    }
    return EXIT_SUCCESS;
}
