// UVA :: 11572 :: Unique Snowflakes
// https://onlinejudge.org/external/115/11572.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while (testCases) {
        size_t soln{0};
        int N{0};
        cin >> N;
        // Boundary case: if N == 0.
        if (N) {
            vector<int> A;
            A.reserve(N);
            copy_n(istream_iterator<int>(cin), N, back_inserter(A));
            deque<int> window;
            map<int, int> freqs;
            for (int a : A) {
                freqs[a] += 1;
                window.push_back(a);
                while (freqs[a] > 1) {
                    freqs[window.front()] -= 1;
                    window.pop_front();
                }
                soln = max(soln, window.size());
            }
        }
        cout << soln << endl;
        --testCases;
    }
    return EXIT_SUCCESS;
}
