// UVA :: 1103 :: Ancient Messages
// jramaswami

#include <bits/stdc++.h>

using namespace std;

/*
const vector<pair<int, int>> OFFSETS{
    {0, 1}, {0, -1}, {1, 0}, {-1, 0},
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
};
*/

const vector<pair<int, int>> OFFSETS{
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}
};

const vector<char> SIGNS{'A', 'D', 'J', 'K', 'S', 'W'};
const vector<int> SPACE_TO_SIGN{-1, 5, 0, 3, 2, 3, 1};

const int BLACK{1};
const int WHITE{0};

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int H{0}, W{0}, caseNo{1};
    cin >> H >> W;
    while (H && W) {
        vector<vector<int>> bitmap(H, vector<int>(W * 4, false));

        /* cerr << H << "x" << W << endl; */
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
                        bitmap[h][w] = 1;
                    }
                    w++;
                }
            }
        }

        // Assign an id to all the connected components.
        // Record the black components.
        vector<vector<int>> id(H, vector<int>(W * 4, 0));
        int blackCounter{0};
        int whiteCounter{0};
        int currId{0};
        vector<set<pair<int, int>>> blackComponents;
        for (int r{0}; r < H; r++) {
            for (int c{0}; c < W * 4; c++) {
                if (id[r][c] == 0) {
                    int currColor{bitmap[r][c]};
                    if (currColor == BLACK) {
                        blackCounter--;
                        currId = blackCounter;
                        blackComponents.push_back(set<pair<int, int>>());
                    } else {
                        whiteCounter++;
                        currId = whiteCounter;
                    }
                    id[r][c] = currId;
                    deque<pair<int, int>> queue;
                    queue.emplace_back(r, c);
                    while (!queue.empty()) {
                        int r0{queue.front().first}, c0{queue.front().second};
                        if (currColor == BLACK) {
                            blackComponents.back().insert(queue.front());
                        }
                        queue.pop_front();
                        for (pair<int, int> off : OFFSETS) {
                            int r1{r0 + off.first}, c1{c0 + off.second};
                            if (r1 >= 0 && r1 < H && c1 >= 0 && c1 < (W * 4)) {
                                if (bitmap[r1][c1] == currColor && id[r1][c1] == 0) {
                                    id[r1][c1] = currId;
                                    queue.emplace_back(r1, c1);
                                }
                            }
                        }
                    }
                }
            }
        }

        // For each black component, count the number of white components
        // it is touching.
        vector<int> freqs{0, 0, 0, 0, 0, 0};
        for (auto component : blackComponents) {
            set<int> whiteComponents;
            for (auto posn : component) {
                int r{posn.first}, c{posn.second};
                for (auto off : OFFSETS) {
                    int r0{r + off.first}, c0{c + off.second};
                    if (r0 >= 0 && r0 < H && c0 >= 0 && c0 < (4 * W)) {
                        if (id[r0][c0] > 0) {
                            whiteComponents.insert(id[r0][c0]);
                        }
                    }
                }
            }
            int t{SPACE_TO_SIGN[whiteComponents.size()]};
            freqs[t]++;
        }

        cout << "Case " << caseNo << ": ";
        for (int i{0}; i < 6; i++) {
            for (int j{0}; j < freqs[i]; j++) {
                cout << SIGNS[i];
            }
        }
        cout << "\n";
        /*
        for (auto row : id) {
            for (auto x : row) {
                if (x < 0) {
                    cout << x;
                } else {
                    cout << " " << x;
                }
            }
            cerr << endl;
        }
        */

        for (auto row : bitmap) {
            copy(row.begin(), row.end(), ostream_iterator<int>(cerr, ""));
            cerr << endl;
        }
        cerr << endl;

        cin >> H >> W;
        caseNo++;
    }
    return EXIT_SUCCESS;
}
