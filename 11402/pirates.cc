// UVA :: 11402 :: Ahoy, Pirates!
// https://onlinejudge.org/external/114/11402.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = unsigned long long int;

const int OK{0};
const int SET{1};
const int CLEAR{2};
const int FLIP{3};
const size_t MAXN{1050000};

vector<number_t> tree(2*(MAXN+1), 0);
vector<int> lazy(2*(MAXN+1), 0);

// Return the next largest power of two.
size_t nextPowOf2(size_t n) {
    size_t p{1};
    while (p < n) {
        p <<= 1;
    }
    return p;
}

// Build tree.  Assumes that array values have been copied to bottom of tree.
void buildTree(const vector<number_t> &A, size_t N) {
    // Calculate padding.
    // Clear any previous values in upper nodes.
    fill(tree.begin(), tree.begin() + N, 0);
    fill(lazy.begin(), lazy.begin() + N, 0);
    // Copy leaf nodes.
    copy(A.begin(), A.end(), tree.begin() + N);
    // Populate upper nodes.
    for (size_t v{N-1}; v >= 1; v--) {
        tree[v] = tree[2*v] + tree[2*v+1];
    }
}

// Apply given operation to node.
void apply(size_t v, size_t sl, size_t sr, int op) {
    switch(op) {
        case SET:
            tree[v] = sr - sl + 1;
            break;
        case CLEAR:
            tree[v] = 0;
            break;
        case FLIP:
            tree[v] = (sr - sl + 1) - tree[v];
            break;
    }
    lazy[v] = op;
}

// Propogate an operation down until it reaches a node that has no pending
// operations.
void propagate(size_t v, size_t sl, size_t sr) {
    if (sl == sr) {
        return;
    }
    size_t sm = sl + ((sr - sl) / 2);
    if (lazy[v] != OK) {
        propagate(v*2, sl, sm);
        propagate(v*2+1, sm+1, sr);
        apply(v*2, sl, sm, lazy[v]);
        apply(v*2+1, sm+1, sr, lazy[v]);

    }
    lazy[v] = OK;
}


void update(size_t v, size_t sl, size_t sr, size_t ql, size_t qr, int op) {
    if (sr < ql || qr < sl) {
        return;
    }

    propagate(v, sl, sr);

    if (ql <= sl && sr <= qr) {
        apply(v, sl, sr, op);
        return;
    }

    size_t sm = sl + ((sr - sl) / 2);
    update(2*v, sl, sm, ql, qr, op);
    update(2*v+1, sm+1, sr, ql, qr, op);
    tree[v] = tree[2*v] + tree[2*v+1];
}

number_t query(size_t v, size_t sl, size_t sr, size_t ql, size_t qr) {
    if (sr < ql || qr < sl) {
        return 0;
    }

    propagate(v, sl, sr);
    if (ql <= sl && sr <= qr) {
        return tree[v];
    }

    size_t sm = sl + ((sr - sl) / 2);
    return query(2*v, sl, sm, ql, qr) + query(2*v+1, sm+1, sr, ql, qr);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    size_t testCases{0};
    cin >> testCases;
    string line;
    for (size_t t{1}; t <= testCases; ++t) {
        cout << "Case " << t << ":" << endl;
        vector<number_t> A;
        size_t M{0};
        cin >> M;
        for (size_t m{0}; m < M; ++m) {
            size_t T{0};
            cin >> T;
            getline(cin, line);  // Read trailing newline.
            getline(cin, line);  // Read pirate segment.
            // Repeat pirate spec T times.
            for (size_t i{0}; i < T; ++i) {
                for (size_t j{0}; j < line.size(); ++j) {
                    if (line.at(j) == '1') {
                        A.push_back(1);
                    } else {
                        A.push_back(0);
                    }
                }
            }
        }

        // Compute padding.
        size_t N = nextPowOf2(A.size());
        // Construct segment tree.
        buildTree(A, N);

        // Read queries.
        size_t Q{0};
        cin >> Q;
        getline(cin, line);  // Read trailing newline.
        size_t qId{1};
        for (size_t q{1}; q <= Q; ++q) {
            getline(cin, line);
            auto s1 = find(line.begin(), line.end(), ' ');
            auto s2 = find(s1+1, line.end(), ' ');
            char cmd = line.at(0);
            size_t ql = static_cast<size_t>(stoi(string(s1+1, s2)));
            size_t qr = static_cast<size_t>(stoi(string(s2+1, line.end())));
            switch (cmd) {
                case 'F':
                    // Mutate [ql, qr] to BUCANEER.
                    update(1, 0, N-1, ql, qr, SET);
                    break;

                case 'E':
                    // Mutate [ql, qr] to BARBARY.
                    update(1, 0, N-1, ql, qr, CLEAR);
                    break;

                case 'I':
                    // Mutate [ql, qr] to INVERSE.
                    update(1, 0, N-1, ql, qr, FLIP);
                    break;

                case 'S':
                    // How many BUCANEERs in [ql, qr].
                    auto result = query(1, 0, N-1, ql, qr);
                    cout << "Q" << qId << ": " << result << endl;
                    qId++;
                    break;
            }
        }
    }
    return EXIT_SUCCESS;
}
