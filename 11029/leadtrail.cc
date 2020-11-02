// UVA :: 11029 :: Leading and Trailing
// https://onlinejudge.org/external/110/11029.pdf

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

// Return the first k digits of the base raised to the exp power.
// REF: https://www.geeksforgeeks.org/given-number-n-find-first-k-digits-nn/
ll leading_digits(ll base, ll exp, ll k) {
    long double log10_product{static_cast<long double>(exp) * log10(static_cast<long double>(base))};
    long double decimal_part{log10_product - floor(log10_product)};
    decimal_part = pow(10, decimal_part);
    ll digits = pow(10, k - 1);
    return decimal_part * digits;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    for (int t{0}; t < testCases; ++t) {
        ll base, exp;
        cin >> base >> exp;
        ll trailing{modpow(base, exp, 1000)};
        ll leading{leading_digits(base, exp, 3)};
        cout << leading << "..." << setfill('0') << setw(3) << trailing << "\n";
    }
    return EXIT_SUCCESS;
}
