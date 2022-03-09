// UVA :: 11581 :: Grid Successors
// https://onlinejudge.org/external/115/11581.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const vector<pair<int, int>> OFFSETS{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

struct Grid {
    bitset<9> grid;

    int indexOf(int r, int c) const {
        return (r * 3) + c;
    }

    void clear() {
        grid.reset();
    }

    void set(int r, int c) {
        grid.set(indexOf(r, c));
    }

    void reset(int r, int c) {
        grid.reset(indexOf(r, c));
    }

    bool test(int r, int c) const {
        return grid.test(indexOf(r, c));
    }

    bool isZeros() const {
        return grid.none();
    }

    bool inbounds(int r, int c) const  {
        return r >= 0 && r < 3 && c >= 0 && c < 3;
    }

    int sumNeighbors(int r, int c) const {
        int result{0};
        for (auto off : OFFSETS) {
            int r0{r + off.first};
            int c0{c + off.second};
            if (inbounds(r0, c0) && test(r0, c0)) {
                result += 1;
            }
        }
        return result;
    }

    friend ostream& operator<<(ostream &os, const Grid &grid);
};


ostream& operator<<(ostream &os, const Grid &grid) {
    for (int r{0}; r < 3; r++) {
        for (int c{0}; c < 3; c++) {
            if (grid.test(r, c)) {
                os << 1;
            } else {
                os << 0;
            }
        }
        os << endl;
    }
    return os;
}

void tick(Grid &currGrid, Grid &nextGrid) {
    nextGrid.clear();
    for (int r{0}; r < 3; r++) {
        for (int c{0}; c < 3; c++) {
            if (currGrid.sumNeighbors(r, c) % 2) {
                nextGrid.set(r, c);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    string line;
    getline(cin, line);  // Read trailing newline.
    getline(cin, line);  // Read blank line.
    while(testCases) {

        Grid currGrid;
        Grid nextGrid;


        for (int r{0}; r < 3; r++) {
            getline(cin, line);
            for (int c{0}; c < 3; c++) {
                if (line.at(c) == '1') {
                    currGrid.set(r, c);
                }
            }
        }
        getline(cin, line);  // Read blank line.

        int ticks{-1};
        while (!currGrid.isZeros()) {
            tick(currGrid, nextGrid);
            ticks++;
            swap(currGrid, nextGrid);
        }
        cout << ticks << endl;
        --testCases;
    }
    return EXIT_SUCCESS;
}
