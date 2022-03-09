// UVA :: 146 :: ID Codes
// https://onlinejudge.org/external/1/146.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    string line;
    getline(cin, line);
    while (line != "#") {
        if (next_permutation(line.begin(), line.end())) {
            cout << line << endl;
        } else {
            cout << "No Successor" << endl;
        }
        getline(cin, line);
    }

    return EXIT_SUCCESS;
}
