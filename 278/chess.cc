// UVA :: 278 :: Chess
// https://onlinejudge.org/external/2/278.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

class Board {

        vector<vector<int>> board;

        const vector<pair<int, int>> knightOffsets{
            {1, 2}, {-1, 2}, {1, -2}, {-1, -2},
            {2, 1}, {-2, 1}, {2, -1}, {-2, -1}
        };

        const vector<pair<int, int>> kingOffsets{
            {0, 1}, {0, -1}, {1, 0}, {-1, 0},
            {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        };

        const vector<pair<int, int>> queenOffsets{
            {-1, -1}, {1, 1}, {-1, 1}, {1, -1},
            {0, 1}, {-1, 0}, {1, 0}, {0, -1}
        };

        const vector<pair<int, int>> rookOffsets{
            {0, 1}, {-1, 0}, {1, 0}, {0, -1}
        };

        bool inbounds(int r, int c) {
            return r >= 0 && r < rows && c >= 0 && c < cols;
        }

        void mark(int incr, const char piece, int r, int c) {
            switch(piece) {
                case 'r': //
                    for (auto off : rookOffsets) {
                        int r0{r}, c0{c};
                        r0 += off.first;
                        c0 += off.second;
                        while (inbounds(r0, c0)) {
                            board[r0][c0] += incr;
                            r0 += off.first;
                            c0 += off.second;
                        }
                    }
                    break;
                case 'k':   // knight
                    for (auto pr : knightOffsets) {
                        int r0 = r + pr.first;
                        int c0 = c + pr.second;
                        if (inbounds(r0, c0)) {
                            board[r0][c0] += incr;
                        }
                    }
                    break;
                case 'Q':   // queen
                    for (auto off : queenOffsets) {
                        int r0{r}, c0{c};
                        r0 += off.first;
                        c0 += off.second;
                        while (inbounds(r0, c0)) {
                            board[r0][c0] += incr;
                            r0 += off.first;
                            c0 += off.second;
                        }
                    }
                    break;
                case 'K':   // king
                    for (auto pr : kingOffsets) {
                        int r0 = r + pr.first;
                        int c0 = c + pr.second;
                        if (inbounds(r0, c0)) {
                            board[r0][c0] += incr;
                        }
                    }
                    break;
            }
            // Mark the piece itself.
            board[r][c] += incr;
        }

    public:

        int rows{0}, cols{0};

        Board(int r, int c) {
            rows = r;
            cols = c;
            board = vector<vector<int>>(rows, vector<int>(cols, 0));
        }

        bool cellOpen(int r, int c) const {
            return board[r][c] == 0;
        }

        void mark(char piece, int r, int c) {
            mark(1, piece, r, c);
        }

        void unmark(char piece, int r, int c) {
            mark(-1, piece, r, c);
        }

        friend ostream& operator<<(ostream &out, const Board &board);
};

ostream& operator<<(ostream &out, const Board &board) {
    for (int r{0}; r < board.rows; ++r) {
        for (int c{0}; c < board.cols; ++c) {
            if (board.cellOpen(r, c)) {
                out << ".";
            } else {
                out << "x";
            }
        }
        out << endl;
    }
    return out;
}

int dfs(char piece, int acc, Board &board) {
    int result = acc;
    for (int r{0}; r < board.rows; ++r) {
        for (int c{0}; c < board.cols; ++c) {
            if (board.cellOpen(r, c)) {
                board.mark(piece, r, c);
                result = max(result, dfs(piece, acc + 1, board));
                board.unmark(piece, r, c);
            }
        }
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
        int soln = dfs(piece, 0, board);
        cout << soln << endl;

        testCases--;
    }

    /* vector<char> T{'k', 'r', 'Q', 'K'}; */
    /* for (auto c : T) { */
    /*     Board board(8, 8); */
    /*     board.mark('x', c, 4, 4); */
    /*     cout << board << endl; */
    /*     board.mark('.', c, 4, 4); */
    /*     cout << board << endl; */
    /* } */
    return EXIT_SUCCESS;
}
