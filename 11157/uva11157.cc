// UVA :: 11157 Dynamic Frog
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Stone {
    char type;
    int posn;

    Stone(char t, int p) {
        type = t;
        posn = p;
    }
};

int deltaAbs(int a, int b) {
    return abs(a - b);
}

void readStones(string &line, vector<Stone> &stones) {
    stringstream ss(line);
    string token;
    while (ss >> token) {
        // First letter of token is type.
        char stoneType{token[0]};
        int stonePosn{stoi(token.substr(2, token.size() - 2))};
        stones.emplace_back(stoneType, stonePosn);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // Solution code.
    // This comes down the choice of when to use small stones.
    // Might even be able to say that you can separate it into
    // subproblems where you must minimize the maximum step between
    // big stones.
    //
    // Can we use scanf to parse data on this one?
    int T{0};
    cin >> T;
    for (int testNo{1}; testNo <= T; testNo++) {
        size_t stoneCount{0};
        int totalDistance{0};
        cin >> stoneCount >> totalDistance;
        string line, stoneDescription;
        // Read trailing newline.
        getline(cin, line);
        vector<Stone> stones;
        while (stones.size() < stoneCount) {
            // Read a line.
            getline(cin, line);
            // Parse the line into stones.
            readStones(line, stones);
        }
        vector<int> going{0};
        vector<int> coming{0};
        bool isGoing{true};
        for (Stone stone : stones) {
            if (stone.type == 'B') {
                going.push_back(stone.posn);
                coming.push_back(stone.posn);
            } else {
                if (isGoing) {
                    going.push_back(stone.posn);
                } else {
                    coming.push_back(stone.posn);
                }
                isGoing = !isGoing;
            }
        }
        going.push_back(totalDistance);
        coming.push_back(totalDistance);
        vector<int> goingDelta;
        vector<int> comingDelta;
        adjacent_difference(going.begin(), going.end(), back_inserter(goingDelta), deltaAbs);
        adjacent_difference(coming.begin(), coming.end(), back_inserter(comingDelta), deltaAbs);
        int soln = max(
            *max_element(goingDelta.begin(), goingDelta.end()),
            *max_element(comingDelta.begin(), comingDelta.end())
        );
        cout << "Case " << testNo << ": " << soln << "\n";
    }
    return EXIT_SUCCESS;
}
