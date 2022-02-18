// UVA :: 278 :: Chess
// https://onlinejudge.org/external/2/278.pdf
// jramaswami

// Knights is half the squares.
// Rooks is min(rows, cols).

#include <bits/stdc++.h>

using namespace std;


class Board {

        vector<vector<int>> board;

        const vector<pair<int, int>> knightOffsets{
            {-2, -1}, {-2, 1}, {2, -1}, {2, 1},
            {-1, -2}, {-1, 2}, {1, -2}, {1, 2}
        };

        bool inbounds(int r, int c) {
            return r >= 0 && r < rows && c >= 0 && c < cols;
        }

        void incr(int i, int r, int c) {
            board[r][c] += i;
            for (auto off : knightOffsets) {
                int r0{r + off.first};
                int c0{c + off.second};
                if (inbounds(r0, c0)) {
                    board[r][c] += i;
                }
            }
        }

    public:
        int rows{0}, cols{0}, pieces{0};

        Board (int r, int c) {
            rows = r;
            cols = c;
            board = vector<vector<int>>(rows, vector<int>(cols, 0));
        }

        void place(int r, int c) {
            incr(1, r, c);
            pieces++;
        }

        void remove(int r, int c) {
            incr(-1, r, c);
            pieces--;
        }

        bool isOpen(int r, int c) const {
            return board[r][c] == 0;
        }

        friend ostream& operator<<(ostream &os, const Board &board);
};


ostream& operator<<(ostream &os, const Board &board) {
    os << board.pieces << " pieces" << endl;
    for (int r{0}; r < board.rows; ++r) {
        for (int c{0}; c < board.cols; ++c) {
            if (board.isOpen(r, c)) {
                os << '.';
            } else {
                os << 'x';
            }
        }
        os << endl;
    }
    return os;
}

int dfs(int r, int c, Board &board) {
    if (r >= board.rows) {
        /* cerr << board << endl; */
        return board.pieces;
    }

    if (c >= board.cols) {
        return dfs(r + 1, 0, board);
    }

    int result{dfs(r, c + 1, board)};
    if (board.isOpen(r, c)) {
        board.place(r, c);
        result = max(result, dfs(r, c + 1, board));
        board.remove(r, c);
    }
    return result;
}

int main() {
    int testCases{0}, filled{0};
    filled = scanf("%d\n", &testCases);
    assert(filled == 1);
    while (testCases) {
        char piece{'z'};
        int rows{0}, cols{0};
        filled = scanf("%c %d %d\n", &piece, &rows, &cols);
        assert(filled == 3);

        Board board(rows, cols);
        int soln{dfs(0, 0, board)};
        cout << soln << endl;

        testCases--;
    }

    return EXIT_SUCCESS;
}
