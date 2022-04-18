// UVA :: 524 :: Prime Ring Problem
// https://onlinejudge.org/external/5/524.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const vector<int> primes{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

void solve(int i, vector<int> &acc, bitset<17> visited, int n, const vector<vector<int>> &adj) {
    if (i >= n) {
        int p = acc.front() + acc.back();
        if (binary_search(primes.begin(), primes.end(), p)) {
            for (int j{0}; j < n; j++) {
                if (j) {
                    cout << " ";
                }
                cout << acc[j];
            }
            cout << endl;
        }
    } else {
        int u = acc[i-1];
        for (auto v : adj[u]) {
            if (v <= n && !visited.test(v)) {
                visited.set(v);
                acc[i] = v;
                solve(i + 1, acc, visited, n, adj);
                acc[i] = 0;
                visited.reset(v);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    // Precompute the numbers that can be adjacent to n.
    // Eg. 6 -> 1 (7), 5, (11), 7 (13), ...
    // Maximum n is 16.  Maximum adjacent pairs is 15 + 16 = 31
    vector<vector<int>> adj(17, vector<int>());
    for (int n{0}; n < 17; ++n) {
        for (auto p : primes) {
            // n + d = p
            // d = p - n
            int d{p - n};
            if (d > 0 && p != n) {
                adj[n].push_back(d);
            }
        }
    };

    // A bitset can be used to keep track of which numbers
    // are already used (since n <= 16).
    // Might work from both ends at the same time, given that
    // we always start with 1.
    int n{0}, caseNo{1};
    while (cin >> n) {
        vector<int> acc(n, 0);
        bitset<17> visited;
        acc[0] = 1;
        visited.set(1);
        if (caseNo > 1) {
            cout << endl;
        }
        cout << "Case " << caseNo << ":" << endl;
        solve(1, acc, visited, n, adj);
        caseNo++;
    }
    return EXIT_SUCCESS;
}
