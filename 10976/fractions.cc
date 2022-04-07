// UVA :: 10976 :: Fractions Again?!
// https://onlinejudge.org/external/109/10976.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Solution {
    int N, a, b;
};

ostream& operator<<(ostream &os, const Solution &s) {
    os << "1/" << s.N << " = " << "1/" << s.a << " + 1/" << s.b;
    return os;
}

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    while (cin >>N) {
        vector<Solution> solns;
        for (int r = N+1; r <= 2 * N; ++r) {
            int D = r * N;
            int x = r - N;
            int g = gcd(x, D);
            x = x / g;
            if (x == 1) {
                solns.push_back(Solution{N, (D / g), r});
            }
        }
        cout << solns.size() << endl;
        for (Solution s : solns) {
            cout << s << endl;
        }
    }
    return EXIT_SUCCESS;
}
