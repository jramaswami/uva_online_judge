// UVA :: 608 :: Counterfeit Dollar
// https://onlinejudge.org/external/6/608.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Measurement {
    bitset<12> heavy;
    bitset<12> light;
    bool isEven{false};

    Measurement(const string &line) {
        auto leftSpace = find(line.begin(), line.end(), ' ');
        auto rightSpace = find(leftSpace+1, line.end(), ' ');
        string lhs = string(line.begin(), leftSpace);
        string rhs = string(leftSpace+1, rightSpace);
        string result = string(rightSpace+1, line.end());
        isEven = result == "even";
        if (result == "down") {
            swap(lhs, rhs);
        }
        for (auto c : lhs) { heavy.set(c-'A'); }
        for (auto c : rhs) { light.set(c-'A'); }
    }
};

ostream& operator<<(ostream &os, const Measurement &m) {
    if (m.isEven) {
        os << "even  " << m.heavy << " even  " << m.light;
    } else {
        os << "heavy " << m.heavy << " light " << m.light;
    }
    return os;
}

char whichCoin(bitset<12> bits) {
    for (char i{0}; i < 12; ++i) {
        if (bits.test(i)) {
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
        string line;
        vector<Measurement> measurements;
        for (int i{0}; i < 3; i++) {
            getline(cin, line);
            cerr << line << endl;
            measurements.emplace_back(line);
        }

        bitset<12> heavy;
        bitset<12> light;
        bitset<12> even;
        for (auto m : measurements) {
            if (m.isEven) {
                even |= m.heavy;
                even |= m.light;
            } else {
                heavy |= m.heavy;
                light |= m.light;
            }
        }

        for (auto m : measurements) {
            // Remove all the even bits from heavy and light.
            m.heavy &= (~even);
            m.light &= (~even);
            // Remove light bits from the heavy side.
            m.heavy &= (~light);
            // Remove heavy bits from the light side.
            m.light &= (~heavy);
            // The measurement with single bit set across both sides has the
            // counterfeit coin.
            cerr << m << endl;
            if (m.heavy.none() && m.light.any()) {
                cout << whichCoin(m.light) << " is the counterfeit coin and it is light." << endl;
            } else if (m.heavy.any() && m.light.none()) {
                cout << whichCoin(m.heavy) << " is the counterfeit coin and it is heavy." << endl;
            }
        }
            cerr << "heavy " << heavy << endl;
            cerr << "light " << light << endl;
            cerr << "even " << even << endl;
        cerr << endl;
    }
    return EXIT_SUCCESS;
}
