// UVA :: 357 :: Let Me Count The Ways
// https://onlinejudge.org/external/3/357.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    const vector<number_t> COINS{1, 5, 10, 25, 50};
    int N{0};
    while (cin >> N) {
        vector<number_t> dp(N+1, 0);
        dp[0] = 1;
        for (auto c : COINS) {
            for (int i{0}; i <= N; ++i) {
                if (i + c <= N) {
                    dp[i+c] += dp[i];
                }
            }
        }
        if (dp[N] == 1) {
            cout << "There is only 1 way to produce " << N << " cents change.\n";
        } else {
            cout << "There are " << dp[N] << " ways to produce " << N << " cents change.\n";
        }
    }
    return EXIT_SUCCESS;
}
