// UVA :: 10855 :: Rotated squares
// https://onlinejudge.org/external/108/10855.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

typedef vector<char> row_t;
typedef vector<row_t> matrix_t;

void printMatrix(const matrix_t &matrix, ostream &os) {
    for (auto row : matrix) {
        copy(row.begin(), row.end(), ostream_iterator<char>(os, ""));
        os << endl;
    }
}

vector<vector<char>> transposeMatrix(const vector<vector<char>> &matrix) {
    size_t rows{matrix.size()};
    size_t cols{matrix[0].size()};
    matrix_t result(cols, row_t(rows, 0));
    for (size_t r{0}; r < rows; ++r) {
        for (size_t c{0}; c < cols; ++c) {
            result[c][r] = matrix[r][c];
        }
    }
    return result;
}

matrix_t reverseMatrix(const matrix_t &matrix) {
    size_t rows{matrix.size()};
    size_t cols{matrix[0].size()};
    matrix_t result(rows, row_t(cols, 0));
    for (size_t r{0}; r < rows; ++r) {
        copy(matrix[r].crbegin(), matrix[r].crend(), result[r].begin());
    }
    return result;
}

matrix_t rotateClockwise90(const matrix_t &matrix) {
    return reverseMatrix(transposeMatrix(matrix));
}

bool matrixMatch(size_t r, size_t c, const matrix_t &haystack, const matrix_t &needle) {
    for (size_t r0{0}; r0 < needle.size(); ++r0) {
        for (size_t c0{0}; c0 < needle.size(); ++c0) {
            if (needle[r0][c0] != haystack[r+r0][c+c0]) {
                return false;
            }
        }
    }
    return true;
}

int countMatches(const matrix_t &haystack, const matrix_t &needle) {
    /* cerr << "countMatches" << endl; */
    /* printMatrix(needle, cerr); */
    int result{0};
    for (size_t r{0}; r + needle.size() <= haystack.size(); ++r) {
        for (size_t c{0}; c + needle.size() <= haystack.size(); ++c) {
            if (matrixMatch(r, c, haystack, needle)) {
                result++;
            }
        }
    }
    return result;
}

vector<int> solve(const matrix_t &haystack, const vector<matrix_t> &needles) {
    vector<int> result(needles.size(), 0);
    for (size_t i{0}; i < needles.size(); ++i) {
        /* cerr << "checking needle " << i << endl; */
        result[i] = countMatches(haystack, needles[i]);
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    size_t N{0}, n{0};
    cin >> N >> n;
    string line;
    while (N || n) {
        /* cerr << "N=" << N << " n=" << n << endl; */
        // Read trailing newline.
        getline(cin, line);
        // Read larger matrix.
        matrix_t haystack;
        haystack.reserve(N);
        for (size_t r{0}; r < N; r++) {
            getline(cin, line);
            row_t row(line.begin(), line.end());
            haystack.push_back(row);
        }

        /* printMatrix(haystack, cerr); */

        // Read smaller matrix.
        matrix_t needle0;
        needle0.reserve(n);
        for (size_t r{0}; r < n; r++) {
            getline(cin, line);
            row_t row(line.begin(), line.end());
            needle0.push_back(row);
        }

        // Generate rotations.
        vector<matrix_t> needles;
        needles.push_back(needle0);
        for (int i{0}; i < 3; ++i) {
            needles.push_back(rotateClockwise90(needles.back()));
        }

        // Solve
        vector<int> soln = solve(haystack, needles);
        for (size_t i{0}; i < soln.size(); ++i) {
            cout << soln[i];
            if (i < soln.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;

        cin >> N >> n;
    }
    return EXIT_SUCCESS;
}
