// UVA :: 12060 :: All Integer Average
// https://onlinejudge.org/external/120/12060.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int countDigits(int n) {
    int digits = 0;
    while (n) {
        digits += 1;
        n /= 10;
    }
    return digits;
}

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int sample_size, x, sum;
    int test_case = 1;
    cin >> sample_size;
    while (sample_size > 0) {
        sum = 0;
        for (int i = 0; i < sample_size; i++) {
            cin >> x;
            sum += x;
        }
        int p = sum / sample_size;
        int r = sum % sample_size;

        cout << "Case " << test_case << ":" << endl;
        if (r == 0) {
            if (p < 0) {
                cout << "- ";
            }
            cout << abs(p) << endl;
        } else {
            // Count leading spaces for fraction.
            int leading = 0;
            if (p < 0 || r < 0) {
                // Add two spaces for the negative sign.
                leading += 2;
            }
            leading += countDigits(p);

            // Compute reduced fraction.
            int g = gcd(abs(r), sample_size);
            int nm = abs(r) / g;
            int dn = sample_size / g;
            int dnDigits = countDigits(dn);
            int nmDigits = countDigits(nm);

            // Print leading spaces and the numerator.  Add extra spaces if
            // numerator has less digits than denominator.
            for (int i = 0; i < leading; ++i) {
                cout << " ";
            }
            int extra = dnDigits - nmDigits;
            for (int i = 0; i < extra; ++i) {
                cout << " ";
            }
            cout << nm << endl;

            // Print sign, whole number, and dashes.
            if (p < 0 || r < 0) {
                cout << "- ";
            }
            if (p != 0) {
                cout << abs(p);
            }
            int dashes = dnDigits;
            for (int i = 0; i < dashes; i++) {
                cout << "-";
            }
            cout << endl;

            // Print leading spaces and denominator.
            for (int i = 0; i < leading; ++i) {
                cout << " ";
            }
            cout << dn << endl;
        }
        cin >> sample_size;
        test_case++;
    }
}
