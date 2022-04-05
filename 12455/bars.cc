// UVA :: 12455 :: Bars
// https://onlinejudge.org/external/124/12455.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int t{0};
    cin >> t;
    while (t--) {
        int n{0}, p{0};
        cin >> n >> p;
        vector<int> bars;
        bars.reserve(p);
        copy_n(istream_iterator<int>(cin), p, back_inserter(bars));

        vector<vector<int>>dp(p+1, vector<int>(n+1, 0));
        dp[0][0] = 1;
        for (int j{0}; j < p; ++j) {
            for (int i{0}; i <= n; ++i) {
                if (dp[j][i]) {
                    dp[j+1][i] = 1;
                    if (i+bars[j] <= n) {
                        dp[j+1][i+bars[j]] = 1;
                    }
                }
            }
        }

        /*
        for (auto row : dp) {
            copy(row.begin(), row.end(), ostream_iterator<int>(cerr, " "));
            cerr << endl;
        }
        */
        if (dp[p][n]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return EXIT_SUCCESS;
}
