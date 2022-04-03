// UVA :: 725 :: Division
// https://onlinejudge.org/external/7/725.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

using bset_t = bitset<10>;
const int MAX_A{98765};
const int MIN_B{1234};
const int ALL_BITS{(1<<11)-1};

bset_t bits(int k) {
    bset_t b;
    for (int i{0}; i < 5; ++i) {
        b.set(k % 10);
        k /= 10;
    }
    return b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    cin >> N;
    while (N) {
        // a / b = N --> a = bN --> a/N = b
        int a{0}, limit{0};
        limit = MAX_A / N;
        vector<pair<int,int>> T;
        for (int b{MIN_B}; b <= limit; ++b) {
            a = b * N;
            bset_t x = bits(a) | bits(b);
            if (x.count() == 10) {
                T.emplace_back(a, b);
            }
        }

        if (T.empty()) {
            cout << "There are no solutions for " << N << "." << endl;
        } else {
            for (auto t : T) {
                cout << setfill('0') << setw(5) << t.first << " / "
                     << setfill('0') << setw(5) << t.second << " = "
                     << N << endl;
            }
        }

        cin >> N;
        if (N) {
            cout << endl;
        }
    }


    return EXIT_SUCCESS;
}
