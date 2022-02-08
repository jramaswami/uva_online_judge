// UVA :: 556 :: Amazing
// https://onlinejudge.org/external/5/556.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct position {
    int row;
    int col;

    bool operator==(const position& other) const {
        return row == other.row && col == other.col;
    }

    bool operator!=(const position& other) const {
        return row != other.row || col != other.col;
    }
};


struct direction {
    int roff;
    int coff;

    bool operator==(const direction& other) const {
        return roff == other.roff && coff == other.coff;
    }
};

vector<direction> directions{{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

direction turnLeft(const direction dirn) {
    auto it = find(directions.begin(), directions.end(), dirn);
    if (it == (directions.end() - 1)) {
        return directions[0];
    }
    return *(it + 1);
}

direction turnRight(const direction dirn) {
    auto it = find(directions.begin(), directions.end(), dirn);
    if (it == directions.begin()) {
        return directions[3];
    }
    return *(it - 1);
}

position move(const position posn, const direction dirn) {
    return position{posn.row + dirn.roff, posn.col + dirn.coff};
}


bool outOfBounds(const position posn, const vector<vector<int>> &maze) {
    int rowCount = static_cast<int>(maze.size());
    int colCount = static_cast<int>(maze[0].size());
    return posn.row < 0 || posn.row >= rowCount || posn.col < 0 || posn.col >= colCount;
}

bool isWall(const position posn, const vector<vector<int>> &maze) {
    // Entrance
    /*
    int rowCount = static_cast<int>(maze.size());
    if (posn.row == rowCount - 1 && posn.col == -1) {
        return false;
    }
    */
    return outOfBounds(posn, maze) || maze[posn.row][posn.col] == 1;
}

bool wallToRight(const position posn, const direction dirn, const vector<vector<int>> &maze) {
    direction dirnRight = turnRight(dirn);
    position posnRight = move(posn, dirnRight);
    return isWall(posnRight, maze);
}

bool wallInFront(const position posn, const direction dirn, const vector<vector<int>> &maze) {
    position posnFront = move(posn, dirn);
    return isWall(posnFront, maze);
}

vector<int> solve(vector<vector<int>> &maze) {
    vector<int> soln{0, 0, 0, 0, 0};

    vector<vector<int>> visits(maze.size());
    for (size_t r = 0; r < maze.size(); r++) {
        visits[r] = vector<int>(maze[r].size());
    }

    // Initial position and direction.
    /*
    position initPosn{static_cast<int>(maze.size()) - 1, -1};
    direction currDirn = directions[0];
    position currPosn = move(initPosn, currDirn);
    */
    // TODO: Fix first square visits?
    position initPosn{static_cast<int>(maze.size()) - 1, 0};
    direction currDirn = directions[0];
    position currPosn{initPosn.row, initPosn.col};
    do {
        if (!wallToRight(currPosn, currDirn, maze)) {
            // Turn right.
            currDirn = turnRight(currDirn);
            // Moving out of this cell, count it as visited.
            visits[currPosn.row][currPosn.col]++;
            // Move.
            currPosn = move(currPosn, currDirn);
        } else if (wallInFront(currPosn, currDirn, maze)) {
            // Turn left.
            currDirn = turnLeft(currDirn);
        } else {
            // Moving out of this cell, count it as visited.
            visits[currPosn.row][currPosn.col]++;
            // Move.
            currPosn = move(currPosn, currDirn);
        }
    } while (currPosn != initPosn);

    // Count visits.
    for (size_t r = 0; r < maze.size(); r++) {
        for (size_t c = 0; c < maze[r].size(); c++) {
            if (maze[r][c] == 0) {
                int v = visits[r][c];
                soln[v]++;
            }
        }
    }
    return soln;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int rows, cols;
    string line;
    while (1) {
        // Read the maze dimensions.
        cin >> rows >> cols;
        if (rows == 0 && cols == 0) {
            break;
        }

        getline(cin, line); // read the rest of the line.

        // Read the maze.
        vector<vector<int>> maze(rows);
        for (int r = 0; r < rows; r++) {
            maze[r] = vector<int>(cols);
            getline(cin, line);
            for (int c = 0; c < cols; c++) {
                if (line.at(c) == '1') {
                    maze[r][c] = 1;
                } else {
                    maze[r][c] = 0;
                }
            }
        }
        vector<int> soln = solve(maze);
        // TODO: Padding for the output.
        for (int i = 0; i < 5; i++) {
            cout << setw(3) << right << soln[i];
        }
        cout << endl;
    }
    return EXIT_SUCCESS;
}
