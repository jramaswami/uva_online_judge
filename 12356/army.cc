// UVA :: 12356 :: Army buddies
// https://onlinejudge.org/external/123/12356.pdf
// jramaswami

// Start with simplest thing that will work.
// Time limit = 1 second.

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int soldierCount{0}, reportCount{0};
    cin >> soldierCount >> reportCount;
    while (soldierCount || reportCount) {

        vector<int> leftBuddy(soldierCount+2, 0);
        vector<int> rightBuddy(soldierCount+2, 0);
        iota(leftBuddy.begin(), leftBuddy.end(), -1);
        iota(rightBuddy.begin(), rightBuddy.end(), 1);

        for (int r{0}; r < reportCount; ++r) {
            int left{0}, right{0};
            cin >> left >> right;

            int prevLeft{leftBuddy[left]};
            int nextRight{rightBuddy[right]};

            cout << (prevLeft > 0 ? to_string(prevLeft) : "*") << " ";
            cout << (nextRight <= soldierCount ? to_string(nextRight) : "*") << endl;

            leftBuddy[nextRight] = prevLeft;
            rightBuddy[prevLeft] = nextRight;
        }

        cout << "-" << endl;
        cin >> soldierCount >> reportCount;
    }
    return EXIT_SUCCESS;
}
