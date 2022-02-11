// UVA :: 401 :: Palindromes
// https://onlinejudge.org/external/4/401.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const map<char, char> mirrors = {
    {'A', 'A'}, {'E', '3'}, {'H', 'H'}, {'I', 'I'}, {'J', 'L'}, {'M', 'M'},
    {'O', 'O'}, {'S', '2'}, {'T', 'T'}, {'U', 'U'}, {'V', 'V'}, {'W', 'W'},
    {'X', 'X'}, {'Y', 'Y'}, {'1', '1'}, {'2', 'S'}, {'3', 'E'}, {'5', 'Z'},
    {'8', '8'}
};

const vector<string> result = {
    " -- is not a palindrome.",
    " -- is a regular palindrome.",
    " -- is a mirrored string.",
    " -- is a mirrored palindrome."
};

bool isPalindrome(const string &line) {
    int left = 0;
    int right = static_cast<int>(line.size()) - 1;
    while (left <= right) {
        if (line[left] != line[right]) {
            return false;
        }
        left++; right--;
    }
    return true;
}

bool isMirror(const string &line) {
    int left = 0;
    int right = static_cast<int>(line.size()) - 1;
    while (left <= right) {
        auto it = mirrors.find(line[left]);
        if (it == mirrors.end() || it->second != line[right]) {
            return false;
        }
        left++; right--;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while(getline(cin, line)) {
        int m{0};
        if (isPalindrome(line)) {
            m |= 1;
        }
        if (isMirror(line)) {
            m |= 2;
        }
        cout << line << result[m] << endl << endl;
    }
    return EXIT_SUCCESS;
}
