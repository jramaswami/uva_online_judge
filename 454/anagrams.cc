// UVA :: 454 :: Anagrams
// https://onlinejudge.org/external/4/454.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

string normalize(const string &word) {
    string normal;
    normal.reserve(word.size());
    copy_if(word.begin(), word.end(), back_inserter(normal), [](char c) {return !isspace(c);});
    sort(normal.begin(), normal.end());
    return normal;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int T{0};
    cin >> T;
    string line;
    getline(cin, line);  // Read trailing newline.
    getline(cin, line);  // Read the blank line.
    while (T) {
        string word;
        vector<string> words;
        while (getline(cin, word) && word != "") {
            words.push_back(word);
        }
        sort(words.begin(), words.end());
        vector<string> keys;
        keys.reserve(words.size());
        transform(words.begin(), words.end(), back_inserter(keys), normalize);
        for (size_t i{0}; i < words.size(); ++i) {
            for (size_t j{i+1}; j < words.size(); ++j) {
                if (keys[i] == keys[j]) {
                    cout << words[i] << " = " << words[j] << endl;
                }
            }
        }
        T--;
        if (T) {
            cout << endl;   // Blank line between testcases
        }
    }

    return EXIT_SUCCESS;
}
