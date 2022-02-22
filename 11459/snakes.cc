// UVA :: 11459 :: Snakes and Ladders
// https://onlinejudge.org/external/114/11459.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while (testCases) {
        int playerCount{0}, snakeCount{0}, rollCount{0};
        cin >> playerCount >> snakeCount >> rollCount;
        vector<int> snakesAndLadders(101, -1);
        while (snakeCount) {
            int u{0}, v{0};
            cin >> u >> v;
            snakesAndLadders[u] = v;
            snakeCount--;
        }

        vector<int> playerLocations(playerCount, 1);
        int currPlayer{0};

        int currRoll{0};
        bool winner{false};
        while (rollCount) {
            cin >> currRoll;
            if (!winner && playerCount) {
                int currLocation{playerLocations[currPlayer]};
                currLocation = min(100, currLocation + currRoll);
                if (snakesAndLadders[currLocation] != -1) {
                    currLocation = snakesAndLadders[currLocation];
                }
                playerLocations[currPlayer] = currLocation;
                if (currLocation == 100) {
                    // Winner!
                    winner = true;
                }
                currPlayer = ((currPlayer + 1) % playerCount);
            }
            rollCount--;
        }

        for (int p{0}; p < playerCount; ++p) {
            cout << "Position of player " << (p + 1) << " is "
                 << playerLocations[p] << "." << endl;
        }

        testCases--;
    }
    return EXIT_SUCCESS;
}
