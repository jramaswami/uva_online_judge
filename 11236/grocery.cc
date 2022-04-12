// UVA :: 11236 :: Grocery store
// 11236 - Grocery store
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;
const number_t OFFSET{1000000};

number_t computeD(number_t a, number_t b, number_t c) {
    number_t s = (a + b + c) * OFFSET;
    number_t p = (a * b * c) - OFFSET;
    if (p > 0 && s % p == 0) {
        return s / p;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    number_t a{1};
    int solns{0};
    while (a <= 2000) {
        number_t b{a};
        while (a + b <= 2000) {
            number_t c{b};
            while (a + b + c <= 2000) {
                number_t d = computeD(a, b, c);
                if (d >= c) {
                    number_t s = (a + b + c + d);
                    number_t p = (a * b * c * d) / OFFSET;
                    if (s <= 2000 && s == p) {
                        solns++;
                        double a0{static_cast<double>(a) / 100.0};
                        double b0{static_cast<double>(b) / 100.0};
                        double c0{static_cast<double>(c) / 100.0};
                        double d0{static_cast<double>(d) / 100.0};
                        cout << fixed << setprecision(2) << a0 << " "
                             << fixed << setprecision(2) << b0 << " "
                             << fixed << setprecision(2) << c0 << " "
                             << fixed << setprecision(2) << d0 << endl;
                    }
                }
                c++;
            }
            b++;
        }
        a++;
    }
    /* cerr << solns << endl; */
    return EXIT_SUCCESS;
}
