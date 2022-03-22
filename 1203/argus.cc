// UVA :: 1203 :: Argus
// https://onlinejudge.org/external/12/1203.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Query {
    int id{0};
    int period{0};
    int clock{0};

    Query(int i, int p): id{i}, period{p}, clock{p} {}
    Query(int i, int p, int c): id{i}, period{p}, clock{c} { }

    Query next() const {
        return Query(id, period, clock + period);
    }
};


bool operator< (const Query &lhs, const Query &rhs) {
    if (lhs.clock == rhs.clock) {
        return lhs.id > rhs.id;
    }
    return lhs.clock > rhs.clock;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    string line;
    // Read register lines.
    getline(cin, line);
    priority_queue<Query, vector<Query>, less<Query>> pq;
    while (line != "#") {
        // Parse the register command.
        auto firstSpace = find(line.begin(), line.end(), ' ');
        auto secondSpace = find(firstSpace+1, line.end(), ' ');
        string qNumStr = string(firstSpace+1, secondSpace);
        string qPeriodStr = string(secondSpace+1, line.end());
        int qNum = stoi(qNumStr);
        int qPeriod = stoi(qPeriodStr);
        Query q{qNum, qPeriod};
        pq.push(q);
        getline(cin, line);
    }
    int K{0};
    cin >> K;
    for (int i{0}; i < K; ++i) {
        cout << pq.top().id << endl;
        pq.push(pq.top().next());
        pq.pop();
    }
    return EXIT_SUCCESS;
}
