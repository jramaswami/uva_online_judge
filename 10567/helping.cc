// UVA :: 10567 :: Helping Fill Bates
// https://onlinejudge.org/external/105/10567.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    string S, junk;
    getline(cin, S);
    int Q{0};
    cin >> Q;
    getline(cin, junk);
    vector<vector<int>> indexes('z'+1, vector<int>());
    int N{static_cast<int>(S.size())};
    for (int i{0}; i < N; ++i) {
        indexes[S.at(i)].push_back(i);
    }
    for (int q{0}; q < Q; ++q) {
        string query;
        getline(cin, query);
        int index{-1}, start{0}, finish{0};
        bool found{true};
        for (size_t j{0}; j < query.size(); ++j) {
            char c{query.at(j)};
            // Find k > index.
            auto it = upper_bound(indexes[c].begin(), indexes[c].end(), index);
            if (it == indexes[c].end()) {
                found = false;
                break;
            }
            index = (*it);
            if (j == 0) {
                start = index;
            }
            if (j == query.size() - 1) {
                finish = index;
            }
        }
        if (found) {
            cout << "Matched " << start << " " << finish << endl;
        } else {
            cout << "Not matched" << endl;
        }
    }
    return EXIT_SUCCESS;
}
