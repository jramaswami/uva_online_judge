// UVA :: 10264 :: The Most Potent Corner
// https://onlinejudge.org/external/102/10264.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    while (cin >> N) {
        // An N dimensional cube has N^2 corners.
        int V{1<<N};
        vector<int> cornerVals;
        cornerVals.reserve(V);
        copy_n(istream_iterator<int>(cin), V, back_inserter(cornerVals));

        // Sum the corners.
        vector<int> cornerSums(V, 0);
        for (int i{0}; i < V; ++i) {
            for (int j{0}; j < V; ++j) {
                // A pair is connected if there is a 1 bit difference.
                bitset<16> connection(i ^ j);
                if (connection.count() == 1) {
                    cornerSums[i] += cornerVals[j];
                }
            }
        }

        // Find the max pair of connected corners.
        int maxPair{0};
        for (int i{0}; i < V; ++i) {
            for (int j{0}; j < V; ++j) {
                // A pair is connected if there is a 1 bit difference.
                bitset<16> connection(i ^ j);
                if (connection.count() == 1) {
                    maxPair = max(maxPair, cornerSums[i] + cornerSums[j]);
                }
            }
        }
        cout << maxPair << endl;
    }
    return EXIT_SUCCESS;
}
