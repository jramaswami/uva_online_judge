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
    // LIS - O(n lg n) using binary search.
    int N{static_cast<int>(nums.size())};
    vector<int> dpValues{nums[0]};
    vector<int> dpIndexes{0};
    vector<int> prevIndexes(nums.size(), -1);
    for (int i{1}; i < N; ++i) {
        if (nums[i] > dpValues.back()) {
            prevIndexes[i] = dpIndexes.back();
            dpValues.push_back(nums[i]);
            dpIndexes.push_back(i);
        } else {
            auto it = lower_bound(dpValues.begin(), dpValues.end(), nums[i]);
            int delta{static_cast<int>(distance(dpValues.begin(), it))};
            dpValues[delta] = nums[i];
            dpIndexes[delta] = i;
            prevIndexes[i] = (delta > 0 ? dpIndexes[delta-1] : -1);
        }
    }
    // Reconstruct path.
    vector<int> path;
    int curr{dpIndexes.back()};
    while (curr >= 0) {
        path.push_back(nums[curr]);
        curr = prevIndexes[curr];
    }
    // Print solution.
    cout << dpValues.size() << "\n-\n";
    for (auto rit = path.crbegin(); rit != path.crend(); ++rit) {
        cout << (*rit) << "\n";
    }

    return EXIT_SUCCESS;
}
