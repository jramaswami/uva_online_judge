// UVA :: 10503 :: The dominoes solitaire
// https://onlinejudge.org/external/105/10503.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Domino {
    int left{0}, right{0};

    void flip() {
        swap(left,right);
    }

    bool connects(Domino &other) {
        if (other.right == left) {
            return true;
        }
        return false;
    }
};

ostream& operator<<(ostream &os, const Domino &d) {
    os << "(" << d.left << "|" << d.right << ")";
    return os;
}

struct Solver {
    int numberOfSpaces{0}, numberOfDominoes{0};
    vector<Domino> fillerDominoes;
    vector<int> visited;
    vector<Domino> acc;
    Domino leftmost, rightmost;

    Solver(int nos, int nod) {
        numberOfSpaces = nos;
        numberOfDominoes = nod;
        fillerDominoes = vector<Domino>(nod);
        visited = vector<int>(nod, -1);
    }

    bool solve() {
        acc.push_back(leftmost);
        return solve(0);
    }

    bool solve(int index) {
        if (index >= numberOfSpaces) {
            if (rightmost.connects(acc.back())) {
                return true;
            }
            return false;
        }

        for (int i{0}; i < numberOfDominoes; ++i) {
            if (visited[i] < 0) {
                Domino d = fillerDominoes[i];
                if (d.connects(acc.back())) {
                    visited[i] = index;
                    acc.push_back(d);
                    if (solve(index + 1)) {
                        return true;
                    }
                    acc.pop_back();
                    visited[i] = -1;
                }
                d.flip();
                if (d.connects(acc.back())) {
                    visited[i] = index;
                    acc.push_back(d);
                    if (solve(index + 1)) {
                        return true;
                    }
                    acc.pop_back();
                    visited[i] = -1;
                }
            }
        }
        return false;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int numberOfSpaces{0}, numberOfDominoes{0};
    cin >> numberOfSpaces;
    while (numberOfSpaces) {
        cin >> numberOfDominoes;
        Solver solver(numberOfSpaces, numberOfDominoes);
        cin >> solver.leftmost.left >> solver.leftmost.right;
        cin >> solver.rightmost.left >> solver.rightmost.right;
        for (int i{0}; i < numberOfDominoes; ++i) {
            cin >> solver.fillerDominoes[i].left;
            cin >> solver.fillerDominoes[i].right;
        }
        if (solver.solve()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
        cin >>numberOfSpaces;
    }

    return EXIT_SUCCESS;
}
