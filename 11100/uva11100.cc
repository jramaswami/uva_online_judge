// UVA :: 11100 :: The Trip, 2007
// jramaswami

#include <bits/stdc++.h>

using namespace std;

// Find the item with the highest frequency.
int highestFrequency(vector<int> &A) {
    int curr{A[0]}, freq{1}, result{0};
    for (size_t i{1}; i < A.size(); i++) {
        if (A[i] == curr) {
            freq++;
        } else {
            result = max(result, freq);
            curr = A[i];
            freq = 1;
        }
    }
    result = max(result, freq);
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    cin >> N;
    while (N) {
        vector<int> A;
        A.reserve(N);
        copy_n(istream_iterator<int>(cin), N, back_inserter(A));
        sort(A.begin(), A.end());
        int M{highestFrequency(A)};
        vector<vector<int>> B(M, vector<int>());
        int i{0};
        for (auto k : A) {
            B[i].push_back(k);
            i = (i + 1) % M;
        }

        cout << M << "\n";
        for (auto X : B) {
            for (size_t i{0}; i < X.size(); i++) {
                cout << X[i];
                if (i + 1 < X.size()) {
                    cout << " ";
                }
            }
            cout << "\n";
        }

        cin >> N;
        if (N) {
            cout << "\n";
        }
    }
    return EXIT_SUCCESS;
}
