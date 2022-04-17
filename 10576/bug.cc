// UVA :: 10576 :: Y2K Accounting Bug
// https://onlinejudge.org/external/105/10576.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const int LIMIT{1 << 13};
const int MONTHS{1 << 13};

struct Solver {
    int surplus{0}, deficit{0}, soln{INT_MIN};
    vector<int> prefix;
    vector<int> journal;

    Solver(int s, int d): surplus{s}, deficit{d} {
        journal = vector<int>(13, 0);
        prefix = vector<int>(13, 0);
    }

    int windowSum(int left, int right) {
        return prefix[right] - prefix[left-1];
    }

    void solve(int m) {
        /*
        cerr << "solve(" << m << ") " << endl;
        copy(journal.begin(), journal.end(), ostream_iterator<int>(cerr, " ")); cerr << endl;
        copy(prefix.begin(), prefix.end(), ostream_iterator<int>(cerr, " ")); cerr << endl;
        */

        if (m == 13) {
            // Base Case.
            soln = max(soln, prefix.back());
        } else {
            prefix[m] = prefix[m-1] + surplus;
            journal[m] = surplus;
            if (m < 5 || windowSum(m-4, m) < 0) {
                solve(m+1);
            }
            prefix[m] = prefix[m-1] - deficit;
            journal[m] = -deficit;
            if (m < 5 || windowSum(m-4, m) < 0) {
                solve(m+1);
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int surplus{0}, deficit{0};
    while (cin >> surplus) {
        cin >> deficit;
        Solver solver(surplus, deficit);
        solver.solve(1);
        if (solver.soln > 0) {
            cout << solver.soln << endl;
        } else {
            cout << "Deficit" << endl;
        }
    }
    return EXIT_SUCCESS;
}
