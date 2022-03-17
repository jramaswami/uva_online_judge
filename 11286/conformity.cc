// UVA :: 11286 :: Conformity
// https://onlinejudge.org/external/112/11286.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

using course_t = tuple<int, int, int, int, int>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    cin >> N;
    while (N) {
        map<course_t, int> freqs;
        for (int i{0}; i < N; ++i) {
            vector<int> A; A.reserve(5);
            copy_n(istream_iterator<int>(cin), 5, back_inserter(A));
            sort(A.begin(), A.end());
            course_t T{A[0], A[1], A[2], A[3], A[4]};
            freqs[T] += 1;
        }

        auto mx = max_element(freqs.cbegin(), freqs.cend(),
                [](const decltype(freqs)::value_type &lhs, const decltype(freqs)::value_type &rhs) {
                    return lhs.second < rhs.second;
                });
        int soln{0};
        for (auto item = freqs.cbegin(); item != freqs.cend(); ++item) {
            if (item->second == mx->second) {
                soln += mx->second;
            }
        }
        cout << soln << endl;
        cin >> N;
    }

    return EXIT_SUCCESS;
}
