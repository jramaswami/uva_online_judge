// UVA :: 1047 :: Zones
// https://onlinejudge.org/external/10/1047.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int planned{0}, built{0}, caseNo{1};
    cin >> planned >> built;
    while (planned || built) {
        // planned <= 20
        // Areas will at most 20 bits set, one for each tower.
        vector<int> areas((1 << 21), 0);
        // Read the total number of customers each tower serves.
        for (int i{0}; i < planned; ++i) {
            cin >> areas[(1 << i)];
        }
        // Read the overlapping service areas.
        int ca{0};
        cin >> ca;
        for (int i{0}; i < ca; ++i) {
            // Read number of towers in overlapping area.
            // Use bitmask to indicate that the tower is in the area.
            int ts{0}, overlap{0};
            cin >> ts;
            for (int j{0}; j < ts; ++j) {
                int t{0};
                cin >> t;
                // Convert to zero-based.
                t--;
                overlap |= (1 << t);
            }
            // Read how many customers are in the overlapping area.
            cin >> areas[overlap];
            // Now for each tower in the overlap, subtract that from the
            // area served by the tower alone.
            for (int b{0}; b < planned; ++b){
                int mask = (1 << b);
                if (mask & overlap) {
                    areas[mask] -= areas[overlap];
                }
            }
        }

        for (size_t i{0}; i < areas.size(); ++i) {
            if (areas[i]) {
                cerr << bitset<20>(i) << " " << areas[i] << endl;
            }
        }

        // Solve
        int maxServed{0}, maxTowers{0};
        for (int candidate{0}; candidate <= (1 << (planned+1)); ++candidate) {
            // Find numbers where the popcount is the number of towers built.
            if (__builtin_popcount(candidate) == built) {
                // Find the sum of all the areas served by the towers.
                int served{0};
                for (size_t i{0}; i < areas.size(); i++) {
                    if (i & candidate) {
                        served += areas[i];
                    }
                }
                if (served > maxServed) {
                    maxServed = served;
                    maxTowers = candidate;
                } else if (served == maxServed) {
                    // Lexicographic.
                    // First bit not set in both.
                    int b = __builtin_ffs(candidate ^ maxTowers) - 1;
                    int mask{1 << b};
                    if (mask & candidate) {
                        maxTowers = candidate;
                    }
                }
            }
        }
        cout << "Case Number  " << caseNo << endl;
        cout << "Number of Customers: " << maxServed << endl;
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
