// UVA :: 183 :: Bit Maps
// https://onlinejudge.org/external/1/183.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Posn {
    int row{0}, col{0};
    Posn(int r, int c): row{r}, col{c} { }
};

ostream& operator<< (ostream &os, const Posn &p) {
    os << "P(" << p.row << "," << p.col << ")";
    return os;
}

struct Rectangle {
    Posn tl, br;
    Rectangle(Posn _tl, Posn _br): tl{_tl}, br{_br} {}
};

ostream& operator<< (ostream &os, const Rectangle &rect) {
    os << "Rect(" << rect.tl << "; " << rect.br << ")";
    return os;
}

vector<Rectangle> split(Rectangle rect) {
    vector<Rectangle> result;
    if (rect.br.row == rect.tl.row) {
        int colMid = rect.tl.col + ((rect.br.col - rect.tl.col) / 2);
        Rectangle lfRect(Posn(rect.tl.row, rect.tl.col), Posn(rect.tl.row, colMid));
        Rectangle rtRect(Posn(rect.br.row, colMid+1), Posn(rect.br.row, rect.br.col));
        return {lfRect, rtRect};
    } else if (rect.tl.col == rect.br.col) {
        int rowMid = rect.tl.row + ((rect.br.row - rect.tl.row) / 2);
        Rectangle topRect(Posn(rect.tl.row, rect.tl.col), Posn(rowMid, rect.tl.col));
        Rectangle botRect(Posn(rowMid+1, rect.br.col), Posn(rect.br.row, rect.br.col));
        return {topRect, botRect};
    } else {
        int rowMid = rect.tl.row + ((rect.br.row - rect.tl.row) / 2);
        int colMid = rect.tl.col + ((rect.br.col - rect.tl.col) / 2);
        Rectangle tlRect(Posn(rect.tl.row, rect.tl.col), Posn(rowMid, colMid));
        Rectangle trRect(Posn(rect.tl.row, colMid+1), Posn(rowMid, rect.br.col));
        Rectangle blRect(Posn(rowMid+1, rect.tl.col), Posn(rect.br.row, colMid));
        Rectangle brRect(Posn(rowMid+1, colMid+1), Posn(rect.br.row, rect.br.col));
        return {tlRect, trRect, blRect, brRect};
    }
}

struct DecompToBinary {
    vector<vector<char>> grid;
    int rows{0}, cols{0}, index{0};
    string decomp;

    DecompToBinary(int _rows, int _cols, string &_decomp) {
        rows = _rows;
        cols = _cols;
        decomp = _decomp;
        grid = vector<vector<char>>(rows, vector<char>(cols, '0'));
    }

    void fill(const Rectangle &rect, char val) {
        for (int r{rect.tl.row}; r <= rect.br.row; ++r) {
            for (int c{rect.tl.col}; c <= rect.br.col; ++c) {
                grid[r][c] = val;
            }
        }
    }

    void decompToBinary(Rectangle &rect) {
        if (decomp[index] == 'D') {
            // Expect four quadrants
            index++;
            vector<Rectangle> quarters = split(rect);
            for (auto r : quarters) {
                decompToBinary(r);
            }
        } else {
            fill(rect, decomp[index]);
            index++;
        }
    }

    void decompToBinary() {
        Posn tl(0, 0);
        Posn br(rows-1, cols-1);
        Rectangle rect(tl, br);
        decompToBinary(rect);
    }
};

struct BinaryToDecomp {
    vector<vector<char>> grid;
    int rows{0}, cols{0};
    string decomp;

    BinaryToDecomp(int _rows, int _cols, string &binary){
        rows = _rows;
        cols = _cols;
        grid = vector<vector<char>>(rows, vector<char>(cols));
        for (size_t i{0}; i < binary.size(); ++i) {
            size_t r = i / cols;
            size_t c = i % cols;
            grid[r][c] = binary[i];
        }
    }

    bool rectAllTheSame(Rectangle rect) {
        for (int r{rect.tl.row}; r <= rect.br.row; ++r) {
            for (int c{rect.tl.col}; c <= rect.br.col; ++c) {
                if (grid[r][c] != grid[rect.tl.row][rect.tl.col]) {
                    return false;
                }
            }
        }
        return true;
    }

    void binaryToDecomp(Rectangle rect) {
        if (rectAllTheSame(rect)) {
            decomp.push_back(grid[rect.tl.row][rect.tl.col]);
        } else {
            decomp.push_back('D');
            vector<Rectangle> quarters = split(rect);
            for (auto r : quarters) {
                binaryToDecomp(r);
            }
        }
    }

    void binaryToDecomp() {
        Rectangle all(Posn(0, 0), Posn(rows-1, cols-1));
        binaryToDecomp(all);
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    string line;
    getline(cin, line);
    while (line != "#") {
        char type{line.at(0)};
        istringstream iss(string(line.begin()+1, line.end()));
        int rows{0}, cols{0};
        iss >> rows >> cols;
        // Following this line will be one or more lines containing the
        // sequence of ‘1’, ‘0’ and ‘D’ characters that represent the bit
        // map, with no intervening spaces. Each line (except the last,
        // which may be shorter) will contain 50 characters.
        string spec;
        getline(cin, line);
        // TODO: figure out how to read the spec without over reading!
        while (line[0] != '#' && line[1] != ' ') {
            spec.append(line);
            getline(cin, line);
        }

        if (type == 'B') {
            cout << "D" << setw(4) << rows << setw(4) << cols << endl;
            BinaryToDecomp btd(rows, cols, spec);
            btd.binaryToDecomp();
            size_t i{0};
            while (i < btd.decomp.size()) {
                cout << btd.decomp.substr(i, 50) << endl;
                i += 50;
            }
        }
        else if (type == 'D') {
            cout << "B" << setw(4) << rows << setw(4) << cols << endl;
            DecompToBinary dtb(rows, cols, spec);
            dtb.decompToBinary();
            string output;
            for (int r{0}; r < rows; ++r) {
                for (int c{0}; c < cols; ++c) {
                    output.push_back(dtb.grid[r][c]);
                }
            }
            size_t i{0};
            while (i < output.size()) {
                cout << output.substr(i, 50) << endl;
                i += 50;
            }
        }
    }
    return EXIT_SUCCESS;
}