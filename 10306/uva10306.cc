// UVA :: 10306 e-Coins
// https://onlinejudge.org/external/103/10306.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct QItem {
    int x{0}, y{0}, d{0};

    QItem(int _x, int _y, int _d) {
        x = _x;
        y = _y;
        d = _d;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while (testCases--) {
        int N{0}, S{0};
        cin >> N >> S;
        int S2{S * S};
        vector<int> xs(N, 0);
        vector<int> ys(N, 0);
        for (int i{0}; i < N; ++i) {
            cin >> xs[i] >> ys[i];
        }
        // dp[sum(x)][sum(y)] = min number of coins required
        vector<vector<int>> dp(S+1, vector<int>(S+1, INT_MAX));
        dp[0][0] = 0;
        deque<QItem> queue;
        queue.emplace_back(0, 0, 0);
        int soln{INT_MAX};
        while (!queue.empty()) {
            auto item = queue.front();
            queue.pop_front();
            if (dp[item.x][item.y] == item.d) {
                if (((item.x * item.x) + (item.y * item.y)) == S2) {
                    soln = min(soln, item.d);
                }
                for (int coin{0}; coin < N; ++coin) {
                    int x0{item.x + xs[coin]};
                    int y0{item.y + ys[coin]};
                    if (x0 <= S && y0 <= S) {
                        int d0{item.d + 1};
                        if (d0 < dp[x0][y0]) {
                            queue.emplace_back(x0, y0, d0);
                            dp[x0][y0] = d0;
                        }
                    }
                }
            }
        }
        if (soln < INT_MAX) {
            cout << soln << "\n";
        } else {
            cout << "not possible\n";
        }
    }
    return EXIT_SUCCESS;
}
