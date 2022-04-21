// UVA :: 11057 :: Exact Sum
// https://onlinejudge.org/external/110/11057.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Solution {
    int a, b;

    Solution(int _a, int _b): a{_a}, b{_b} { }
};

bool operator<(const Solution &lhs, const Solution &rhs) {
    return (abs(lhs.a - lhs.b) < abs(rhs.a - rhs.b));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N;
    while (cin >> N) {
        int M;
        vector<int> A;
        A.reserve(N);
        copy_n(istream_iterator<int>(cin), N, back_inserter(A));
        sort(A.begin(), A.end());
        cin >> M;
        Solution soln{0, INT_MAX};
        for (auto a = A.cbegin(); a != A.cend(); ++a) {
            int d{M - (*a)};
            auto start = next(a);
            if (binary_search(start, A.cend(), d)) {
                Solution candidate{(*a), d};
                soln = min(candidate, soln);
            }
        }
        cout << "Peter should buy books whose prices are "
             << soln.a << " and " << soln.b << "." << endl << endl;
    }
    return EXIT_SUCCESS;
}
