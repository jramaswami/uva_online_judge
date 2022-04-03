// UVA :: 441 :: Lotto
// https://onlinejudge.org/external/4/441.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

void traverse(size_t i, vector<int> &acc, const vector<int> &S) {
    if (acc.size() == 6) {
        for (size_t j{0}; j < acc.size(); ++j) {
            cout << acc[j];
            if (j < 5) {
                cout << " ";
            }
        }
        cout << endl;
        return;
    }

    // Make sure there are enough values to fill the subset.
    if (S.size() - i < 6 - acc.size()) {
        return;
    }

    for (size_t j{i}; j < S.size(); ++j) {
        acc.push_back(S[j]);
        traverse(j+1, acc, S);
        acc.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int k{0};
    cin >> k;
    while (k) {
        vector<int> S;
        S.reserve(k);
        copy_n(istream_iterator<int>(cin), k, back_inserter(S));
        vector<int> acc;
        traverse(0, acc, S);
        cin >> k;
        if (k) {
            cout << endl;
        }
    }
    return EXIT_SUCCESS;
}
