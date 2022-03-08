// UVA :: 10920 :: Spiral Tap
// https://onlinejudge.org/external/109/10920.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const vector<pair<int, int>> OFFSETS{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

struct Matrix {
    int matrixSize{0}, center{0}, cellCount{0}, currRow{0}, currCol{0},
        currIndex{0}, targetIndex{0}, currDirn{0}, currSteps{1};

    Matrix(int ms, int ti) {
        targetIndex = ti;
        matrixSize = ms;
        // Determine center of matrix.  Constraints say matrixSize is an
        // odd number less than 100,000.
        center = matrixSize / 2;
        // There are matrixSize^2 cells.
        cellCount = matrixSize*matrixSize;
    }

    bool inbounds(int r, int c) {
        return r >= 0 && r < matrixSize && c >= 0 && c < matrixSize;
    }

    void move(const pair<int, int> &dirn) {
        if (currIndex < targetIndex) {
            currRow += dirn.first;
            currCol += dirn.second;
            currIndex++;
        }
    }

    void printStatus(ostream &os) {
        os << "(" << currRow << ", " << currCol << ") @ " << currIndex << endl;
    }

    pair<int, int> find() {
        // Put our current position in the center.
        currRow = center; currCol = center;
        currIndex = 1; currDirn = 0; currSteps = 1;
        while (currIndex < targetIndex) {
            for (int i{0}; i < currSteps; ++i) {
                move(OFFSETS[currDirn]);
                if (currIndex == targetIndex) return {matrixSize-currRow, currCol+1};
            }
            currDirn = (currDirn + 1) % 4;
            for (int i{0}; i < currSteps; ++i) {
                move(OFFSETS[currDirn]);
                if (currIndex == targetIndex) return {matrixSize-currRow, currCol+1};
            }
            currDirn = (currDirn + 1) % 4;
            currSteps++;
        }
        // Convert into positive goes up and one based column.
        return {matrixSize-currRow, currCol+1};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    // 1, 1, 2, 2, 3, 3, 4, 4, ...

    int matrixSize{0}, targetIndex{0};
    cin >> matrixSize >> targetIndex;
    while (matrixSize || targetIndex) {
        Matrix M(matrixSize, targetIndex);
        pair<int, int> soln = M.find();
        cout << "Line = " << soln.first << ", column = " << soln.second << "." << endl;
        cin >> matrixSize >> targetIndex;
    }

    return EXIT_SUCCESS;
}
