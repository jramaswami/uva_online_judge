// UVA :: 1103 :: Ancient Messages
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const vector<pair<int, int>> OFFSETS{
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}
};

const vector<char> HOLES_TO_SIGN{'W', 'A', 'K', 'J', 'S', 'D'};

const int BLACK{1};
const int WHITE{0};
const int NONE{INT_MIN};
const int BACKGROUND{0};

unsigned int hexValue(char c) {
    if (c >= '0' && c <= '9') {
        return static_cast<unsigned int>(c - '0');
    }
    switch(c) {
        case 'a': return 10U; break;
        case 'b': return 11U; break;
        case 'c': return 12U; break;
        case 'd': return 13U; break;
        case 'e': return 14U; break;
        case 'f': return 15U; break;
    }
    return 0;
}

struct Bitmap {
    int height{0}, width{0}, currBlackId{0}, currWhiteId{-2};
    vector<vector<int>> grid;
    vector<vector<int>> component;

    Bitmap(int h, int w) {
        height = h;
        width = w;
        grid = vector<vector<int>>(height, vector<int>(width, 0));
        component = vector<vector<int>>(height, vector<int>(width, NONE));
    }

    bool inbounds(int r, int c) {
        return r >= 0 && r < height && c >= 0 && c < width;
    }

    void fill(int initR, int initC, int color, int id) {
        deque<pair<int, int>> queue;
        queue.emplace_back(initR, initC);
        component[initR][initC] = id;
        while (!queue.empty()) {
            int r{queue.front().first}, c{queue.front().second};
            queue.pop_front();
            for (pair<int, int> off : OFFSETS) { int r0{r + off.first}, c0{c + off.second};
                if (inbounds(r0, c0) && grid[r0][c0] == color && component[r0][c0] == NONE) {
                    queue.emplace_back(r0, c0);
                    component[r0][c0] = id;
                }
            }
        }
    }

    void fillBackground() {
        // Top row.
        for (int c{0}; c < width; c++) {
            if (grid[0][c] == WHITE && component[0][c] == NONE) {
                fill(0, c, WHITE, BACKGROUND);
            }
        }
        // Bottom row.
        for (int c{0}; c < width; c++) {
            if (grid[height-1][c] == WHITE && component[height-1][c] == NONE) {
                fill(height-1, c, WHITE, BACKGROUND);
            }
        }
        // Left side.
        for (int r{0}; r < height; r++) {
            if (grid[r][0] == WHITE && component[r][0] == NONE) {
                fill(r, 0, WHITE, BACKGROUND);
            }
        }
        // Right side.
        for (int r{0}; r < height; r++) {
            if (grid[r][width-1] == WHITE && component[r][width-1] == NONE) {
                fill(r, width-1, WHITE, BACKGROUND);
            }
        }
    }

    // Fill the black components.
    void fillBlack() {
        for (int r{0}; r < height; r++) {
            for (int c{0}; c < width; c++) {
                if (grid[r][c] == BLACK && component[r][c] == NONE) {
                    currBlackId++;
                    fill(r, c, BLACK, currBlackId);
                }
            }
        }
    }

    // Fill the white components.
    void fillWhite() {
        for (int r{0}; r < height; r++) {
            for (int c{0}; c < width; c++) {
                if (grid[r][c] == WHITE && component[r][c] == NONE) {
                    currWhiteId--;
                    fill(r, c, WHITE, currWhiteId);
                }
            }
        }
    }

    string findSymbols() {
        vector<set<int>> holes(currBlackId+1, set<int>());
        for (int r{0}; r < height; r++) {
            for (int c{0}; c < width; c++) {
                if (component[r][c] > 0) {
                    // Black component.
                    int compId{component[r][c]};
                    for (pair<int, int> off : OFFSETS) {
                        int r0{r + off.first}, c0{c + off.second};
                        if (inbounds(r0, c0) && component[r0][c0] < 0) {
                            holes[compId].insert(component[r0][c0]);
                        }
                    }
                }
            }
        }
        string result;
        for (int i{1}; i <= currBlackId; i++) {
            result.push_back(HOLES_TO_SIGN[holes[i].size()]);
        }
        sort(result.begin(), result.end());
        return result;
    }

    // Scan image and count the number of each symbol.
    string solve() {
        // Start by identifying the background.
        fillBackground();
        fillBlack();
        fillWhite();
        return findSymbols();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int H{0}, W{0}, caseNo{1};
    cin >> H >> W;
    while (H && W) {

        Bitmap bitmap(H, W*4);
        string junk, line;
        getline(cin, junk); // Read trailing newline.
        for (int h{0}; h < H; h++) {
            getline(cin, line);
            size_t w{0};
            for (auto c : line) {
                unsigned int x{hexValue(c)};
                for (int b{3}; b >= 0; b--) {
                    unsigned int mask{1U << b};
                    if (mask & x) {
                        bitmap.grid[h][w] = 1;
                    }
                    w++;
                }
            }
        }

        string soln{bitmap.solve()};
        cout << "Case " << caseNo << ": " << soln << "\n";

        cin >> H >> W;
        caseNo++;
    }
    return EXIT_SUCCESS;
}
