// UVA :: 11034 :: Ferry Loading IV
// https://onlinejudge.org/external/110/11034.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while (testCases) {
        string line;
        int ferryLength, carCount;
        cin >> ferryLength >> carCount;
        getline(cin, line);  // Read trailing newline.
        vector<int> leftSide;
        vector<int> rightSide;
        for (int c{0}; c < carCount; ++c) {
            getline(cin, line);
            auto it = find(line.begin(), line.end(), ' ');
            int carLength = stoi(line.substr(0, distance(line.begin(), it)));
            string side = string(it+1, line.end());
            if (side == "left") {
                leftSide.push_back(carLength);
            } else {
                rightSide.push_back(carLength);
            }
        }
        bool onLeft{true};
        size_t leftIndex{0};
        size_t rightIndex{0};
        int trips{0};
        while (leftIndex < leftSide.size() || rightIndex < rightSide.size()) {
            int remainingCapacity{ferryLength * 100};   // Convert ferrylength from m to cm.
            if (onLeft) {
                while (leftIndex < leftSide.size() && leftSide[leftIndex] <= remainingCapacity) {
                    remainingCapacity -= leftSide[leftIndex];
                    leftIndex++;
                }
            } else {
                while (rightIndex < rightSide.size() && rightSide[rightIndex] <= remainingCapacity) {
                    remainingCapacity -= rightSide[rightIndex];
                    rightIndex++;
                }
            }
            onLeft = !onLeft;
            trips++;
        }
        cout << trips << endl;
        --testCases;
    }

    return EXIT_SUCCESS;
}
