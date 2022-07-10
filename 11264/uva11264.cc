// UVA :: 11264 :: Coin Collector
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while (testCases--) {
        int coinCount{0};
        cin >> coinCount;
        vector<int> coins;
        coins.reserve(coinCount);
        copy_n(istream_iterator<int>(cin), coinCount, back_inserter(coins));
        sort(coins.begin(), coins.end());
        vector<int> withdrawnCoins{coins[0]};
        vector<int> withdrawnAmount{coins[0]};
        for (int i{1}; i < coinCount; i++) {
            while (withdrawnAmount.back() >= coins[i]) {
                withdrawnCoins.pop_back();
                withdrawnAmount.pop_back();
            }
            withdrawnAmount.push_back(withdrawnAmount.back() + coins[i]);
            withdrawnCoins.push_back(coins[i]);
        }
        cout << withdrawnCoins.size() << "\n";
    }
    return EXIT_SUCCESS;
}
