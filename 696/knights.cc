// UVA :: 696 :: How Many Knights
// https://onlinejudge.org/external/6/696.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int rows{0}, cols{0};
    cin >> rows >> cols;
    while (rows || cols) {
        int soln{0};
        if (rows == 0 || cols == 0) {
            soln = 0;
        } else if (rows == 1 || cols == 1) {
            soln = max(cols, rows);
        } else if (rows == 2 || cols == 2) {
            int k{max(rows, cols)};
            soln = (k / 4) * 4;
            if (k % 4 == 1) {
                soln += 2;
            }
            if (k % 4 > 1) {
                soln += 4;
            }
        } else {
            int squares{rows * cols};
            soln = (squares / 2) + (squares % 2);
        }
        cout << soln << " knights may be placed on a " << rows << " row "
             << cols << " column board." << endl;
        cin >> rows >> cols;
    }
    return EXIT_SUCCESS;
}
