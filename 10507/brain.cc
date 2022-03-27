// UVA :: 10507 :: Waking up brain
// https://onlinejudge.org/external/105/10507.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int labelToIndex(char label) {
    return static_cast<int>(label - 'A');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    size_t sleepingAreas{0}, edgeCount{0};
    while (cin >> sleepingAreas >> edgeCount) {
        string line;
        getline(cin, line);   // Read trailing newline.
        bitset<26> brainAreas;
        vector<vector<int>> graph(26, vector<int>());
        bitset<26> prevAwake;
        bitset<26> nextAwake;
        // Read stimulated areas.
        getline(cin, line);
        for (size_t i{0}; i < 3; ++i) {
            int u{labelToIndex(line.at(i))};
            brainAreas.set(u);
            prevAwake.set(u);
        }
        // Read edges.
        for (size_t i{0}; i < edgeCount; ++i) {
            getline(cin, line);
            int u{labelToIndex(line.at(0))}, v{labelToIndex(line.at(1))};
            graph[u].push_back(v);
            graph[v].push_back(u);
            brainAreas.set(u);
            brainAreas.set(v);
        }
        int distance{0};
        while (prevAwake != nextAwake) {
            distance++;
            nextAwake |= prevAwake;
            for (size_t node{0}; node < 26; node++) {
                if (brainAreas.test(node)) {
                    int awakeNeighbors{0};
                    for (auto neighbor : graph[node]) {
                        if (prevAwake.test(neighbor)) {
                            awakeNeighbors++;
                        }
                    }
                    if (awakeNeighbors >= 3) {
                        nextAwake.set(node);
                    }
                }
            }
            swap(prevAwake, nextAwake);
        }
        if (brainAreas.count() == sleepingAreas && prevAwake == brainAreas) {
            // Subtract a year for the year where there was no change.
            cout << "WAKE UP IN, " << (distance - 1) << ", YEARS" << endl;
        } else {
            cout << "THIS BRAIN NEVER WAKES UP" << endl;
        }
        // Read trailing newline.
        getline(cin, line);
    }
    return EXIT_SUCCESS;
}
