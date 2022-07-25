// UVA :: 10718 :: Bit Mask
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    uint32_t N{0}, L{0}, U{0};
    while (cin >> N >> L >> U) {
        uint32_t M{0};
        for (int bit{31}; bit >= 0;  bit--) {
            uint32_t mask{1U << bit};
            if (M + (mask - 1) < L) {
                // Is this bit necessary? (Assume all bits after this one
                // are turned on, will it be enough to make M >= L?)
                // If bit is necessary, turn it on.
                M |= mask;
            } else if (((mask & N) == 0) && ((M | mask) <= U)) {
                // If it is not, turn it on if it is not in N and will not
                // take us over U.
                M |= mask;
            }
        }
        cout << M << "\n";
    }
    return EXIT_SUCCESS;
}
