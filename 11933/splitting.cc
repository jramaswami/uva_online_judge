// UVA :: 11933 :: Splitting Numbers
// https://onlinejudge.org/external/119/11933.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    cin >> N;
    while(N) {
        int bitIndex{1}, a{0}, b{0};
        for (int bit{0}; bit < 31; ++bit) {
            int mask{1 << bit};
            if (N & mask) {
                if (bitIndex % 2) {
                    a |= mask;
                } else {
                    b |= mask;
                }
                bitIndex++;
            }
        }
        cout << a << " " << b << endl;
        cin >> N;
    }
    return EXIT_SUCCESS;
}
