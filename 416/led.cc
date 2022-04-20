// UVA :: 416 :: LED Test
// https://onlinejudge.org/external/4/416.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;



struct Solver {
    vector<bitset<7>> readings;
    vector<int> acc;
    int readingCount{0};

    const vector<bitset<7>> DIGIT_LIGHTS {
        bitset<7>("1111110"),  // 0
        bitset<7>("0110000"),  // 1
        bitset<7>("1101101"),  // 2
        bitset<7>("1111001"),  // 3
        bitset<7>("0110011"),  // 4
        bitset<7>("1011011"),  // 5
        bitset<7>("1011111"),  // 6
        bitset<7>("1110000"),  // 7
        bitset<7>("1111111"),  // 8
        bitset<7>("1111011")   // 9
    };

    Solver(int r) {
        readingCount = r;
        readings = vector<bitset<7>>(r);
    }

    bool couldBe(int d, int i, bitset<7> prevBurntOut) {
        cerr << "couldBe(" << d << "[" << DIGIT_LIGHTS[d] << "], " << readings[i] << ", " << prevBurntOut << ")" << endl;
        auto digits = DIGIT_LIGHTS[d];
        auto reading = readings[i];
        // Digit could be reading as long as:
        // (1) There are no lights lit that are not part of the digit.
        for (int b{0}; b < 7; ++b) {
            if (reading.test(b)) {
                if (digits.test(b)) {
                    // OK
                } else {
                    cerr << "cannot be " << d << " b/c " << b << " bit disagrees." << endl;
                    return false;
                }
            }
        }
        // (2) There are not lights lit that are considered burnt out.
        for (int b{0}; b < 7; ++b) {
            if (prevBurntOut.test(b)) {
                if (reading.test(b)) {
                    cerr << "cannot be " << d << " b/c " << b << " bit not burnt." << endl;
                    return false;
                }
            }
        }
        return true;
    }

    bitset<7> nextBurntOut(int d, int i, bitset<7> prevBurntOut) {
        // Lights that are considered burnt out are those in digit that were
        // not in the test reading in addition to those that are already
        // considered burnt out.
        return (DIGIT_LIGHTS[d] ^ readings[i]) | prevBurntOut;
    }

    bool solve(int i, bitset<7> prevBurntOut) {
        cerr << "solve(" << i << ", " << prevBurntOut << ")" << endl;
        copy(acc.begin(), acc.end(), ostream_iterator<int>(cerr, " "));
        cerr << endl;

        if (i >= readingCount) {
            // Base case
            copy(acc.begin(), acc.end(), ostream_iterator<int>(cerr, " "));
            cerr << endl;
            return true;
        } else if (i == 0) {
            for (int d{9}; d >= 0; --d) {
                if (couldBe(d, i, prevBurntOut)) {
                    acc.push_back(d);
                    if (solve(i+1, nextBurntOut(d, i, prevBurntOut))) {
                        return true;
                    }
                    acc.pop_back();
                }
            }
        } else {
            if (couldBe(acc.back()-1, i, prevBurntOut)) {
                acc.push_back(acc.back()-1);
                if (solve(i+1, nextBurntOut(acc.back(), i, prevBurntOut))) {
                    return true;
                }
                acc.pop_back();
            }
        }
        return false;
    }

    bool solve() {
        bitset<7> prevBurntOut;
        return solve(0, prevBurntOut);
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int readingCount{0};
    string line;
    cin >> readingCount;
    while (readingCount) {
        getline(cin, line); // Read trailing newline.
        Solver solver(readingCount);
        for (int i{0}; i < readingCount; ++i) {
            getline(cin, line);
            for (int j{0}; j < 7; ++j) {
                if (line.at(j) == 'Y') {
                    solver.readings[i].set(j);
                }
            }
        }
        if (solver.solve()) {
            cout << "MATCH" << endl;
        } else {
            cout << "MISMATCH" << endl;
        }
        cin >> readingCount;
    }
    return EXIT_SUCCESS;
}
