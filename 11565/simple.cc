// UVA :: 11565 :: Simple Equations
// https://onlinejudge.org/external/115/11565.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int sq(int k) {
    return k * k;
}

bool valid(int A, int B, int C, int x, int y, int z) {
    return ((x + y + z == A) &&
            (x * y * z == B) &&
            (sq(x) + sq(y) + sq(z) == C)
    );
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    cin >> N;
    while (N--) {
        int A{0}, B{0}, C{0};
        cin >> A >> B >> C;
        vector<int> soln{INT_MAX, INT_MAX, INT_MAX};
        for (int x{1}; x <= B; ++x) {
            for (int y{x+1}; x * y <= B; ++y) {
                int z{B / (x * y)};
                if (z <= y) {
                    continue;
                }
                /* cerr << "x=" << x << " y=" << y << " z=" << z << endl; */
                if (valid(A, B, C, -y, -x, z) && -y < soln[0]) {
                    soln[0] = -y; soln[1] = -x; soln[2] = z;
                }
                if (valid(A, B, C, x, y, z) && x < soln[0]) {
                    soln[0] = x; soln[1] = y; soln[2] = z;
                }
            }
        }
        if (soln[0] < INT_MAX) {
            cout << soln[0] << " " << soln[1] << " " << soln[2] << endl;
        } else {
            cout << "No solution." << endl;
        }
    }
    return EXIT_SUCCESS;
}
