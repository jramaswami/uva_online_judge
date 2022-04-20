// UVA :: 416 :: LED Test
// https://onlinejudge.org/external/4/416.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;



struct Solver {
    vector<string> readings;
    int readingCount{0};

    const vector<string> DIGIT_LIGHTS {
        "YYYYYYN", // 0
        "NYYNNNN", // 1
        "YYNYYNY", // 2
        "YYYYNNY", // 3
        "NYYNNYY", // 4
        "YNYYNYY", // 5
        "YNYYYYY", // 6
        "YYYNNNN", // 7
        "YYYYYYY", // 8
        "YYYYNYY"  // 9
    };

    Solver(int r) {
        readingCount = r;
        readings = vector<string>(r);
    }

    bool couldBe(int d, int i, string &working) {
        auto digit = DIGIT_LIGHTS[d];
        auto reading = readings[i];
        // Digit could be reading as long as:
        // (1) There are no lights lit that are not part of the digit.
        for (int j{0}; j < 7; ++j) {
            if (reading[j] == 'Y' && digit[j] == 'N') {
                return false;
            }
        }
        // (2) There are not lights lit that are considered not working.
        for (int j{0}; j < 7; ++j) {
            if (reading[j] == 'Y' && working[j] == 'N') {
                return false;
            }
        }
        return true;
    }

    void stillWorking(int d, int i, string &working) {
        // Lights that are considered burnt out are those in digit that were
        // not in the test reading in addition to those that are already
        // considered burnt out.
        auto digit = DIGIT_LIGHTS[d];
        auto reading = readings[i];
        for (int j{0}; j < 7; ++j) {
            if (digit[j] == 'Y' && reading[j] == 'N') {
                working[j] = 'N';
            }
        }
    }

    bool testCountDown(int n) {
        string working(7, 'Y');
        for (int i{0}; i < readingCount; ++i) {
            if (couldBe(n, i, working)) {
                stillWorking(n, i, working);
                n--;
            } else {
                return false;
            }
        }
        return true;
    }

    bool solve() {
        for (int start{9}; start + 1 >= readingCount; --start) {
            if (testCountDown(start)) {
                return true;
            }
        }
        return false;
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
            getline(cin, solver.readings[i]);
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
