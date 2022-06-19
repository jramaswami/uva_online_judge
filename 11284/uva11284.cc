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
                int wt{static_cast<int>(100.0 * wt0)};
                cost[u][v] = wt;
                cost[v][u] = wt;
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

            cerr << "storeCount=" << storeCount << " roadCount=" << roadCount << endl;
            cerr << "FW" << endl;
            for (auto row : cost) {
                copy(row.begin(), row.end(), ostream_iterator<int>(cerr, " "));
                cerr << endl;
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
                double d0{0};
                cin >> u >> d0;
                int d{static_cast<int>(100.0 * d0)};
                destinations.push_back(u);
                discounts.push_back(d);
            }
            cerr << "destinations: ";
            copy(destinations.begin(), destinations.end(), ostream_iterator<int>(cerr, " "));
            cerr << endl;
            cerr << "discounts: ";
            copy(discounts.begin(), discounts.end(), ostream_iterator<int>(cerr, " "));
            cerr << endl;
        }

        int getCost(int a, int b) {
            int u{destinations[a]}, v{destinations[b]};
            return cost[u][v];
        }

        // Fix This!!!  Convert to top-down instead of bottom-up.
        double solve() {
            allVisited = (1 << destinations.size()) - 1;
            cache = vector<vector<int>>(destinations.size(), vector<int>(allVisited+1, -1));
            int result = solve0(0, 1);
            cerr << "cache" << endl;
            for (auto row : cache) {
                copy(row.begin(), row.end(), ostream_iterator<int>(cerr, " "));
                cerr << endl;
            }
            double soln{static_cast<double>(result) / 100.0};
            return soln;
        }

        // Return the money saved for a trip that visited that ended at the
        // current store and visited the set of visited stores.
        int solve0(int currentStore, int visitedStores) {
            // The money saved (discounts - road costs) is the
            // current discount + the money saved from any previous
            // trips.
            if (cache[currentStore][visitedStores] == -1) {
                int result{0};
                int previousVisitedStores{visitedStores ^ (1 << currentStore)};
                for (int previousStore{0}; previousStore < storeCount; previousStore++) {
                    // If the previous location is in the set of previously visited stores ...
                    if ((1 << previousStore) & previousVisitedStores) {
                        int discountsToHere{discounts[currentStore] - getCost(currentStore, previousStore)};
                        result = max(result, discountsToHere + solve0(previousStore, previousVisitedStores));
                    }
                }
                cache[currentStore][visitedStores] = result;
            }
            return cache[currentStore][visitedStores];
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
        double soln = solver.solve();
        cout << fixed << setprecision(2) << soln << endl;
    }
    return EXIT_SUCCESS;
}
