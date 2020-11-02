// UVA :: 374 :: Big Mod
// https://onlinejudge.org/external/3/374.pdf

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Raise base to the power of exp modulo mod.
// REF: https://cp-algorithms.com/algebra/binary-exp.html
ll modpow(ll base, ll exp, ll mod) {
    ll result{1};
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll base, exp, mod;
    cin >> base;
    while (!cin.eof()) {
        cin >> exp >> mod;
        cout << modpow(base, exp, mod) << "\n";
        cin >> base;
    }
    return EXIT_SUCCESS;
}
