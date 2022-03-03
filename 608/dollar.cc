// UVA :: 608 :: Counterfeit Dollar
// https://onlinejudge.org/external/6/608.pdf
// jramaswami


/*

Example.
BEF JIL down
could be lighter{BEF} could be heavier{JIL}
J A even
could be lighter{BEF} could be heaver{IL}  evens{JA}
(J cannot be lighter and even)
CEF BJI even
could be lighter{} could be heavier{L} evens{JACEFBI}
(B,E,F cannot be even and lighter; I cannot be even and ligher)
L is heavier, as the only answer for heavier.


Another Example.
AC BD down
could be lighter{A, C} could be heavier{B, D}
AC EF down
could be lighter{A, C} could be heavier{B, D, E, F}
A F even
could be lighter{C} could be heavier{B, D, E}
(A cannot be even and lighter, F cannot be even and lighter}
So, C must be lighter because it is the only single answer.

*/

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
        cerr << "test " << t << endl;

        bitset<12> possiblyHeavy;
        bitset<12> possiblyLight;
        bitset<12> definitelyEven;
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
                for (char c : lhs) {
                    heavySide[i].set(c-'A');
                    definitelyEven.set(c-'A');
                    possiblyHeavy.reset(c-'A');
                    possiblyLight.reset(c-'A');
                }
                for (char c : rhs) {
                    lightSide[i].set(c-'A');
                    definitelyEven.set(c-'A');
                    possiblyHeavy.reset(c-'A');
                    possiblyLight.reset(c-'A');
                }
            } else {
                // Heavy side.
                for (char c : lhs) {
                    heavySide[i].set(c-'A');
                    if (possiblyLight.test(c-'A')) {
                        // The coin cannot be possibly light and possibly heavy
                        // at the same time.
                        possiblyLight.reset(c-'A');
                        definitelyEven.set(c-'A');
                    } else if (definitelyEven.test(c-'A')) {
                        // The coin cannot be possibly light and definitely
                        // even at the same time.
                        // pass
                    } else {
                        possiblyHeavy.set(c-'A');
                    }
                }
                // Light side.
                for (char c : rhs) {
                    lightSide[i].set(c-'A');
                    if (possiblyHeavy.test(c-'A')) {
                        // The coin cannot be possibly heavy and possibly light
                        // at the same time.
                        possiblyHeavy.reset(c-'A');
                        definitelyEven.set(c-'A');
                    } else if (definitelyEven.test(c-'A')) {
                        // The coin cannot be possibly heavy and definitely
                        // even at the same time.
                        // pass
                    } else {
                        possiblyLight.set(c-'A');
                    }
                }
            }
            cerr << line << endl;
            cerr << lhs << " " << rhs << " " << isEven[i] << endl;
        }

        // Remove from balances all coins known to be even.
        for (int i{0}; i < 3; i++) {
            heavySide[i] &= ~definitelyEven;
            lightSide[i] &= ~definitelyEven;
        }

        cerr << "heavy " << possiblyHeavy << endl;
        cerr << "light " << possiblyLight << endl;
        cerr << "even  " << definitelyEven << endl;

        char soln{'!'};
        char solnLight{false};
        // We will have a balance with only one coin left on one side.
        for (int i{0}; i < 3; i++) {
            cerr << "balance " << i << " " << heavySide[i] << " " << lightSide[i] << endl;
            if (lightSide[i].count() == 1 && heavySide[i].count() == 0) {
                soln = whichCoin(lightSide[i]);
                solnLight = true;
                cerr << soln << " is light b/c it is the only possible light left on balance" << i << endl;
            } else if (lightSide[i].count() == 0 && heavySide[i].count() == 1) {
                soln = whichCoin(heavySide[i]);
                cerr << soln << " is heavy b/c it is the only possible heavy left on balance" << i << endl;
            }
        }
        // Or possibly light or possibly heavy may have only one possible coin
        // left.
        if (possiblyLight.count() == 1) {
            soln = whichCoin(possiblyLight);
            solnLight = true;
            cerr << soln << " is light b/c it is the only possible light left total." << endl;
        }
        if (possiblyHeavy.count() == 1) {
            soln = whichCoin(possiblyHeavy);
            cerr << soln << " is heavy b/c it is the only possible heavy left total." << endl;

        }

        cout << soln;
        if (solnLight) {
            cout << " is the counterfeit coin and it is light." << endl;
        } else {
            cout << " is the counterfeit coin and it is heavy." << endl;
        }
    }
    return EXIT_SUCCESS;
}
