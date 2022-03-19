// UVA :: 978 :: Lemmings Battle!
// https://onlinejudge.org/external/9/978.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while(testCases) {

        int battlefields{0}, greenCount{0}, blueCount{0};
        cin >> battlefields >> greenCount >> blueCount;
        // Read green army.
        vector<int> G;
        G.reserve(greenCount);
        copy_n(istream_iterator<int>(cin), greenCount, back_inserter(G));
        priority_queue<int, vector<int>, less<int>> greenArmy(G.begin(), G.end());
        // Read blue army.
        vector<int> B;
        B.reserve(greenCount);
        copy_n(istream_iterator<int>(cin), blueCount, back_inserter(B));
        priority_queue<int, vector<int>, less<int>> blueArmy(B.begin(), B.end());
        // Commence the battles.
        while (1) {
            if (greenArmy.empty() || blueArmy.empty()) {
                break;
            }
            vector<int> greenWinners;
            vector<int> blueWinners;
            for (int b{0}; b < battlefields; ++b) {
                int greenWarrior{0};
                if (!greenArmy.empty()) {
                    greenWarrior = greenArmy.top();
                    greenArmy.pop();
                }
                int blueWarrior{0};
                if (!blueArmy.empty()) {
                    blueWarrior = blueArmy.top();
                    blueArmy.pop();
                }
                if (greenWarrior > blueWarrior) {
                    greenWinners.push_back(greenWarrior - blueWarrior);
                } else if (greenWarrior < blueWarrior) {
                    blueWinners.push_back(blueWarrior - greenWarrior);
                }
            }

            for (auto greenWarrior : greenWinners) {
                greenArmy.push(greenWarrior);
            }
            for (auto blueWarrior : blueWinners) {
                blueArmy.push(blueWarrior);
            }
        }

        if (blueArmy.empty() && greenArmy.empty()) {
            cout << "green and blue died" << endl;
        } else if (blueArmy.empty()) {
            cout << "green wins" << endl;
            while (!greenArmy.empty()) {
                cout << greenArmy.top() << endl;
                greenArmy.pop();
            }
        } else if (greenArmy.empty()) {
            cout << "blue wins" << endl;
            while (!blueArmy.empty()) {
                cout << blueArmy.top() << endl;
                blueArmy.pop();
            }
        }

        testCases--;
        if (testCases) {
            cout << endl;
        }
    }

    return EXIT_SUCCESS;
}
