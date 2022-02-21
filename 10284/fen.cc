// UVA :: 10284 :: Chessboard in FEN
// https://onlinejudge.org/external/102/10284.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

class Board {
    // Black starts at row 0,1
    // White starts at row 6,7.

        vector<vector<char>> board = vector<vector<char>>(8, vector<char>(8, '.'));

        vector<pair<int, int>> rookOffsets{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        vector<pair<int, int>> bishopOffsets{{1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
        vector<pair<int, int>> queenKingOffsets{{0, 1}, {1, 0}, {0, -1}, {-1, 0},
                                               {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
        };
        vector<pair<int, int>> knightOffsets{{2, 1}, {-2, 1}, {2, -1}, {-2, -1},
                                             {1, 2}, {-1, 2}, {1, -2}, {-1, -2}
        };
        vector<pair<int, int>> whitePawnOffsets{{-1, 1}, {-1, -1}};
        vector<pair<int, int>> blackPawnOffsets{{1, 1}, {1, -1}};

        bool inbounds(int r, int c) {
            return r >= 0 && r < 8 && c >= 0 && c < 8;
        }

        bool isOpen(int r, int c) {
            return board[r][c] == '.' || board[r][c] == 'x';
        }

        void attack(int r, int c) {
            char p = board[r][c];
            switch(p) {
                case 'n':
                case 'N':
                    for (auto off : knightOffsets) {
                        int r0{r + off.first};
                        int c0{c + off.second};
                        if (inbounds(r0, c0) && isOpen(r0, c0)) {
                            board[r0][c0] = 'x';
                        }
                    }
                    break;
                case 'k':
                case 'K':
                    for (auto off : queenKingOffsets) {
                        int r0{r + off.first};
                        int c0{c + off.second};
                        if (inbounds(r0, c0) && isOpen(r0, c0)) {
                            board[r0][c0] = 'x';
                        }
                    }
                    break;
                case 'p':
                    for (auto off : blackPawnOffsets) {
                        int r0{r + off.first};
                        int c0{c + off.second};
                        if (inbounds(r0, c0) && isOpen(r0, c0)) {
                            board[r0][c0] = 'x';
                        }
                    }
                    break;
                case 'P':
                    for (auto off : whitePawnOffsets) {
                        int r0{r + off.first};
                        int c0{c + off.second};
                        if (inbounds(r0, c0) && isOpen(r0, c0)) {
                            board[r0][c0] = 'x';
                        }
                    }
                    break;
                case 'b':
                case 'B':
                    for (auto off : bishopOffsets) {
                        int r0{r + off.first};
                        int c0{c + off.second};
                        while (inbounds(r0, c0) && isOpen(r0, c0)) {
                            board[r0][c0] = 'x';
                            r0 += off.first;
                            c0 += off.second;
                        }
                    }
                    break;
                case 'r':
                case 'R':
                    for (auto off : rookOffsets) {
                        int r0{r + off.first};
                        int c0{c + off.second};
                        while (inbounds(r0, c0) && isOpen(r0, c0)) {
                            board[r0][c0] = 'x';
                            r0 += off.first;
                            c0 += off.second;
                        }
                    }
                    break;
                    break;
                case 'q':
                case 'Q':
                    for (auto off : queenKingOffsets) {
                        int r0{r + off.first};
                        int c0{c + off.second};
                        while (inbounds(r0, c0) && isOpen(r0, c0)) {
                            board[r0][c0] = 'x';
                            r0 += off.first;
                            c0 += off.second;
                        }
                    }
                    break;
                    break;
            }
        }

    public:

        void place(int r, int c, char p) {
            board[r][c] = p;
        }

        void attack() {
            for (int r{0}; r < 8; ++r) {
                for (int c{0}; c < 8; ++c) {
                    if (isalpha(board[r][c]) && board[r][c] != 'x') {
                        attack(r, c);
                    }
                }
            }
        }

        int countSafe() {
            int soln{0};
            for (int r{0}; r < 8; ++r) {
                for (int c{0}; c < 8; ++c) {
                    if (board[r][c] == '.') {
                        soln++;
                    }
                }
            }
            return soln;
        }

        friend ostream& operator<<(ostream &os, const Board &board);
};

ostream& operator<<(ostream &os, const Board &board) {
    for (auto row : board.board) {
        copy(row.begin(), row.end(), ostream_iterator<char>(os, ""));
        os << endl;
    }
    return os;
}

void parse(const string &line, Board &board) {
    int r{0};
    int c{0};
    for (char t : line) {
        if (t == '/') {
            c = 0;
            r++;
        } else if (isdigit(t)) {
            int off{t - '0'};
            c += off;
        } else {
            board.place(r, c, t);
            c++;
        }
    }
}

int solve(const string &line) {
    Board board;
    parse(line, board);
    board.attack();
    // cerr << board << endl;
    return board.countSafe();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    string line;
    while (getline(cin, line)) {
        int soln{solve(line)};
        cout << soln << endl;
    }
    return EXIT_SUCCESS;
}
