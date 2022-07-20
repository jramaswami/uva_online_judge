// UVA :: 11100 :: The Trip, 2007
// jramaswami

#include <bits/stdc++.h>

using namespace std;

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
        deque<vector<int>> Q;
        for (auto k : A) {
            if (Q.empty() || Q.front().back() >= k) {
                vector<int> X{k};
                Q.push_back(X);
            } else {
                vector<int> X{Q.front()};
                Q.pop_front();
                X.push_back(k);
                Q.push_back(X);
            }
        }

        for (auto X : Q) {
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
