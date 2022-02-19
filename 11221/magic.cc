// UVA :: 11221 :: Magic square palindromes
// https://onlinejudge.org/external/112/11221.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

// Cache of squares.
unordered_map<int, int> squares;

vector<char> normalize(const string &line) {
    vector<char> result;
    for (auto c : line) {
        if (isalpha(c)) {
            result.push_back(static_cast<char>(tolower(c)));
        }
    }
    return result;
}

bool isPalindrome(const vector<char> &normal) {
    if (normal.size() < 2) {
        return true;
    }
    size_t left{0};
    size_t right{normal.size() - 1};
    while (left <= right) {
        if (normal[left] != normal[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

pair<int, int> nextFromTopLeft(pair <int, int> posn, int sqrt) {
    int row{posn.first};
    int col{posn.second};
    row++;
    if (row >= sqrt) {
        row = 0;
        col++;
    }
    return pair<int, int>{row, col};
}

pair<int, int> nextFromBottomRight(pair<int, int> posn, int sqrt) {
    int row{posn.first};
    int col{posn.second};
    row--;
    if (row < 0) {
        row = sqrt - 1;
        col--;
    }
    return pair<int, int>{row, col};
}

bool isSquarePalindrome(const vector<char> &normal, int sqrt) {
    pair<int, int> tl{0, 0};
    pair<int, int> br{sqrt-1, sqrt-1};
    while (br.second >= 0) {
        int tlIndex{(tl.first * sqrt) + tl.second};
        int brIndex{(br.first * sqrt) + br.second};
        if (normal[tlIndex] != normal[brIndex]){
            return false;
        }
        tl = nextFromTopLeft(tl, sqrt);
        br = nextFromBottomRight(br, sqrt);
    }
    return true;
}

int solve(const vector<char> &normal) {
    if (!isPalindrome(normal)) {
        return -1;
    }
    auto it = squares.find(static_cast<int>(normal.size()));
    if (it == squares.end()) {
        return -1;
    }
    if (isSquarePalindrome(normal, it->second)) {
        return (it->second);
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Cache squares up to 10,000
    int i{0};
    while (i * i <= 10000) {
        squares[i*i] = i;
        i++;
    }

    int testCases{0};
    cin >> testCases;
    string line;
    getline(cin, line);  // Read trailing newline.
    for (int testCase{1}; testCase <= testCases; ++testCase) {
        getline(cin, line);
        vector<char> normal = normalize(line);
        int result = solve(normal);
        cout << "Case #" << testCase << ":" << endl;
        if (result < 0) {
            cout << "No magic :(" << endl;
        } else {
            cout << result << endl;
        }
    }
    return EXIT_SUCCESS;
}
