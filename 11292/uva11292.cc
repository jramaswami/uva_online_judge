// UVA :: 11292 :: The Dragon of Loowater
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int headCount{0}, knightCount{0};
    cin >> headCount >> knightCount;
    while (headCount || knightCount) {
        vector<number_t> heads;
        heads.reserve(headCount);
        copy_n(istream_iterator<number_t>(cin), headCount, back_inserter(heads));
        vector<number_t> knights;
        knights.reserve(knightCount);
        copy_n(istream_iterator<number_t>(cin), knightCount, back_inserter(knights));
        sort(heads.begin(), heads.end());
        sort(knights.begin(), knights.end());
        int h{0};
        number_t expense{0};
        for (auto knight : knights) {
            if (h < headCount && knight >= heads[h]) {
                expense += knight;
                h++;
            }
        }
        if (h == headCount) {
            cout << expense << "\n";
        } else {
            cout << "Loowater is doomed!\n";
        }
        cin >> headCount >> knightCount;
    }
    return EXIT_SUCCESS;
}
