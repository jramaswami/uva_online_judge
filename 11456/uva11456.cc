// UVA :: 11456 Trainsorting
// https://onlinejudge.org/external/114/11456.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int first_gte(int x, const vector<int> &A) {
    int result{static_cast<int>(A.size())};
    int lo{0};
    int hi{result - 1};
    while (lo <= hi) {
        int mid{lo + ((hi - lo) / 2)};
        if (A[mid] >= x) {
            result = min(result, mid);
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return result;
}

int first_lte(int x, const vector<int> &A) {
    int result{static_cast<int>(A.size())};
    int lo{0};
    int hi{result-1};
    while (lo <= hi) {
        int mid{lo + ((hi - lo) / 2)};
        if (A[mid] <= x) {
            result = min(result, mid);
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return result;
}


size_t solve(const vector<int> &trains) {
    cerr << "trn ";
    copy(trains.begin(), trains.end(), ostream_iterator<int>(cerr, " "));
    cerr << endl;

    vector<int> lis;
    vector<int> lds;
    for (auto x : trains) {
        if (lis.empty() || x > lis.back()) {
            lis.push_back(x);
        } else {
            int i = first_gte(x, lis);
            lis[i] = x;
        }

        if (lds.empty() || x < lds.back()) {
            lds.push_back(x);
        } else {
            int i = first_lte(x, lds);
            lds[i] = x;
        }
    }

    cerr << "lis ";
    copy(lis.begin(), lis.end(), ostream_iterator<int>(cerr, " "));
    cerr << endl;
    cerr << "lds ";
    copy(lds.begin(), lds.end(), ostream_iterator<int>(cerr, " "));
    cerr << endl;

    int N{static_cast<int>(lis.size())};
    int M{static_cast<int>(lds.size())};
    int soln{max(N, M)};
    for (auto x : trains) {
        int i{first_gte(x, lis)};
        int j{first_lte(x, lds)};
        cerr << "x=" << x << " i=" << i << " j=" << j << endl;
        soln = max(soln, (N - i) + (M - j) - 1);
        soln = max(soln, i + j);
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
        cerr << "N=" << N << endl;
        vector<int> trains;
        if (N) {
            trains.reserve(N);
            copy_n(istream_iterator<int>(cin), N, back_inserter(trains));
        }
        cout << solve(trains) << endl;
    }
    return EXIT_SUCCESS;
}
