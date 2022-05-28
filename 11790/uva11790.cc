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

        map<int, int> next;
        map<int, int> prev;
        int bestIncreasing{INT_MIN};
        for (int i{0}; i < N; ++i) {
            // This building only.
            next[widths[i]] = heights[i];
            bestIncreasing = max(bestIncreasing, widths[i]);

            for (const auto &T : prev) {
                // Skip this building.
                auto it = next.find(T.first);
                if (it == next.end()) {
                    next[T.first] = T.second;
                } else {
                    it->second = min(it->second, T.second);
                }

                // Increasing with this building if possible.
                if (heights[i] > T.second) {
                    int nextWidth{T.first + widths[i]};
                    bestIncreasing = max(bestIncreasing, nextWidth);
                    auto it = next.find(nextWidth);
                    if (it == next.end()) {
                        next[nextWidth] = heights[i];
                    } else {
                        it->second = min(it->second, heights[i]);
                    }
                }
            }
            prev = next;
            next = map<int, int>();
        }

        next = map<int, int>();
        prev = map<int, int>();
        int bestDecreasing{INT_MIN};
        for (int i{0}; i < N; ++i) {
            // This building only.
            next[widths[i]] = heights[i];
            bestDecreasing = max(bestDecreasing, widths[i]);

            for (const auto &T : prev) {
                // Skip this building.
                auto it = next.find(T.first);
                if (it == next.end()) {
                    next[T.first] = T.second;
                } else {
                    it->second = min(it->second, T.second);
                }

                // Decreasing with this building if possible.
                if (heights[i] < T.second) {
                    int nextWidth{T.first + widths[i]};
                    bestDecreasing = max(bestDecreasing, nextWidth);
                    auto it = next.find(nextWidth);
                    if (it == next.end()) {
                        next[nextWidth] = heights[i];
                    } else {
                        it->second = min(it->second, heights[i]);
                    }
                }
            }
            prev = next;
            next = map<int, int>();
        }

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
