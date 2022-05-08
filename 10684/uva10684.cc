// UVA :: 10684 :: The jackpot
// https://onlinejudge.org/external/106/10684.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    cin >> N;
    while (N) {
        vector<int> nums;
        nums.reserve(N);
        copy_n(istream_iterator<int>(cin), N, back_inserter(nums));
        int curr_sum{0}, max_sum{0};
        for (auto n : nums) {
            curr_sum = max(0, curr_sum + n);
            max_sum = max(max_sum, curr_sum);
        }
        if (max_sum > 0) {
            cout << "The maximum winning streak is " << max_sum << "." << endl;
        } else {
            cout << "Losing streak." << endl;
        }
        cin >> N;
    }

    return EXIT_SUCCESS;
}
