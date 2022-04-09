// UVA :: 735 :: Dart-a-Mania
// https://onlinejudge.org/external/7/735.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const vector<int> possibles{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 24, 26, 27, 28, 30, 32, 33, 34, 36, 38, 39, 40, 42, 45, 48, 50,
    51, 54, 57, 60
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int score{0};
    cin >> score;
    while (score > 0) {
        int combos{0}, perms{0};
        for (size_t i{0}; i < possibles.size(); ++i) {
            for (size_t j{i}; j < possibles.size(); ++j) {
                for (size_t k{j}; k < possibles.size(); ++k) {
                    int a{possibles[i]}, b{possibles[j]}, c{possibles[k]};
                    if (a + b + c == score) {
                        // a <= b <= c
                        if (a == b && b == c) {
                            // There is only one permutation.
                            combos += 1;
                            perms += 1;
                        } else if ((a == b) || (b == c)) {
                            // There are 3 permutations:
                            // a, a, c; a, c, a; c, a, a;
                            combos += 1;
                            perms += 3;
                        } else {
                            // a != b != c
                            // There are 6 permutations. 3 * 2 * 1.
                            combos += 1;
                            perms += 6;
                        }
                    }
                }
            }
        }
        if (combos) {
            cout << "NUMBER OF COMBINATIONS THAT SCORES " << score << " IS " << combos << "." << endl;
            cout << "NUMBER OF PERMUTATIONS THAT SCORES " << score << " IS " << perms << "." << endl;
        } else {
            cout << "THE SCORE OF " << score << " CANNOT BE MADE WITH THREE DARTS." << endl;
        }
        cout << "**********************************************************************" << endl;
        cin >> score;
    }
    cout << "END OF OUTPUT" << endl;
    return EXIT_SUCCESS;
}
