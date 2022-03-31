// UVA :: 11402 :: Ahoy, Pirates!
// https://onlinejudge.org/external/114/11402.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = unsigned long long int;


const int CLEAN{0};
const int BUCANEER{1};
const int BARBARY{2};
const int INVERSE{3};

struct SegmentTree {
    size_t N{0};
    vector<number_t> tree;
    deque<int> dirty;

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

    void invert(size_t v, size_t sl, size_t sr) {
        tree[v] = (sr - sl + 1) - tree[v];
    }

    void makeBucaneer(size_t v, size_t sl, size_t sr) {
        tree[v] = (sr - sl + 1);
    }

    void makeBarbary(size_t v, size_t sl, size_t sr) {
        tree[v] = 0;
    }

    void push(size_t v, size_t sl, size_t sr, int label) {
        if (label == BUCANEER) {
            makeBucaneer(v, sl, sr);
        } else if (label == BARBARY) {
            makeBarbary(v, sl, sr);
        } else if (label == INVERSE) {
            invert(v, sl, sr);
        }
        dirty[v] = label;
    }

    size_t query(size_t v, size_t sl, size_t sr, size_t ql, size_t qr) {
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
        // If dirty, be sure to update next level of nodes.
        if (dirty[v] != CLEAN) {
            push(lc, sl, sm, dirty[v]);
            push(rc, sm+1, sr, dirty[v]);
            dirty[v] = CLEAN;
        }
        return query(lc, sl, sm, ql, qr) + query(rc, sm+1, sr, ql, qr);
    }

    void update(size_t v, size_t sl, size_t sr, size_t ql, size_t qr, int label) {
        // Disjoint
        if (sr < ql || qr < sl) {
            return;
        }

        // Covered
        if (ql <= sl && sr <= qr) {
            // Segment is entirely covered by update.
            if (label == BUCANEER) {
                makeBucaneer(v, sl, sr);
            } else if (label == BARBARY) {
                makeBarbary(v, sl, sr);
            } else if (label == INVERSE) {
                invert(v, sl, sr);
            }
            dirty[v] = label;
            return;
        }

        // Mixed.
        size_t lc{v * 2};
        size_t rc{lc + 1};
        size_t sm{sl + ((sr - sl) / 2)};
        // If dirty, be sure to update next level of nodes.
        if (dirty[v] != CLEAN) {
            push(lc, sl, sm, dirty[v]);
            push(rc, sm+1, sr, dirty[v]);
            dirty[v] = CLEAN;
        }
        update(lc, sl, sm, ql, qr, label);
        update(rc, sm+1, sr, ql, qr, label);
        tree[v] = tree[lc] + tree[rc];
        assert(tree[v] <= (sr - sl + 1));
    }

    SegmentTree(const vector<number_t> &A) {
        N = A.size();
        tree.resize(4 * N);
        dirty.resize(4 * N);
        fill(dirty.begin(), dirty.end(), CLEAN);
        build(1, 0, N-1, A);
    }

    size_t query(size_t ql, size_t qr) {
        return query(1, 0, N-1, ql, qr);
    }

    void update(size_t ql, size_t qr, int label) {
        update(1, 0, N-1, ql, qr, label);
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
            cerr << "Query " << queryType << " [" << qryLeft << ", " << qryRight << "]" << endl;
            switch (queryType) {
                case 'F':
                    // Mutate [qryLeft, qryRight] to BUCANEER.
                    st.update(qryLeft, qryRight, BUCANEER);
                    break;

                case 'E':
                    // Mutate [qryLeft, qryRight] to BARBARY.
                    st.update(qryLeft, qryRight, BARBARY);
                    break;

                case 'I':
                    // Mutate [qryLeft, qryRight] to INVERSE.
                    st.update(qryLeft, qryRight, INVERSE);
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
