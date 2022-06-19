// UVA :: 11284 :: Shopping Trip
// https://onlinejudge.org/external/112/11284.pdf
// jramaswami

// TODO: Compute shortest path all pairs.
//       Then reduce graph to only home and those stores that have discount,
//       using the distances computed between pairs.
//       Run TSP on the reduced graph.

#include <bits/stdc++.h>

using namespace std;
const int INF{1000000000};
const double EPS{10e-9};
const bool DEBUG{false};

struct Solver {
        int storeCount{0}, roadCount{0}, dvdCount{0}, allVisited{0};
        vector<vector<int>> cost;
        vector<int> destinations;
        vector<int> discounts;
        vector<vector<int>> cache;

        void readRoadNetwork() {
            cost = vector<vector<int>>(storeCount+1, vector<int>(storeCount+1, INF));
            for (int i{0}; i < roadCount; ++i) {
                int u{0}, v{0};
                double wt0{0.0};
                cin >> u >> v >> wt0;
                int wt{static_cast<int>(100.0 * (wt0 + EPS))};
                cost[u][v] = min(wt, cost[u][v]);
                cost[v][u] = min(wt, cost[v][u]);
            }

            // Floyd-Warshall to get cost between all pairs of stores.
            for (int u{0}; u <= storeCount; u++) {
                cost[u][u] = 0;
            }

            for (int k{0}; k <= storeCount; ++k) {
                for (int i{0}; i <= storeCount; ++i) {
                    for (int j{0}; j <= storeCount; ++j) {
                        cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
                    }
                }
            }

            if (DEBUG) {
                cerr << "storeCount=" << storeCount << " roadCount=" << roadCount << endl;
                cerr << "FW" << endl;
                for (auto row : cost) {
                    copy(row.begin(), row.end(), ostream_iterator<int>(cerr, " "));
                    cerr << endl;
                }
            }
        }

        void readDvdDiscounts() {
            destinations.reserve(dvdCount+1);
            discounts.reserve(dvdCount+1);
            // Add home to destinations;
            destinations.push_back(0);
            discounts.push_back(0);
            for (int i{0}; i < dvdCount; ++i) {
                int u{0};
                double d0{0.0};
                cin >> u >> d0;
                d0 += EPS;
                d0 *= 100.0;
                int d{static_cast<int>(d0)};
                destinations.push_back(u);
                discounts.push_back(d);
            }

            if (DEBUG) {
                cerr << "destinations: ";
                copy(destinations.begin(), destinations.end(), ostream_iterator<int>(cerr, " "));
                cerr << endl;
                cerr << "discounts: ";
                copy(discounts.begin(), discounts.end(), ostream_iterator<int>(cerr, " "));
                cerr << endl;
            }
        }

        int getCost(int a, int b) {
            int u{destinations[a]}, v{destinations[b]};
            return cost[u][v];
        }

        int solve() {
            // dp[last store visited][set of visited stores] = max discount
            int allVisited{(1 << (dvdCount+1)) - 1};
            vector<vector<int>> dp(dvdCount+1, vector<int>(allVisited+1, -INF));

            // We must start at zero.
            set<int> currQ = {1};
            set<int> nextQ;
            dp[0][1] = 0;

            int soln{-INF};

            for (int length = 2; length <= dvdCount+1; ++length) {

                for (auto prevVisitedStores : currQ) {

                    for (int lastStoreIndex{0}; lastStoreIndex <= dvdCount; ++lastStoreIndex) {
                        if (prevVisitedStores > 1 && lastStoreIndex == 0) {
                            // The last store can be 0 only when the only
                            // visited store is 0 i.e. prevVisitedStores == 1
                            continue;
                        }

                        for (int nextStoreIndex{1}; nextStoreIndex <= dvdCount; ++nextStoreIndex) {
                            int mask = (1 << nextStoreIndex);
                            if ((prevVisitedStores & mask) == 0) {
                                int nextVisitedStores{prevVisitedStores | mask};
                                nextQ.insert(nextVisitedStores);
                                dp[nextStoreIndex][nextVisitedStores] = max(
                                    dp[nextStoreIndex][nextVisitedStores],
                                    dp[lastStoreIndex][prevVisitedStores] - getCost(lastStoreIndex, nextStoreIndex) + discounts[nextStoreIndex]
                                );

                                // I can finish my shopping here and just go home.
                                soln = max(soln, dp[nextStoreIndex][nextVisitedStores] - getCost(nextStoreIndex, 0));
                            }
                        }
                    }
                }
                currQ.swap(nextQ);
                nextQ.clear();
            }

            if (DEBUG) {
                for (auto row : dp) {
                    copy(row.begin(), row.end(), ostream_iterator<int>(cerr, " "));
                    cerr << endl;
                }

                cerr << soln << endl;
            }

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
        // Read road network.
        Solver solver;
        cin >> solver.storeCount >> solver.roadCount;
        solver.readRoadNetwork();
        cin >> solver.dvdCount;
        solver.readDvdDiscounts();
        int soln = solver.solve();
        if (soln > 0) {
            cout << "Daniel can save $" << fixed << setprecision(2) << (static_cast<double>(soln) / 100.0) << endl;
        } else {
            cout << "Don't leave the house\n";
        }

    }
    return EXIT_SUCCESS;
}
