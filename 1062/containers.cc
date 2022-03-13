// UVA :: 1062 :: Containers
// https://onlinejudge.org/external/10/1062.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    string containers;
    getline(cin, containers);
    /* cerr << "Containers: " << containers << endl; */
    int caseNumber{1};
    while (containers != "end") {
        bitset<26> uniqueContainers;
        vector<vector<char>> stacks;
        for (char container : containers) {
            uniqueContainers.set(container - 'A');
            // Find the best stack.
            size_t bestStack{stacks.size()};
            char bestDelta{CHAR_MAX};
            for (size_t i{0}; i < stacks.size(); ++i) {
                if (stacks[i].back() >= container) {
                    if (stacks[i].back() - container < bestDelta) {
                        bestDelta = stacks[i].back() - container;
                        bestStack = i;
                    }
                }
            }
            if (bestStack == stacks.size()) {
                stacks.push_back(vector<char>());
            }
            stacks[bestStack].push_back(container);
        }
        /*
        cerr << "Stacks:" << endl;
        for (auto stack : stacks) {
            copy(stack.begin(), stack.end(), ostream_iterator<char>(cerr, ""));
            cerr << endl;
        }
        */
        cout << "Case " << caseNumber << ": " << min(uniqueContainers.count(), stacks.size()) << endl;
        caseNumber++;
        getline(cin, containers);
    }
    return EXIT_SUCCESS;
}
