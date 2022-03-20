// UVA :: 11136 :: Hoax or what
// https://onlinejudge.org/external/111/11136.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int promotionDays{0};
    cin >> promotionDays;
    while(promotionDays) {
        number_t soln{0};
        map<number_t, number_t> freqs;
        for (int d{0}; d < promotionDays; ++d) {
            int billsToday{0};
            cin >> billsToday;
            for (int i{0}; i < billsToday; ++i) {
                number_t x{0};
                cin >> x;
                freqs[x] += 1;
            }

            auto mn = freqs.cbegin()->first;
            auto mx = freqs.crbegin()->first;
            soln += (mx - mn);
            freqs[mx]--;
            freqs[mn]--;
            if (freqs[mn] == 0) {
                freqs.erase(mn);
            }
            if (freqs[mx] == 0) {
                freqs.erase(mx);
            }
        }
        cout << soln << endl;
        cin >> promotionDays;
    }

    return EXIT_SUCCESS;
}
