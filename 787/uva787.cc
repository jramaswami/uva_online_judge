// UVA :: 787 :: Maximum Sub-sequence Product
// https://onlinejudge.org/external/7/787.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

number_t solve(const vector<number_t> &nums) {
    number_t maxNegative{LLONG_MIN}, minPositive{LLONG_MAX},
             currProduct{nums[0]}, soln{nums[0]};

    if (nums[0] > 0) {
        minPositive = nums[0];
    } else {
        maxNegative = nums[0];
    }

    for (size_t i{1}; i < nums.size(); ++i) {
        currProduct *= nums[i];
        soln = max(soln, currProduct);
        if (currProduct > 0) {
            soln = max(soln, currProduct / minPositive);
            minPositive = min(minPositive, currProduct);
        } else if (currProduct < 0) {
            soln = max(soln, currProduct / maxNegative);
            maxNegative = max(maxNegative, currProduct);
        }
    }
    return soln;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    vector<number_t> nums;
    number_t n;
    while (cin >> n) {
        if (n == -999999) {
            cout << solve(nums) << endl;
            nums.clear();
        } else {
            nums.push_back(n);
        }
    }
    return EXIT_SUCCESS;
}
