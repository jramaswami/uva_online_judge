// UVA :: 11517 :: Exact Change
// https://onlinejudge.org/external/115/11517.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;


struct QItem {
    int coinCount, coinSum, lastCoin;
};

bool operator< (const QItem &lhs, const QItem &rhs) {
    if (lhs.coinCount == rhs.coinCount) {
        return lhs.coinSum < rhs.coinSum;
    }
    return lhs.coinCount < rhs.coinCount;
}

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
        priority_queue<QItem> pq;
        pq.push(QItem{0, 0, -1});
        int solnAmount{INT_MAX}, solnCount{INT_MAX};
        while (!pq.empty()) {
            QItem item = pq.top();
            pq.pop();
            if (target <= item.coinSum) {
                if (item.coinSum == solnAmount) {
                    solnCount = min(solnCount, item.coinCount);
                } else if (item.coinSum < solnAmount) {
                    solnAmount = item.coinSum;
                    solnCount = item.coinCount;
                }
            }

            for (int i{item.lastCoin + 1}; i < N; ++i) {
                if (item.coinSum <= solnAmount) {
                    pq.push(QItem{item.coinCount + 1, item.coinSum + coins[i], i});
                }
            }
        }
        cout << solnAmount << " " << solnCount << "\n";

    }
    return EXIT_SUCCESS;
}
