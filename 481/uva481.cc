// UVA :: 481 :: What Goes Up
// https://onlinejudge.org/external/4/481.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read input array.
    vector<int> nums;
    int n{0};
    while (cin >> n) {
        nums.push_back(n);
    }
    // LIS
    int N{static_cast<int>(nums.size())};
    vector<int> dp(nums.size(), 0);
    vector<int> prev(nums.size(), -1);
    pair<int, int> soln;
    for (int right{0}; right < N; ++right) {
        dp[right] = 1;
        prev[right] = -1;
        for (int left{0}; left < right; ++left) {
            if (nums[left] < nums[right]) {
                if (dp[right] <= 1 + dp[left]) {
                    dp[right] = 1 + dp[left];
                    prev[right] = left;
                }
            }
        }
        soln = max(soln, {dp[right], right});
    }
    cout << soln.first << "\n" << "-" << "\n";
    vector<int> path;
    int curr{soln.second};
    while (curr >= 0) {
        path.push_back(nums[curr]);
        curr = prev[curr];
    }
    for (auto it = path.crbegin(); it != path.crend(); ++it) {
        cout << (*it) << "\n";
    }
    return EXIT_SUCCESS;
}
