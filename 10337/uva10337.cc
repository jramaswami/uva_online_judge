// UVA :: 10337 :: Flight Planner
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const int CLIMB_COST{60}, HOLD_COST{30}, SINK_COST{20}, MAX_ALTITUDE{9};;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while (testCases--) {
        int distance{0};
        cin >> distance;
        int ticks{distance / 100};
        vector<vector<int>> windspeeds(MAX_ALTITUDE + 1, vector<int>(ticks, 0));
        for (int altitude{MAX_ALTITUDE}; altitude >= 0; altitude--) {
            for (int t{0}; t < ticks; t++) {
                cin >> windspeeds[altitude][t];
            }
        }

        // dp[altitude][tick] = cost
        vector<vector<int>> dp(MAX_ALTITUDE + 1, vector<int>(ticks+1, INT_MAX));
        dp[0][0] = 0;
        for (int t{0}; t + 1 <= ticks; t++) {
            for (int altitude{0}; altitude <= MAX_ALTITUDE; altitude++) {
                if (dp[altitude][t] < INT_MAX) {
                    if (altitude + 1 <= MAX_ALTITUDE) {
                        dp[altitude+1][t+1] = min(
                            dp[altitude+1][t+1],
                            dp[altitude][t] + max(0, CLIMB_COST - windspeeds[altitude][t])
                        );
                    }
                    dp[altitude][t+1] = min(
                        dp[altitude][t+1],
                        dp[altitude][t] + max(0, HOLD_COST - windspeeds[altitude][t])
                    );
                    if (altitude - 1 >= 0) {
                        dp[altitude-1][t+1] = min(
                            dp[altitude-1][t+1],
                            dp[altitude][t] + max(0, SINK_COST - windspeeds[altitude][t])
                        );
                    }
                }
            }
        }

        // Landing at ticks - 1.
        cout << dp[0][ticks] << "\n\n";
    }
    return EXIT_SUCCESS;
}
