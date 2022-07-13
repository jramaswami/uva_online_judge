// UVA :: 12405 :: Scarecrow
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0}, N{0};
    cin >> testCases;
    string junk, field;
    for (int caseNo{1}; caseNo <= testCases; caseNo++) {
        cin >> N;
        // read trailing newline
        getline(cin, junk);
        // read field
        getline(cin, field);
        int i{1}, scarecrows{0};
        while (i < N) {
            while (i < N && field[i-1] == '#') {
                i++;
            }
            if (i < N) {
                // Plant scarecrow at i.
                scarecrows++;
                i += 3;
            }
        }
        // Check to make sure that we weren't relying on the last scarecrow
        // to cover the end of the field.
        if (i == N && field[N-1] == '.') {
            scarecrows++;
        }
        cout << "Case " << caseNo << ": " << scarecrows << "\n";
    }
    return EXIT_SUCCESS;
}
