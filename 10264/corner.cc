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
        for (int vertex{0}; vertex < V; ++vertex) {
            for (int bit{0}; bit < N; ++bit) {
                // Two vertices are connected if they differ by one bit.
                int mask{1 << bit};
                int neighbor{vertex ^ mask};
                cornerSums[vertex] += cornerVals[neighbor];
            }
        }

        // Find the max pair of connected corners.
        int maxPair{0};
        for (int vertex{0}; vertex < V; ++vertex) {
            for (int bit{0}; bit < N; ++bit) {
                // Two vertices are connected if they differ by one bit.
                int mask{1 << bit};
                int neighbor{vertex ^ mask};
                maxPair = max(maxPair, cornerSums[vertex] + cornerSums[neighbor]);
            }
        }
        cout << maxPair << endl;
    }
    return EXIT_SUCCESS;
}
