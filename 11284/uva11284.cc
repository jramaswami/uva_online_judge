// UVA :: 11284 :: Shopping Trip
// https://onlinejudge.org/external/112/11284.pdf
// jramaswami

// TODO: Compute shortest path all pairs.
//       Then reduce graph to only home and those stores that have discount,
//       using the distances computed between pairs.
//       Run TSP on the reduced graph.

#include <bits/stdc++.h>

using namespace std;

const double INF{INT_MAX};

struct Road {
    int u{0}, v{0}, weight{0};

    Road(int _u, int _v, double _w) {
        u = min(_u, _v);
        v = max(_u, _v);
        weight = static_cast<int>(100 * _w);
    }

    int neighbor(int x) {
        if (x == u) {
            return v;
        }
        return u;
    }
};

struct Solver {
    int storeCount{0}, roadCount{0};
    vector<vector<Road>> graph;
    vector<int> dvdSavings, costToHome;

    void readGraph(int _storeCount, int _roadCount) {
        storeCount = _storeCount;
        roadCount = _roadCount;
        graph = vector<vector<Road>>(storeCount+1, vector<Road>());

        for (int i{0}; i < roadCount; ++i) {
            int u{0}, v{0};
            double w{0.0};
            cin >> u >> v >> w;
            graph[u].emplace_back(u, v, w);
            graph[v].emplace_back(u, v, w);
        }
    }

    void readDvdSavings(int dvdCount) {
        dvdSavings = vector<int>(storeCount+1);
        for (int i{0}; i < dvdCount; ++i) {
            int t{0};
            double s{0};
            cin >> t >> s;
            dvdSavings[t] += static_cast<int>(100 * s);
        }
    }

    void computeDistanceToHome() {
        costToHome = vector<int>(storeCount + 1, INF);
        costToHome[0] = 0;
        deque<pair<int, int>> Q;
        Q.emplace_back(0, 0);
        while (!Q.empty()) {
            auto T = Q.front();
            int u = T.first;
            int d = T.second;
            Q.pop_front();
            if (costToHome[u] == d) {
                for (auto rd : graph[u]) {
                    int v{rd.neighbor(u)};
                    if (costToHome[u] + rd.weight < costToHome[v]) {
                        costToHome[v] = costToHome[u] + rd.weight;
                        Q.emplace_back(v, costToHome[v]);
                    }
                }
            }
        }
        copy(costToHome.begin(), costToHome.end(), ostream_iterator<double>(cerr, " ")); cerr << endl;
    }

    int solve() {
        // TODO: TSP problem, with return trip being distance to home.
        //       Check every length circuit.
        int soln = 0;

        return soln;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while (testCases--) {
        Solver solver;
        int storeCount{0}, roadCount{0}, dvdCount{0};
        cin >> storeCount >> roadCount;
        solver.readGraph(storeCount, roadCount);
        cin >> dvdCount;
        solver.readDvdSavings(dvdCount);
        solver.computeDistanceToHome();
    }
    return EXIT_SUCCESS;
}
