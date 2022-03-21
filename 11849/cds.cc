// UVA :: 11849 :: CD
// https://onlinejudge.org/external/118/11849.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    number_t N{0}, M{0};
    cin >> N >> M;
    while (N > 0 || M > 0) {
        set<number_t> ncds;
        copy_n(istream_iterator<number_t>(cin), N, inserter(ncds, ncds.end()));
        vector<number_t> mcds;
        copy_n(istream_iterator<number_t>(cin), M, back_inserter(mcds));
        auto soln = count_if(mcds.begin(), mcds.end(),
                             [&ncds](number_t x) {
                                 return ncds.find(x) != ncds.end();
                             }
        );

        cout << soln << endl;
        cin >> N >> M;
    }
    return EXIT_SUCCESS;
}
