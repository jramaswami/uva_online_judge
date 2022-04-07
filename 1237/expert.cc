// UVA :: 1237 :: Expert Enough?
// https://onlinejudge.org/external/12/1237.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Record {
    string manufacturer;
    int lowPrice{0};
    int highPrice{0};
};

bool operator< (const Record &lhs, const Record &rhs) {
    return lhs.lowPrice < rhs.lowPrice;
}

bool cmp(const Record &lhs, int P) {
    return lhs.lowPrice < P;
}

string query(int P, const vector<Record> &database) {
    bool found{false};
    string result;
    for (auto r : database) {
        if (r.lowPrice > P) {
            break;
        }
        if (r.highPrice >= P) {
            if (found) {
                found = false;
                break;
            }
            result = r.manufacturer;
            found = true;
        }
    }
    if (found) {
        return result;
    }
    return "UNDETERMINED";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    string line;
    int T{0};
    cin >> T;
    while (T) {
        int D{0};
        cin >> D;
        getline(cin, line);  // Read trailing newline.
        vector<Record> database(D);
        for (int d{0}; d < D; ++d) {
            getline(cin, line);
            auto s1 = find(line.begin(), line.end(), ' ');
            auto s2 = find(s1+1, line.end(), ' ');
            database[d].manufacturer = string(line.begin(), s1);
            database[d].lowPrice = stoi(string(s1+1, s2));
            database[d].highPrice = stoi(string(s2+1, line.end()));
        }
        sort(database.begin(), database.end());
        int Q{0};
        cin >> Q;
        for (int q{0}; q < Q; ++q) {
            int P{0};
            cin >> P;
            cout << query(P, database) << endl;
        }

        T--;
        if (T) {
            cout << endl;
        }
    }
    return EXIT_SUCCESS;
}
