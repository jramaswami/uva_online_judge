// UVA :: 11389 :: The Bus Driver Problem
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int busRouteCount{0}, maxHours{0}, overtimeRate{0};
    cin >> busRouteCount >> maxHours >> overtimeRate;
    while (busRouteCount || maxHours || overtimeRate) {
        vector<int> morningRoutes;
        morningRoutes.reserve(busRouteCount);
        copy_n(istream_iterator<int>(cin), busRouteCount, back_inserter(morningRoutes));
        vector<int> eveningRoutes;
        eveningRoutes.reserve(busRouteCount);
        copy_n(istream_iterator<int>(cin), busRouteCount, back_inserter(eveningRoutes));
        sort(morningRoutes.begin(), morningRoutes.end());
        sort(eveningRoutes.begin(), eveningRoutes.end(), greater<int>());
        int overtimeHours{0};
        for (int i{0}; i < busRouteCount; i++) {
            int k{morningRoutes[i] + eveningRoutes[i]};
            if (k > maxHours) {
                overtimeHours += (k - maxHours);
            }
        }
        cout << (overtimeHours * overtimeRate) << "\n";
        cin >> busRouteCount >> maxHours >> overtimeRate;
    }

    return EXIT_SUCCESS;
}
