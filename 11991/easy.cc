// UVA :: 11991 :: Easy Problem from Rujia Liu?
// https://onlinejudge.org/external/119/11991.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int arrayCount{0}, queryCount{0};
    while (cin >> arrayCount >> queryCount) {
        map<int, vector<int>> indexes;
        for (int i{1}; i <= arrayCount; ++i) {
            int x{0};
            cin >> x;
            auto it = indexes.find(x);
            if (it == indexes.end()) {
                indexes[x] = vector<int>();
            }
            indexes[x].push_back(i);
        }

        for (int q{0}; q < queryCount; ++q) {
            size_t k{0};
            int v{0};
            cin >> k >> v;
            k--;  // Convert to zero-based.
            auto it = indexes.find(v);
            if (it == indexes.end() || indexes[v].size() <= k) {
                cout << 0 << endl;
            } else {
                cout << indexes[v][k] << endl;
            }
        }
    }
    return EXIT_SUCCESS;
}
