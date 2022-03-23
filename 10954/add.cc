// UVA :: 10954 Add All
// https://onlinejudge.org/external/109/10954.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    cin >> N;
    while (N) {
        // Read numbers into a priority queue.
        priority_queue<number_t, vector<number_t>, greater<number_t>> pq;
        for (int i{0}; i < N; ++i) {
            number_t x{0};
            cin >> x;
            pq.push(x);
        }
        // To minimize total cost, you always want to add the smallest
        // numbers available.
        number_t soln{0};
        while (pq.size() > 1) {
            auto a = pq.top(); pq.pop();
            auto b = pq.top(); pq.pop();
            soln += (a + b);
            pq.push(a + b);
        }
        cout << soln << endl;

        cin >> N;
    }

    return EXIT_SUCCESS;
}
