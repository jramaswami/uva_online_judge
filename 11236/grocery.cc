// UVA :: 11236 :: Grocery store
// 11236 - Grocery store
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const double EPS{10e-9};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    double a{0.01};
    int solns{0};
    while (a <= 20.00) {
        double b{a};
        while (a + b <= 20.00) {
            double c{b};
            while (a + b + c <= 20.00) {
                double d{(a + b + c) / ((a * b * c) - 1.00)};
                if (d >= c && a + b + c + d <= 20.00 && fabs((a+b+c+d) - (a*b*c*d)) < EPS) {
                    solns++;
                    /* printf("%0.2f %0.2f %0.2f %0.2f\n", a, b, c, d); */
                    printf("%0.2f %0.2f %0.2f %0.2f %f %f\n", a, b, c, d, a+b+c+d, a*b*c*d);
                }
                c += 0.01;
            }
            b += 0.01;
        }
        a += 0.01;
    }
    cerr << solns;
    return EXIT_SUCCESS;
}
