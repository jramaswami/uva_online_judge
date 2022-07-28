// UVA :: 11831 :: Sticker Collector Robots
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const pair<int, int> EAST{0, 1};
const pair<int, int> WEST{0, -1};
const pair<int, int> SOUTH{1, 0};
const pair<int, int> NORTH{-1, 0};
const vector<pair<int, int>> ORIENTATIONS{EAST, SOUTH, WEST, NORTH};

struct Robot {
    int r, c, orientation;

    Robot turnRight() {
        return Robot{r, c, (orientation + 1) % 4};
    }

    Robot turnLeft() {
        return Robot{r, c, (orientation - 1 + 4) % 4};
    }

    Robot moveForward() {
        return Robot {
            r + ORIENTATIONS[orientation].first,
            c + ORIENTATIONS[orientation].second,
            orientation
        };
    }
};

struct Grid {
    int rowCount, columnCount;
    vector<string> grid;

    Grid(int r, int c) {
        rowCount = r;
        columnCount = c;
        grid = vector<string>(rowCount);
    }

    bool inbounds(int r, int c) {
        return r >= 0 && r < rowCount && c >= 0 && c < columnCount;
    }

    bool isSticker(int r, int c) {
        return grid[r][c] == '*';
    }

    bool isPillar(int r, int c) {
        return grid[r][c] == '#';
    }

    void pickupSticker(int r, int c) {
        grid[r][c] = '.';
    }

    Robot findRobot() {
        for (int r{0}; r < rowCount; r++) {
            for (int c{0}; c < columnCount; c++) {
                if (grid[r][c] == 'L') {
                    return Robot{r, c, 0};
                } else if (grid[r][c] == 'S') {
                    return Robot{r, c, 1};
                } else if (grid[r][c] == 'O') {
                    return Robot{r, c, 2};
                } else if (grid[r][c] == 'N') {
                    return Robot{r, c, 3};
                }
            }
        }
        return Robot{0, 0, 0};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int rowCount{0}, columnCount{0}, instructionCount{0};
    cin >> rowCount >> columnCount >> instructionCount;
    while (rowCount || columnCount || instructionCount) {
        // Read input.
        string junk, instructions;
        Grid grid(rowCount, columnCount);
        getline(cin, junk);  // Read trailing newline.
        for (int r{0}; r < rowCount; r++) {
            getline(cin, grid.grid[r]);
        }
        getline(cin, instructions);
        // Find the robot's position and initial orientation.
        Robot robot = grid.findRobot();
        // Follow instructions, unless stalled.
        int stickersFound{0};
        for (char instruction : instructions) {
            // Turn or move robot.
            switch (instruction) {
                case 'D':
                    robot = robot.turnRight();
                    break;
                case 'E':
                    robot = robot.turnLeft();
                    break;
                case 'F':
                    Robot robot0 = robot.moveForward();
                    if (grid.inbounds(robot0.r, robot0.c) && !grid.isPillar(robot0.r, robot0.c)) {
                        robot = robot0;
                    }
                    break;
            }
            if (grid.isSticker(robot.r, robot.c)) {
                stickersFound++;
                grid.pickupSticker(robot.r, robot.c);
            }
        }
        cout << stickersFound << "\n";
        cin >> rowCount >> columnCount >> instructionCount;
    }
    return EXIT_SUCCESS;
}
