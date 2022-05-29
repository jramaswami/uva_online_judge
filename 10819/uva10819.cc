// UVA :: 10819 :: Trouble of 13-Dots
// https://onlinejudge.org/external/108/10819.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int money{0}, items{0};
    while (cin >> money >> items) {
        // Read prices and favorability.
        vector<int> prices(items, 0);
        vector<int> favors(items, 0);
        int maxFavor{0};
        for (int i{0}; i < items; ++i) {
            cin >> prices[i] >> favors[i];
            maxFavor += favors[i];
        }

        // dp[index][favor] = min cost
        int moneyLimit{money + 200 + 10};
        vector<vector<int>> dp(items+1, vector<int>(maxFavor + 1, moneyLimit));
        int soln{0};
        dp[0][0] = 0;
        for (int i{1}; i <= items; ++i) {
            int price{prices[i-1]};
            int favor{favors[i-1]};
            for (int j{0}; j <= maxFavor; ++j) {
                // Skip this item.
                dp[i][j] = min(dp[i][j], dp[i-1][j]);
                // Choose this item.
                int price0{dp[i-1][j] + price};
                if (price0 <= moneyLimit) {
                    int favor0{j + favor};
                    dp[i][favor0] = min(dp[i][favor0], price0);
                    if (price0 > 2000) {
                        if (price0 - 200 <= money) {
                            soln = max(soln, j+favor);
                        }
                    } else {
                        if (price0 <= money) {
                            soln = max(soln, j+favor);
                        }
                    }
                }
            }
        }
        cout << soln << "\n";
    }

    return EXIT_SUCCESS;
}
