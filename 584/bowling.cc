// UVA :: 584 :: Bowling
// https://onlinejudge.org/external/5/584.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;


int scoreRoll(const vector<char> &rolls, size_t i) {
    if (i >= rolls.size()) {
        return 0;
    }
    if (rolls[i] == 'X') {
        return 10;
    } else if (rolls[i] == '/') {
        return 10 - scoreRoll(rolls, i-1);
    } else {
        return rolls[i] - '0';
    }
}

int scoreGame(const vector<char> &rolls) {
    int score{0};
    int frameNumber{1};
    int frameRoll{1};
    for (size_t i{0}; i < rolls.size(); i++) {
        if (frameNumber <= 10) {
            if (rolls[i] == 'X') {
                score += scoreRoll(rolls, i);
                score += scoreRoll(rolls, i+1);
                score += scoreRoll(rolls, i+2);
                frameRoll += 2;
            } else if (rolls[i] == '/') {
                score += scoreRoll(rolls, i);
                score += scoreRoll(rolls, i+1);
                frameRoll++;
            } else {
                score += scoreRoll(rolls, i);
                frameRoll++;
            }
        }
        if (frameRoll == 3) {
            frameNumber++;
            frameRoll = 1;
        }
    }
    return score;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    string line;
    getline(cin, line);
    while (line != "Game Over") {
        vector<char> rolls;
        pair<int, int> curr_frame{-1, -1};
        for (size_t i{0}; i < line.size(); i += 2) {
            rolls.push_back(line[i]);
        }
        cout << scoreGame(rolls) << endl;
        getline(cin, line);
    }

    return EXIT_SUCCESS;
}
