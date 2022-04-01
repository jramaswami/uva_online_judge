// UVA :: 11402 :: Ahoy, Pirates!
// https://onlinejudge.org/external/114/11402.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = unsigned long long int;

const int SET{1};
const int CLEAR{2};
const int FLIP{3};

struct SegmentTree {
    size_t N{0};
    vector<number_t> tree;
    vector<vector<int>> lazy;

    SegmentTree(const vector<number_t> &A) {
        N = A.size();
        tree.resize(4 * N);
        lazy.resize(4 * N);
        fill(lazy.begin(), lazy.end(), vector<int>());
        build(1, 0, N-1, A);
    }

    void build(size_t v, size_t sl, size_t sr, const vector<number_t> &A) {
        // Leaf Node
        if (sl == sr) {
            tree[v] = A[sl];
            return;
        }

        // Not a leaf node.
        size_t lc{v * 2};
        size_t rc{lc + 1};
        size_t sm{sl + ((sr - sl) / 2)};
        build(lc, sl, sm, A);
        build(rc, sm+1, sr, A);
        tree[v] = tree[lc] + tree[rc];
        assert(tree[v] <= (sr - sl) + 1);
    }

    void apply(size_t v, size_t sl, size_t sr) {
        if (lazy[v].empty()) {
            return;
        }

        // Push changes down.
        if (sl != sr) {
            size_t lc{v * 2};
            size_t rc{lc + 1};
            copy(lazy[v].begin(), lazy[v].end(), back_inserter(lazy[lc]));
            copy(lazy[v].begin(), lazy[v].end(), back_inserter(lazy[rc]));
        }

        // Apply changes to current node.
        for (auto change : lazy[v]) {
            switch(change) {
                case SET:
                    set(v, sl, sr);
                    break;
                case CLEAR:
                    clear(v, sl, sr);
                    break;
                case FLIP:
                    flip(v, sl, sr);
                    break;
            }
        }

        // Clear lazy changes.
        lazy[v].clear();
    }

    void flip(size_t v, size_t sl, size_t sr) {
        tree[v] = (sr - sl + 1) - tree[v];
    }

    void set(size_t v, size_t sl, size_t sr) {
        tree[v] = (sr - sl + 1);
    }

    void clear(size_t v, size_t sl, size_t sr) {
        tree[v] = 0;
    }

    size_t query(size_t v, size_t sl, size_t sr, size_t ql, size_t qr) {
        apply(v, sl, sr);

        // Disjoint.
        if (sr < ql || qr < sl) {
            return 0;
        }

        // Covered.
        if (ql <= sl && sr <= qr) {
            return tree[v];
        }

        // Do not know.
        size_t lc{v * 2};
        size_t rc{lc + 1};
        size_t sm{sl + ((sr - sl) / 2)};
        return query(lc, sl, sm, ql, qr) + query(rc, sm+1, sr, ql, qr);
    }

    void update(size_t v, size_t sl, size_t sr, size_t ql, size_t qr, int change) {
        apply(v, sl, sr);

        // Disjoint
        if (sr < ql || qr < sl) {
            return;
        }


        size_t lc{v * 2};
        size_t rc{lc + 1};

        // Covered
        if (ql <= sl && sr <= qr) {
            switch(change) {
                case SET:
                    set(v, sl, sr);
                    break;
                case CLEAR:
                    clear(v, sl, sr);
                    break;
                case FLIP:
                    flip(v, sl, sr);
                    break;
            }
            if (sl != sr) {
                lazy[lc].push_back(change);
                lazy[rc].push_back(change);
            }
            return;
        }

        // Mixed.
        size_t sm{sl + ((sr - sl) / 2)};
        update(lc, sl, sm, ql, qr, change);
        update(rc, sm+1, sr, ql, qr, change);
        tree[v] = tree[lc] + tree[rc];
        assert(tree[v] <= (sr - sl + 1));
    }

    size_t query(size_t ql, size_t qr) {
        return query(1, 0, N-1, ql, qr);
    }

    void update(size_t ql, size_t qr, int change) {
        update(1, 0, N-1, ql, qr, change);
    }

};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    size_t testCases{0};
    cin >> testCases;
    string line;
    for (size_t t{1}; t <= testCases; ++t) {
        cout << "Case " << t << ":" << endl;
        vector<number_t> pirates;
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
                        pirates.push_back(1);
                    } else {
                        pirates.push_back(0);
                    }
                }
            }
        }
        // Construct segment tree.
        SegmentTree st(pirates);

        // Read queries.
        size_t Q{0};
        cin >> Q;
        getline(cin, line);  // Read trailing newline.
        size_t qId{1};
        for (size_t q{1}; q <= Q; ++q) {
            getline(cin, line);
            auto firstSpace = find(line.begin(), line.end(), ' ');
            auto secondSpace = find(firstSpace+1, line.end(), ' ');
            char queryType = line.at(0);
            size_t qryLeft = static_cast<size_t>(stoi(string(firstSpace+1, secondSpace)));
            size_t qryRight = static_cast<size_t>(stoi(string(secondSpace+1, line.end())));
            switch (queryType) {
                case 'F':
                    // Mutate [qryLeft, qryRight] to BUCANEER.
                    st.update(qryLeft, qryRight, SET);
                    break;

                case 'E':
                    // Mutate [qryLeft, qryRight] to BARBARY.
                    st.update(qryLeft, qryRight, CLEAR);
                    break;

                case 'I':
                    // Mutate [qryLeft, qryRight] to INVERSE.
                    st.update(qryLeft, qryRight, FLIP);
                    break;

                case 'S':
                    // How many BUCANEERs in [qryLeft, qryRight].
                    auto result = st.query(qryLeft, qryRight);
                    cout << "Q" << qId << ": " << result << endl;
                    qId++;
                    break;
            }
        }
    }
    return EXIT_SUCCESS;
}
