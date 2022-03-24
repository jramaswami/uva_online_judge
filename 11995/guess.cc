// UVA :: 11995 :: I Can Guess the Data Structure!
// https://onlinejudge.org/external/119/11995.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const size_t STACK{0};
const size_t QUEUE{1};
const size_t PRIORITY_QUEUE{2};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    while (cin >> N) {
        stack<int> S;
        queue<int> Q;
        priority_queue<int, vector<int>, less<int>> P;
        bitset<3> ok;
        ok.set();
        for (int i{0}; i < N; ++i) {
            int op{0}, arg{0};
            cin >> op >> arg;
            if (op == 1) {
                // Push
                if (ok.test(STACK)) { S.push(arg); }
                if (ok.test(QUEUE)) { Q.push(arg); }
                if (ok.test(PRIORITY_QUEUE)) { P.push(arg); }
            } else {
                // Pop
                if (ok.test(STACK)) {
                    if (S.empty() || S.top() != arg) {
                        ok.reset(STACK);
                    } else {
                        S.pop();
                    }
                }
                if (ok.test(QUEUE)) {
                    if (Q.empty() || Q.front() != arg) {
                        ok.reset(QUEUE);
                    } else {
                        Q.pop();
                    }
                }
                if (ok.test(PRIORITY_QUEUE)) {
                    if (P.empty() || P.top() != arg) {
                        ok.reset(PRIORITY_QUEUE);
                    } else {
                        P.pop();
                    }
                }
            }
        }
        if (ok.count() == 0) {
            cout << "impossible" << endl;
        } else if (ok.count() > 1) {
            cout << "not sure" << endl;
        } else if (ok.test(STACK)) {
            cout << "stack" << endl;
        } else if (ok.test(QUEUE)) {
            cout << "queue" << endl;
        } else if (ok.test(PRIORITY_QUEUE)) {
            cout << "priority queue" << endl;
        }
    }
    return EXIT_SUCCESS;
}
