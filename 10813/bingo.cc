// UVA :: 10813 :: Traditional BINGO
// https://onlinejudge.org/external/108/10813.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> row_t;
typedef vector<row_t> board_t;

const int SIZE{5};
const int BINGO_CALLS{75};


bool rowWinner(const board_t &board, int r) {
    for (int c{0}; c < SIZE; c++) {
        if (board[r][c] > 0) {
            return false;
        }
    }
    return true;
}

bool colWinner(const board_t &board, int c) {
    for (int r{0}; r < SIZE; r++) {
        if (board[r][c] > 0) {
            return false;
        }
    }
    return true;
}

bool leftDiagonalWinner(const board_t &board) {
    int r1{0}, c1{0};
    while (r1 < SIZE) {
        if (board[r1][c1] > 0) {
            return false;
        }
        r1++; c1++;
    }
    return true;
}

bool rightDiagonalWinner(const board_t &board) {
    int r1{0}, c1{SIZE-1};
    while (r1 < SIZE) {
        if (board[r1][c1] > 0) {
            return false;
        }
        r1++; c1--;
    }
    return true;
}

bool isWinner(const board_t &board) {
    for (int d{0}; d < SIZE; d++) {
        if (colWinner(board, d) || rowWinner(board, d)) {
            return true;
        }
    }
    return leftDiagonalWinner(board) || rightDiagonalWinner(board);
}

void mark(board_t &board, int call) {
    for (int r{0}; r < SIZE; r++) {
        for (int c{0}; c < SIZE; c++) {
            if (board[r][c] == call) {
                board[r][c] = -call;
            }
        }
    }
}

int playGame(const vector<int> &calls, board_t &board) {
    int ticks{1};
    for (auto call : calls) {
        mark(board, call);
        /*
        cerr << "tick " << ticks << " call " << call << endl;
        for (auto row : board) {
            copy(row.begin(), row.end(), ostream_iterator<int>(cerr, " "));
            cerr << endl;
        }
        cerr << endl;
        */
        if (isWinner(board)) {
            return(ticks);
        }
        ticks++;
    }
    return ticks;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T{0};
    cin >> T;
    while (T) {
        board_t board;
        for (int r{0}; r < SIZE; r++) {
            int toRead{SIZE};
            if (r == 2) toRead--;
            row_t row;
            copy_n(istream_iterator<int>(cin), toRead, back_inserter(row));
            board.push_back(row);
        }
        // Fix row 3.
        board[2].push_back(0);
        board[2][4] = board[2][3];
        board[2][3] = board[2][2];
        board[2][2] = 0;

        vector<int> bingoCalls;
        bingoCalls.reserve(75);
        copy_n(istream_iterator<int>(cin), BINGO_CALLS, back_inserter(bingoCalls));

        int ticks{playGame(bingoCalls, board)};
        cout << "BINGO after " << ticks << " numbers announced" << endl;

        T--;
    }
    return EXIT_SUCCESS;
}
