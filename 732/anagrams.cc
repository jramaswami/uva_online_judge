// UVA :: 732 :: Anagrams by Stack
// https://onlinejudge.org/external/7/732.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

void solve(size_t t, size_t s, const string &source, const string &target, string &stack, string &acc, vector<string> &solns) {
    // Base case: we have reached the end of the target string.
    // This means we have constructed the target string and have a solution.
    if (t >= target.size()) {
        string result(acc);
        solns.push_back(result);
        return;
    }

    // Can we pop from stack to reconstruct target?
    if (target[t] == stack.back()) {
        char c = stack.back();
        acc.push_back('o');
        stack.pop_back();
        solve(t + 1, s, source, target, stack, acc, solns);
        // Undo what we did.
        acc.pop_back();
        stack.push_back(c);
    }

    // Can we push from source onto stack?
    if (s < source.size()) {
        acc.push_back('i');
        stack.push_back(source[s]);
        solve(t, s + 1, source, target, stack, acc, solns);
        // Undo what we did.
        stack.pop_back();
        acc.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    string source, target, acc;
    while (1) {
        // Read the source string.  There may be blank lines.
        bool done{false};
        getline(cin, source);
        while (source.empty()) {
            if (cin.eof()) {
                done = true;
                break;
            }
            getline(cin, source);
        }

        if (done) {
            break;
        }

        // Read the target string.  There may be blank lines.
        getline(cin, target);
        while (target.empty()) {
            getline(cin, target);
        }

        vector<string> solns;
        string stack;
        string acc;
        solve(0, 0, source, target, stack, acc, solns);
        sort(solns.begin(), solns.end());
        cout << "[" << endl;
        for (auto soln : solns) {
            for (size_t i{0}; i < soln.size(); ++i) {
                cout << soln[i];
                if (i < soln.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }
        cout << "]" << endl;
    }
    return EXIT_SUCCESS;
}
