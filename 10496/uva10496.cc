// UVA :: 10496 :: Collecting Beepers
// https://onlinejudge.org/external/104/10496.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x{0}, y{0};
};

struct Solver {
    Point init;
    int beeperCount{0}, ALL_VISITED{0};
    vector<Point> beepers;
    vector<vector<int>> cache;

    Solver(Point _init, int _beeperCount, const vector<Point>& _beepers) {
        beeperCount = _beeperCount;
        init = _init;
        beepers = _beepers;
        ALL_VISITED = (1 << beeperCount) - 1;

        // Set up cache.
        // cache[ends at][visited set] = min distance
        cache = vector<vector<int>>(beeperCount, vector<int>(ALL_VISITED+1, INT_MAX));
    }

    // Return the manhattan distance between beepers[i] and beepers[j].
    int manhattanDistance(int i, int j) {
        return abs(beepers[i].x - beepers[j].x) + abs(beepers[i].y - beepers[j].y);
    }

    int solve() {
        return solve(0, 1);
    }

    int solve(int lastVisited, int visitedBeepers) {
        if (cache[lastVisited][visitedBeepers] == INT_MAX) {
            if (visitedBeepers == ALL_VISITED) {
                cache[lastVisited][visitedBeepers] = manhattanDistance(lastVisited, 0);
            } else {
                int result{INT_MAX};
                for (int beeper{1}; beeper < beeperCount; ++beeper) {
                    int mask{1 << beeper};
                    if ((mask & visitedBeepers) == 0) {
                        result = min(
                            result,
                            manhattanDistance(lastVisited, beeper) + solve(beeper, visitedBeepers | mask)
                        );
                    }
                }
                cache[lastVisited][visitedBeepers] = result;
            }
        }
        return cache[lastVisited][visitedBeepers];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while (testCases--) {
        int height{0}, width{0}, beeperCount{0};
        Point init;
        cin >> height >> width >> init.x >> init.y >> beeperCount;
        vector<Point> beepers(beeperCount+1);
        beepers[0] = init;
        for (int i{1}; i <= beeperCount; ++i) {
            cin >> beepers[i].x >> beepers[i].y;
        }
        Solver solver(init, beeperCount+1, beepers);
        cout << "The shortest path has length " << solver.solve() << endl;
    }
    return EXIT_SUCCESS;
}
