// UVA :: 11988 :: Broken Keyboard (a.k.a. Beiju Text)
// https://onlinejudge.org/external/119/11988.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    string line;
    while(getline(cin, line)) {
        deque<vector<char>> soln;
        soln.push_back(vector<char>());
        size_t i{0};
        for (auto c : line) {
            if (c == '[') {
                soln.push_front(vector<char>());
                i = 0;
            } else if (c == ']') {
                soln.push_back(vector<char>());
                i = soln.size() - 1;
            } else {
                soln[i].push_back(c);
            }
        }
        for (auto curr0 : soln) {
            for (auto c : curr0) {
                cout << c;
            }
        }
        cout << endl;
    }
    return EXIT_SUCCESS;
}
