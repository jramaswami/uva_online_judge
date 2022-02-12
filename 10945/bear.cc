// UVA :: 10945 :: Mother Bear
// https://onlinejudge.org/external/109/10945.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

bool isPalindrome(const string &line) {
    if (line.size() > 1) {
        size_t left{0};
        size_t right{line.size() - 1};
        while (left <= right) {
            if (!isalpha(line[left])) {
                left++;
            } else if (!isalpha(line[right])) {
                right--;
            } else {
                if (tolower(line[left]) != tolower(line[right])) {
                    return false;
                }
                left++; right--;
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    while (line != "DONE") {
        if (isPalindrome(line)) {
            cout << "You won't be eaten!" << endl;
        } else {
            cout << "Uh oh.." << endl;
        }
        getline(cin, line);
    }
    return EXIT_SUCCESS;
}
