// UVA :: 10226 :: Hardwood Species
// https://onlinejudge.org/external/102/10226.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    string line;
    cin >> testCases;
    getline(cin, line);  // Read trailing newline.
    getline(cin, line);  // Read blank line.
    while (testCases) {
        string tree;
        getline(cin, tree);
        map<string, double> freqs;
        double total{0.0};
        while (tree != "") {
            total += 1.0;
            freqs[tree] += 1.0;
            getline(cin, tree);
        }

        for (const auto &item : freqs) {
            double soln{round(1000000 * item.second / total) / 10000.00};
            cout << item.first << fixed << setprecision(4) << " " << soln << endl;
        }
        testCases--;
        if (testCases) cout << endl;
    }

    return EXIT_SUCCESS;
}
