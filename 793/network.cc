// UVA :: 793 Network Connections
// https://onlinejudge.org/external/7/793.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

class UnionFind {
    vector<int> id;
    vector<size_t> size;

public:

    UnionFind(int N) {
        id = vector<int>(N+1);
        iota(id.begin(), id.end(), 0);
        size = vector<size_t>(N+1, 1);
    }

    int find(int u) {
        if (id[u] != u) {
            id[u] = find(id[u]);
        }
        return id[u];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b]) {
                swap(a, b);
            }
            id[b] = a;
            size[a] += b;
        }
    }

    bool areConnected(int a, int b) {
        return find(a) == find(b);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    string line;
    while (testCases) {
        int nodeCount{0};
        cin >> nodeCount;
        UnionFind uf(nodeCount);
        getline(cin, line);  // Read trailing newline.
        // Read queries.
        getline(cin, line);
        int successful{0}, unsuccesful{0};
        while(!line.empty()) {
            char command{line[0]};
            int u{0}, v{0};
            auto firstSpace = find(line.begin(), line.end(), ' ');
            auto secondSpace = find(firstSpace + 1, line.end(), ' ');
            u = stoi(string(firstSpace+1, secondSpace));
            v = stoi(string(secondSpace+1, line.end()));
            if (command == 'c') {
                // union
                uf.unite(u, v);
            } else {
                // connected?
                if (uf.areConnected(u, v)) {
                    successful++;
                } else {
                    unsuccesful++;
                }
            }
            getline(cin, line);
        }
        cout << successful << "," << unsuccesful << endl;
        testCases--;
        if (testCases) {
            cout << endl;
        }
    }

    return EXIT_SUCCESS;
}
