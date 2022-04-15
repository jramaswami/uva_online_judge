// UVA :: 1047 :: Zones
// https://onlinejudge.org/external/10/1047.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int nCk(int n, int k) {
    double res = 1;
    for (int i = 1; i <= k; ++i)
        res = res * (n - k + i) / i;
    return (int)(res + 0.01);
}

// Choose the towers such that choices including tower 1 are preferable. If
// this rule still leaves room for more than one solution, solutions including
// tower 2 are preferable, and so on
int chooseTowers(int left, int right) {
    // First bit not set in both.
    int b = __builtin_ffs(left ^ right) - 1;
    int mask{1 << b};
    if (mask & left) {
        return left;
    }
    return right;
}

int computeCustomersServed(int towers, vector<int> towerCustomers, vector<pair<int, int>> overlappingZones) {
    // Inclusion/exclusion principle.
    int total{0};
    int N{0};
    // First get the sum of towerCustomers[i] where i is in towers.
    for (size_t i{0}; i < towerCustomers.size(); ++i) {
        int mask = 1 << i;
        if (towers & mask) {
            total += towerCustomers[i];
        }
        N++;
    }

    for (int i{2}; i <= N; ++i) {
        for (auto oz : overlappingZones) {
            int subset = towers & oz.first;
            int k = __builtin_popcount(subset);
            if (k >= i) {
                int t = nCk(k, i);
                if (i % 2) {
                    total += (oz.second * t);
                } else {
                    total -= (oz.second * t);
                }
            }
        }
    }

    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int planned{0}, built{0}, caseNo{1};
    cin >> planned >> built;
    while (planned || built) {
        // planned <= 20
        // Areas will at most 20 bits set, one for each tower.
        vector<int> towerCustomers;
        towerCustomers.reserve(planned);
        copy_n(istream_iterator<int>(cin), planned, back_inserter(towerCustomers));
        // Read the overlapping service zones.
        int ca{0};
        cin >> ca;
        vector<pair<int, int>> overlappingZones(ca);
        for (int i{0}; i < ca; ++i) {
            // Read number of towers in overlapping area.
            // Use bitmask to indicate that the tower is in the area.
            int ts{0};
            cin >> ts;
            for (int j{0}; j < ts; ++j) {
                int t{0};
                cin >> t;
                t--;   // Convert to 0-based indexing.
                overlappingZones[i].first |= (1 << t);
            }
            // Read how many customers are in the overlapping zone.
            cin >> overlappingZones[i].second;
        }

        // Compute solution.
        int limit = (1 << (planned));
        int maxCustomers{0};
        int maxTowers{0};
        for (int towers{0}; towers < limit; ++towers) {
            if (__builtin_popcount(towers) != built) {
                continue;
            }
            int customers = computeCustomersServed(
                                towers, towerCustomers, overlappingZones
            );
            if (customers > maxCustomers) {
                maxCustomers = customers;
                maxTowers = towers;
            } else if (customers == maxCustomers) {
                maxTowers = chooseTowers(maxTowers, towers);
            }
        }

        // Print solution.
        cout << "Case Number  " << caseNo << endl;
        cout << "Number of Customers: " << maxCustomers << endl;
        cout << "Locations recommended: ";
        for (int b{0}; b < 32; ++b) {
            int mask = (1 << b);
            if (mask & maxTowers) {
                built--;
                cout << (b + 1);
                if (built) {
                    cout << " ";
                }
            }
        }
        cout << endl << endl;

        cin >> planned >> built;
        caseNo++;
    }
    return EXIT_SUCCESS;
}
