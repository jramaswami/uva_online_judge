// UVA :: 11742 :: Social Constraints
// https://onlinejudge.org/external/117/11742.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Constraint {
    int a{0}, b{0}, dist{0};

    Constraint(int _a, int _b, int _d): a{_a}, b{_b}, dist{_d} {}
};

ostream& operator<<(ostream& os, const Constraint &cons) {
    os << "Constraint(" << cons.a << ", " << cons.b << ", " << cons.dist << ")";
    return os;
}

bool valid(const vector<int> &arrangement, const vector<Constraint> &constraints) {
    for (auto cons : constraints) {
        auto a = find(arrangement.begin(), arrangement.end(), cons.a);
        auto b = find(arrangement.begin(), arrangement.end(), cons.b);
        int k = abs(static_cast<int>(distance(a, b)));
        if (cons.dist > 0 && k > cons.dist) {
            return false;
        }
        if (cons.dist < 0 && k < (-cons.dist)) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int n{0}, m{0};
    cin >> n >> m;
    while (n || m) {
        vector<Constraint> constraints;
        for (int i{0}; i < m; ++i) {
            int a{0}, b{0}, d{0};
            cin >> a >> b >> d;
            constraints.emplace_back(a, b, d);
        }

        vector<int> arrangement(n, 0);
        iota(arrangement.begin(), arrangement.end(), 0);
        int soln{0};
        do {
            if (valid(arrangement, constraints)) {
                soln++;
            }
        } while(next_permutation(arrangement.begin(), arrangement.end()));
        cout << soln << endl;
        cin >> n >> m;
    }
    return EXIT_SUCCESS;
}
