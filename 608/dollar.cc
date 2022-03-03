// UVA :: 608 :: Counterfeit Dollar
// https://onlinejudge.org/external/6/608.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

char whichCoin(const bitset<12> coins) {
    for (char i{0}; i < 12; i++) {
        if (coins.test(i)) {
            return i + 'A';
        }
    }
    return '!';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int T{0};
    cin >> T;
    string junk;
    getline(cin, junk);   // Read trailing newline.
    for (int t{0}; t < T; ++t) {
        // Read measurements.
        vector<bitset<12>> heavySide(3, bitset<12>());
        vector<bitset<12>> lightSide(3, bitset<12>());
        deque<bool> isEven(3, false);
        string line;
        for (int i{0}; i < 3; i++) {
            getline(cin, line);
            // Parse line.
            auto leftSpace = find(line.begin(), line.end(), ' ');
            auto rightSpace = find(leftSpace+1, line.end(), ' ');
            string lhs(line.begin(), leftSpace);
            string rhs(leftSpace+1, rightSpace);
            string balance(rightSpace+1, line.end());
            // Place heavy side on the left.
            if (balance == "down") {
                swap(lhs, rhs);
            }

            if (balance == "even") {
                isEven[i] = true;
            }
            for (char c : lhs) {
                heavySide[i].set(c-'A');
            }
            for (char c : rhs) {
                lightSide[i].set(c-'A');
            }
        }

        bitset<12> heavy;
        bitset<12> light;
        bitset<12> even;
        for (int i{0}; i < 3; i++) {
            if (isEven[i]) {
                even |= heavySide[i];
                even |= lightSide[i];
            } else {
                heavy |= heavySide[i];
                light |= lightSide[i];
            }
        }

        // Determine which coin is always heavy or always light.
        bitset<12> alwaysHeavy;
        alwaysHeavy.set();
        alwaysHeavy &= ~even;
        bitset<12> alwaysLight;
        alwaysLight.set();
        alwaysLight &= ~even;
        for (int i{0}; i < 3; i++) {
            if (!isEven[i]) {
                alwaysHeavy &= heavySide[i];
                alwaysLight &= lightSide[i];
            }
        }
        if (alwaysLight.count()) {
            cout << whichCoin(alwaysLight) << " is the counterfeit coin and it is light." << endl;
        }
        if (alwaysHeavy.count()) {
            cout << whichCoin(alwaysHeavy) << " is the counterfeit coin and it is heavy." << endl;
        }
    }

    return EXIT_SUCCESS;
}
