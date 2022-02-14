// UVA :: 195 :: Anagram
// https://onlinejudge.org/external/1/195.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

vector<char> order;

void generate(size_t index, vector<int> &freqs, vector<char> &anagram, vector<string> &acc, size_t N) {
    if (index >= N) {
        acc.push_back(string(anagram.begin(), anagram.end()));
        return;
    }

    for (char c : order) {
        if (freqs[c] > 0) {
            freqs[c]--;
            anagram.push_back(c);
            generate(index + 1, freqs, anagram, acc, N);
            freqs[c]++;
            anagram.pop_back();
        }
    }
}

vector<string> anagrams(const string &line) {
    vector<int> freqs(128, 0);
    for_each(line.begin(), line.end(), [&freqs](char c) { freqs[c]++; });
    vector<char> anagram;
    anagram.reserve(line.size());
    vector<string> result;
    generate(0, freqs, anagram, result, line.size());
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Create ordering
    for (char c{'A'}; c <= 'Z'; ++c) {
        order.push_back(c);
        order.push_back(c + 32);
    }

    string line;
    int testCases{0};
    cin >> testCases;
    getline(cin, line); // Read trailing newline.
    for (int t{0}; t < testCases; ++t) {
        getline(cin, line);
        vector<string> result = anagrams(line);
        copy(result.begin(), result.end(), ostream_iterator<string>(cout, "\n"));
    }
    return EXIT_SUCCESS;
}
