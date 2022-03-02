// UVA :: 608 :: Counterfeit Dollar
// https://onlinejudge.org/external/6/608.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Measurement {
    string lhs;
    string rhs;
    string result;

    Measurement(const string &line) {
        // Find the first space.
        auto leftSpace = find(line.begin(), line.end(), ' ');
        auto rightSpace = find(leftSpace+1, line.end(), ' ');
        lhs = string(line.begin(), leftSpace);
        rhs = string(leftSpace+1, rightSpace);
        result = string(rightSpace+1, line.end());
    }

};

ostream& operator<<(ostream &os, const Measurement &measurement) {
    os << "lhs=" << measurement.lhs << " rhs=" << measurement.rhs << " result=" << measurement.result;
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int T{0};
    cin >> T;
    string junk;
    getline(cin, junk);   // Read trailing newline.
    while (T) {
        // Each test case is three lines.
        vector<Measurement> measurements;
        string line;
        for (int i{0}; i < 3; i++) {
            getline(cin, line);
            measurements.emplace_back(line);
        }
        vector<int> weight(128, 0);
        for (auto m : measurements) {
            if (m.result == "up") {
                // Heavy side is on the left.
                for (auto c : m.lhs) {
                    weight[c] += 1;
                }
                for (auto c : m.rhs) {
                    weight[c] -= 1;
                }
            } else if (m.result == "down") {
                // Heavy side is on the right.
                for (auto c : m.lhs) {
                    weight[c] -= 1;
                }
                for (auto c : m.rhs) {
                    weight[c] += 1;
                }
            }
        }
        for (auto m : measurements) {
            if (m.result == "even") {
                // These are all genuine.
                for (auto c : m.lhs) {
                    weight[c] = 0;
                }
                for (auto c : m.rhs) {
                    weight[c] = 0;
                }
            }
        }

        copy(weight.begin() + 'A', weight.begin() + 'M', ostream_iterator<int>(cerr, " ")); cerr << endl;
        for (char c{'A'}; c <= 'L'; ++c) {
            if (weight[c] <= -1) {
                cout << c << " is the counterfeit coin and it is light." << endl;
            } else if (weight[c] >= 2) {
                cout << c << " is the counterfeit coin and it is heavy." << endl;
            }

        }
        --T;
    }
    return EXIT_SUCCESS;
}
