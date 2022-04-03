// UVA :: 927 :: Integer Sequences from Addition of Terms
// https://onlinejudge.org/external/9/927.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

number_t evalPolynomial(const vector<number_t> &P, number_t n) {
    number_t t{1}, s{0};
    for (auto a : P) {
        s += (a * t);
        t *= n;
    }
    return s;
}

number_t findN(number_t d, number_t k) {
    number_t n{1}, curr{0}, prev{0};
    while (1) {
        prev = curr;
        curr += (d * n);
        if (prev < k && k <= curr) {
            return n;
        }
        n++;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int C{0};
    cin >> C;
    while (C--) {
        number_t j{0};
        cin >> j;
        vector<number_t> P;
        P.reserve(j+1);
        copy_n(istream_iterator<number_t>(cin), j+1, back_inserter(P));
        number_t d{0}, k{0};
        cin >> d >> k;
        number_t n = findN(d, k);
        cout << evalPolynomial(P, n) << endl;
    }
    return EXIT_SUCCESS;
}
