// UVA :: 10721 :: Bar Codes
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = int64_t;

number_t solve(number_t totalWidth, number_t barCount, number_t maxUnitWidth) {
    // dp[number of bars][width] = number of ways
    vector<vector<number_t>> dp(barCount+1, vector<number_t>(totalWidth+1));

    // Init
    for (int unitWidth{1}; unitWidth <= maxUnitWidth; ++ unitWidth) {
        if (unitWidth > totalWidth) {
            break;
        }
        dp[1][unitWidth] = 1;
    }

    for(int numberOfBars{1}; numberOfBars < barCount; ++numberOfBars) {
        for (int currWidth{1}; currWidth < totalWidth; ++currWidth) {
            for (int unitWidth{1}; unitWidth <= maxUnitWidth; ++unitWidth) {
                if (currWidth + unitWidth > totalWidth) {
                    break;
                }
                dp[numberOfBars+1][currWidth + unitWidth] += dp[numberOfBars][currWidth];
            }
        }
    }

    return dp[barCount][totalWidth];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    number_t totalWidth{0}, barCount{0}, maxUnitWidth{0};
    while (cin >> totalWidth >> barCount >> maxUnitWidth) {
        cout << solve(totalWidth, barCount, maxUnitWidth) << "\n";
    }
    return EXIT_SUCCESS;
}
