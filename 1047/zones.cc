// UVA :: 1047 :: Zones
// https://onlinejudge.org/external/10/1047.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

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
    cerr << "computing " << bitset<20>(towers) << endl;
    // Inclusion/exclusion principle.
    int total{0};
    // First get the sum of towerCustomers[i] where i is in towers.
    for (size_t i{0}; i < towerCustomers.size(); ++i) {
        int mask = 1 << i;
        if (towers & mask) {
            total += towerCustomers[i];
        }
    }

    // Now, add/subtract overlapping zones.
    for (auto overlap : overlappingZones) {
        int subset = overlap.first & towers;
        if (subset == towers) {
            continue;
        }
        int k = __builtin_popcount(subset);
        // k will tell you how many times this has already been counted.
        // Check for overflow.
        if (k > 1) {
            cerr << "overlap " << bitset<20>(overlap.first) << endl;
            if (k % 2) {
                cerr << bitset<20>(subset) << "+" << overlap.second << endl;
                total += overlap.second;
            } else {
                cerr << bitset<20>(subset) << "-" << overlap.second << endl;
                total -= overlap.second;
            }
        }
    }
    cerr << "total=" << total << endl;
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
        cerr << "planned " << planned << " build " << built << endl;
        int limit = (1 << (planned));
        int maxCustomers{0};
        int maxTowers{0};
        for (int towers{0}; towers < limit; ++towers) {
            if (__builtin_popcount(towers) != built) {
                continue;
            }
            cerr << "popcount " << __builtin_popcount(towers) << endl;
            int customers = computeCustomersServed(
                                towers, towerCustomers, overlappingZones
            );
            cerr << bitset<20>(towers) << " " << customers << endl;
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
        cout << endl;

        cin >> planned >> built;
        if (planned || built) {
            cout << endl;
        }
        caseNo++;
    }
    return EXIT_SUCCESS;
}
