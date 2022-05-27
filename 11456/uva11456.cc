// UVA :: 11456 Trainsorting
// https://onlinejudge.org/external/114/11456.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;


int computeBest(int start, const vector<int> &trains, int N) {
    vector<int> lis{};
    vector<int> lds{};

    for (int i{start+1}; i < N; ++i) {
        if (trains[i] > trains[start]) {
            if (lis.empty() || trains[i] > lis.back()) {
                lis.push_back(trains[i]);
            } else {
                auto it = lower_bound(lis.begin(), lis.end(), trains[i]);
                (*it) = trains[i];
            }
        }

        if (trains[i] < trains[start]) {
            if (lds.empty() || trains[i] < lds.back()) {
                lds.push_back(trains[i]);
            } else {
                auto it = lower_bound(lds.begin(), lds.end(), trains[i], greater<int>());
                (*it) = trains[i];
            }
        }
    }
    return static_cast<int>(lis.size() + lds.size() + 1);
}

int solve(const vector<int> &trains, int N) {
    int soln{0};
    for (int start{0}; start < N; ++start) {
        soln = max(soln, computeBest(start, trains, N));
    }
    return soln;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int T{0}, N{0};
    cin >> T;
    while (T--) {
        cin >> N;
        vector<int> trains;
        if (N) {
            trains.reserve(N);
            copy_n(istream_iterator<int>(cin), N, back_inserter(trains));
        }
        cout << solve(trains, N) << endl;
    }
    return EXIT_SUCCESS;
}
