// UVA :: 12085 :: Mobile Casanova
// https://onlinejudge.org/external/120/12085.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

vector<int> reversedDigits(int n) {
    vector<int> result;
    while (n) {
        result.push_back(n % 10);
        n /= 10;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int numberCount;
    cin >> numberCount;
    int caseNumber = 1;
    while (numberCount) {
        vector<pair<int, int>> intervals;
        int lastInterval = -1;

        for (int i = 0; i < numberCount; i++) {
            int phoneNumber;
            cin >> phoneNumber;

            if (lastInterval < 0 || intervals[lastInterval].second + 1 != phoneNumber) {
                intervals.emplace_back(phoneNumber, phoneNumber);
                lastInterval++;
            } else {
                intervals[lastInterval].second = phoneNumber;
            }
        }

        if (caseNumber > 1) {
            cout << endl;
        }
        cout << "Case " << caseNumber << ":" << endl;
        for (size_t i = 0; i < intervals.size(); i++) {
            cout << "0" << intervals[i].first;
            if (intervals[i].first != intervals[i].second) {
                // Compute the differences between the two numbers.
                auto left = reversedDigits(intervals[i].first);
                auto right = reversedDigits(intervals[i].second);
                cout << "-";
                bool shouldPrint = false;
                for (int i = static_cast<int>(right.size()) - 1; i >= 0; i--) {
                    if (left[i] != right[i]) {
                        shouldPrint = true;
                    }
                    if (shouldPrint) {
                        cout << right[i];
                    }
                }
            }
            cout << endl;
        }
        cin >> numberCount;
        caseNumber++;
    }
    return EXIT_SUCCESS;

}
