// UVA :: 486 :: Hangman Judge
// https://onlinejudge.org/external/4/489.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCase{0};
    string junk, solution, guesses;
    cin >> testCase;
    while (testCase != -1) {
        getline(cin, junk); // Read trailing newline.
        getline(cin, solution);
        getline(cin, guesses);

        bitset<26> solutionLetters;
        for (char c : solution) {
            solutionLetters.set(c - 'a');
        }

        bitset<26> wrongGuesses;
        bitset<26> correctGuesses;
        for (char c : guesses) {
            if (solutionLetters.test(c - 'a')) {
                correctGuesses.set(c - 'a');
            } else {
                wrongGuesses.set(c - 'a');
            }
            if (wrongGuesses.count() >= 7) {
                break;
            }
            if (solutionLetters == correctGuesses) {
                break;
            }
        }

        cout << "Round " << testCase << endl;
        if (wrongGuesses.count() >= 7) {
            cout << "You lose." << endl;
        } else if (solutionLetters == correctGuesses) {
            cout << "You win." << endl;
        } else {
            cout << "You chickened out." << endl;
        }
        cin >> testCase;
    }
    return EXIT_SUCCESS;
}
