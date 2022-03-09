// UVA :: 10107 :: What is the Median?
// <URL>
// jramaswami

#include <bits/stdc++.h>

using namespace std;

typedef long long int number_t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    priority_queue<number_t, vector<number_t>, greater<number_t>> left;
    priority_queue<number_t, vector<number_t>, less<number_t>> right;

    number_t N{0};
    number_t currMedian{0};
    while (cin >> N) {
        if (N > currMedian) {
            left.push(N);
        } else {
            right.push(N);
        }
        while (left.size() > right.size() + 1) {
            right.push(left.top());
            left.pop();
        }
        while (left.size() + 1 < right.size()) {
            left.push(right.top());
            right.pop();
        }

        if (left.size() == right.size()) {
            currMedian = (left.top() + right.top()) / 2;
        } else {
            currMedian = (left.size() > right.size() ? left.top() : right.top());
        }
        cout << currMedian << endl;
    }
    return EXIT_SUCCESS;
}
