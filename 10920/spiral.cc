// UVA :: 10920 :: Spiral Tap
// https://onlinejudge.org/external/109/10920.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

typedef long long int number_t;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    number_t matrixSize{0}, targetIndex{0};
    cin >> matrixSize >> targetIndex;
    while (matrixSize || targetIndex) {

        // Binary search for the odd number squared that is greater than or
        // equal to the target.
        number_t k{matrixSize};
        number_t high{matrixSize};
        number_t low{0};
        while (low <= high) {
            number_t mid{low + ((high - low) / 2)};
            number_t oddMid{(mid*2) + 1};
            number_t midSq{oddMid * oddMid};
            if (midSq >= targetIndex) {
                k = min(oddMid, k);
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        number_t kSq{k * k};

        // TODO: figure out distance from center to square row.
        // The compute the center of the matrix.
        number_t center{1 + matrixSize / 2};

        // Figure out where k^2 is located in the matrix and the four corners
        // of its box.
        number_t sqDist{((k - 1) / 2)};
        number_t leftCol{center - sqDist};
        number_t rightCol{center + sqDist};
        number_t topRow = {center + sqDist};
        number_t bottomRow = {center - sqDist};

        // Figure out what is in the other four corners.
        number_t brVal{kSq - k + 1};
        number_t blVal{brVal - k + 1};
        number_t tlVal{blVal - k + 1};
        number_t prevKSq{tlVal - k + 1};
        assert (((k-2)*(k-2)) == prevKSq);

        number_t solnRow{-1}, solnCol{-1}, delta{0};
        if (brVal <= targetIndex && targetIndex <= kSq) {
            // Case 1: brVal < targetIndex <= k^2
            // The same column as the square number, the right column.
            delta = kSq - targetIndex;
            solnRow = topRow - delta;
            solnCol = rightCol;
        } else if (blVal < targetIndex && targetIndex <= brVal) {
            // Case 2: blVal < targetIndex <= brVal
            // The bottom row.
            solnRow = bottomRow;
            delta = brVal - targetIndex;
            solnCol = rightCol - delta;
        } else if (tlVal < targetIndex && targetIndex <= blVal) {
            // Case 3: tlVal < targetIndex <= blVal
            // The left column.
            solnCol = leftCol;
            delta = blVal - targetIndex;
            solnRow = bottomRow + delta;
        } else if (prevKSq < targetIndex && targetIndex <= tlVal) {
            // Case 4: prevKSq < targetIndex <= tlVal
            // The same row as the square number, the top column.
            solnRow = topRow;
            delta = tlVal - targetIndex;
            solnCol = leftCol + delta;
        }

        cout << "Line = " << solnRow << ", column = " << solnCol << "." << endl;
        cin >> matrixSize >> targetIndex;
    }

    return EXIT_SUCCESS;
}
