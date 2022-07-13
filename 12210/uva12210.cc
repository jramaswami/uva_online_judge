// UVA :: 12210 :: A Match Making Problem
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int B{0}, S{0}, caseNo{1};
    cin >> B >> S;
    while (B || S) {
        vector<int> batchelors;
        batchelors.reserve(B);
        copy_n(istream_iterator<int>(cin), B, back_inserter(batchelors));
        vector<int> spinsters;
        spinsters.reserve(S);
        copy_n(istream_iterator<int>(cin), S, back_inserter(spinsters));
        if ( S >= B) {
            // If there are enough spinsters, then all batchelor gets married!
            cout << "Case " << caseNo << ": 0\n";
        } else {
            // If there aren't enough spinsters, then (B - S) batchelors don't
            // get married, including the youngest batchelor.
            cout << "Case " << caseNo << ": " << (B - S) << " "
                 << (*min_element(batchelors.begin(), batchelors.end()))
                 << "\n";
        }
        caseNo++;
        cin >> B >> S;
    }
    return EXIT_SUCCESS;
}
