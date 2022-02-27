// UVA :: 278 :: Chess
// https://onlinejudge.org/external/2/278.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    int testCases{0}, filled{0};
    filled = scanf("%d\n", &testCases);
    assert(filled == 1);
    while (testCases) {
        char piece{'z'};
        int rows{0}, cols{0};
        filled = scanf("%c %d %d\n", &piece, &rows, &cols);
        assert(filled == 3);

        int soln{0};
        switch (piece) {
            case 'k': {
                    int squares{rows * cols};
                    soln = (squares / 2) + (squares % 2);
                }
                break;
            case 'r':
                soln = min(rows, cols);
                break;
            case 'Q':
                soln = min(rows, cols);
                break;
            case 'K':
                soln = ((rows / 2) + (rows % 2)) * ((cols / 2) + (cols % 2));
                break;
        }
        cout << soln << endl;
        testCases--;
    }

    return EXIT_SUCCESS;
}
