// UVA :: 10895 :: Matrix Transpose
// https://onlinejudge.org/external/108/10895.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int rowCount{0}, colCount{0};
    while (cin >> rowCount >> colCount) {
        vector<map<int, int>> transposed(colCount+1, map<int, int>());
        for (int r{1}; r <= rowCount; r++) {
            int nonZeroCols{0};
            cin >> nonZeroCols;
            if (nonZeroCols) {
                vector<int> indexes;
                indexes.reserve(nonZeroCols);
                vector<int> values;
                values.reserve(nonZeroCols);
                copy_n(istream_iterator<int>(cin), nonZeroCols, back_inserter(indexes));
                copy_n(istream_iterator<int>(cin), nonZeroCols, back_inserter(values));
                for (int i{0}; i < nonZeroCols; ++i) {
                    int c{indexes[i]};
                    int v{values[i]};
                    transposed[c][r] = v;
                }
            }
        }
        cout << colCount << " " << rowCount << endl;
        for (int r{1}; r <= colCount; r++) {
            cout << transposed[r].size();
            if (transposed[r].size()) {
                cout << " ";
            }
            vector<int> indexes;
            indexes.reserve(transposed[r].size());
            vector<int> values;
            values.reserve(transposed[r].size());
            for (auto it = transposed[r].cbegin(); it != transposed[r].cend(); ++it) {
                indexes.push_back(it->first);
                values.push_back(it->second);
            }
            for (size_t i{0}; i < indexes.size(); ++i) {
                cout << indexes[i];
                if (i + 1 < indexes.size()) {
                    cout << " ";
                }
            }
            cout << "\n";
            for (size_t i{0}; i < values.size(); ++i) {
                cout << values[i];
                if (i + 1 < values.size()) {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }
    return EXIT_SUCCESS;
}
