// UVA :: 12532 :: Interval Product
// https://onlinejudge.org/external/125/12532.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const int MAXN{131072};
vector<int> tree(2 * (MAXN+5), 0);

int nextPowOf2(int n) {
    int p{1};
    while (p < n) {
        p <<= 1;
    }
    return p;
}

int signum(int x) {
    if (x < 0) {
        return -1;
    } else if (x > 0) {
        return 1;
    }
    return 0;
}

char label(int x) {
    if (x < 0) {
        return '-';
    } else if (x > 0) {
        return '+';
    }
    return '0';
}

void update(int v, int tl, int tr, int p, int x) {
    // Disjoint
    if (p < tl || tr < p) {
        return;
    }

    // Point.
    if (tl == p && tl == tr) {
        tree[v] = x;
        return;
    }

    int tm = tl + ((tr - tl) / 2);
    update(v*2, tl, tm, p, x);
    update(v*2+1, tm+1, tr, p, x);
    tree[v] = tree[v*2] * tree[v*2+1];
}

int query(int v, int tl, int tr, int ql, int qr) {
    // Disjoint
    if (qr < tl || tr < ql) {
        return 1;
    }

    // Covered.
    if (ql <= tl && tr <= qr) {
        return tree[v];
    }

    int tm = tl + ((tr - tl) / 2);
    return query(v*2, tl, tm, ql, qr) * query(v*2+1, tm+1, tr, ql, qr);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0}, K{0};
    while (cin >> N >> K) {
        // Compute size of tree.
        int M = nextPowOf2(N);
        // Read array directly into leaf nodes.
        for (int i = 0; i < M; ++i) {
            int x = 1;
            if (i < N) {
                cin >> x;
                x = signum(x);
            }
            tree[i+M] = x;
        }
        // Build tree.
        for (int i = M - 1; i >= 1; --i) {
            tree[i] = tree[i*2] * tree[i*2+1];
        }

        // Read queries.
        string line;
        getline(cin, line);  // Read trailing newline.
        for (int q = 0; q < K; ++q) {
            getline(cin, line);
            auto s1 = find(line.begin(), line.end(), ' ');
            auto s2 = find(s1+1, line.end(), ' ');
            char cmd = line.at(0);
            int a = stoi(string(s1+1, s2));
            int b = stoi(string(s2+1, line.end()));
            switch (cmd) {
                case 'C':
                    // Change command.
                    update(1, 0, M-1, --a, signum(b));
                    break;
                case 'P':
                    // Product command.
                    auto result = query(1, 0, M-1, --a, --b);
                    cout << label(result);
                    break;
            }
        }
        cout << endl;
    }
    return EXIT_SUCCESS;
}
