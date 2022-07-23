// UVA :: 10656 :: Maximum Sum (II)
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0};
    cin >> N;
    while (N) {
        vector<int> soln;
        for (int i{0}; i < N; i++) {
            int x{0};
            cin >> x;
            if (x > 0) {
                soln.push_back(x);
            }
        }
        if (soln.empty()) {
            cout << "0\n";
        } else {
            for (size_t i{0}; i < soln.size(); i++) {
                cout << soln[i];
                if (i < soln.size() - 1) {
                    cout << " ";
                }
            }
            cout << "\n";
        }
        cin >> N;
    }
    return EXIT_SUCCESS;
}
