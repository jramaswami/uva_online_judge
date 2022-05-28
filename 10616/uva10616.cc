// UVA :: 10616 :: Divisible Group Sums
// https://onlinejudge.org/external/106/10616.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

// Return the positive number that is x mod m.
number_t posMod(number_t x, number_t m) {
    number_t y{x % m};
    if (y < 0) {
        return y + m;
    }
    return y;
}

number_t query(number_t D, number_t M, const vector<number_t> &A) {
    // Convert A to A mod D.
    vector<number_t> B(A.size());
    transform(A.begin(), A.end(), B.begin(), [D](number_t x){ return posMod(x, D); });
    // dp[B][M][D] = number of ways
    vector<vector<vector<number_t>>> dp(A.size(),
                                   vector<vector<number_t>>(
                                       M+1, vector<number_t>(D, 0)));
    for (size_t i{0}; i < B.size(); ++i) {
        number_t x{B[i]};
        // I can always choose this element alone.
        dp[i][1][x] += 1;
        // For previous entries ...
        if (i > 0) {
            for (number_t m{0}; m <= M; ++m) {
                for (number_t d{0}; d < D; ++d) {
                    if (dp[i-1][m][d]) {
                        // I can skip this element.
                        dp[i][m][d] += dp[i-1][m][d];
                        // I can add this element.
                        if (m + 1 <= M) {
                            dp[i][m+1][(d + x) % D] += dp[i-1][m][d];
                        }
                    }
                }
            }
        }
    }
    return dp[B.size() - 1][M][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0}, Q{0}, t{1};;
    cin >> N >> Q;
    while (N || Q) {
        vector<number_t> A;
        A.reserve(N);
        copy_n(istream_iterator<number_t>(cin), N, back_inserter(A));

        cout << "SET " << t << ":\n";
        for (int q{1}; q <= Q; ++q) {
            cout << "QUERY " << q << ": ";
            number_t M{0}, D{0};
            cin >> D >> M;
            cout << query(D, M, A) << "\n";
        }
        t++;
        cin >> N >> Q;
    }
    return EXIT_SUCCESS;
}
