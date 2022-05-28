// UVA :: 11790 :: Murcia’s Skyline
// https://onlinejudge.org/external/117/11790.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases;
    cin >> testCases;
    for (int t{1}; t <= testCases; ++t) {
        int N{0};
        cin >> N;
        vector<int> heights; heights.reserve(N);
        vector<int> widths; widths.reserve(N);
        copy_n(istream_iterator<int>(cin), N, back_inserter(heights));
        copy_n(istream_iterator<int>(cin), N, back_inserter(widths));

        vector<int> dpIncreasing(widths);
        vector<int> dpDecreasing(widths);

        for (int i{0}; i < N; ++i) {
            for (int j{i+1}; j < N; ++j) {
                // Increasing
                if (heights[i] < heights[j]) {
                    dpIncreasing[j] = max(
                        dpIncreasing[j],
                        dpIncreasing[i] + widths[j]
                    );
                }
                // Decreasing
                if (heights[i] > heights[j]) {
                    dpDecreasing[j] = max(
                        dpDecreasing[j],
                        dpDecreasing[i] + widths[j]
                    );
                }
            }
        }

        int bestIncreasing{*max_element(dpIncreasing.begin(), dpIncreasing.end())};
        int bestDecreasing{*max_element(dpDecreasing.begin(), dpDecreasing.end())};

        cout << "Case " << t << ". ";
        if (bestIncreasing >= bestDecreasing) {
            cout << "Increasing (" << bestIncreasing << "). "
                 << "Decreasing (" << bestDecreasing << ").\n";
        } else {
            cout << "Decreasing (" << bestDecreasing << "). "
                 << "Increasing (" << bestIncreasing << ").\n";
        }
    }
    return EXIT_SUCCESS;
}
