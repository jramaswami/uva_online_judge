// UVA :: 10341 :: Solve It
// https://onlinejudge.org/external/103/10341.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Function {

    double p{0}, q{0}, r{0}, s{0}, t{0}, u{0};

    Function(int _p, int _q, int _r, int _s, int _t, int _u) {
        p = static_cast<double>(_p);
        q = static_cast<double>(_q);
        r = static_cast<double>(_r);
        s = static_cast<double>(_s);
        t = static_cast<double>(_t);
        u = static_cast<double>(_u);
    }

    double f(double x) {
        // p*e^{-x} + q*sin(x) + r*cos(x) + s*tan(x) + t*x^2 + u = 0
        double result{p * exp(-x)};
        result += (q * sin(x));
        result += (r * cos(x));
        result += (s * tan(x));
        result += (t * x * x);
        result += u;
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int p{0}, q{0}, r{0}, s{0}, t{0}, u{0};
    while (cin >> p >> q >> r >> s >> t >> u) {
        Function fn(p, q, r, s, t, u);
        // f is non-increasing on [0, 1], per hint.
        double lowbound = fn.f(0.0);
        double highbound = fn.f(1.0);
        if (lowbound < 0 || highbound > 0) {
            cout << "No solution" << endl;
        } else {
            double lo{0.0};
            double hi{1.0};
            double x{0};
            for (int i{0}; i < 500; ++i) {
                x = {lo + ((hi - lo) / 2)};
                double y{fn.f(x)};
                if (y > 0) {
                    lo = x;
                } else {
                    hi = x;
                }
            }
            cout << fixed << setprecision(4) << x << endl;
        }
    }
    return EXIT_SUCCESS;
}
