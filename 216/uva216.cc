// UVA :: 216 :: Getting in Line
// https://onlinejudge.org/external/2/216.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int N{0}, networkId{1};
    cin >> N;
    while (N) {
        // Read the network coordinates.
        vector<int> xs; xs.reserve(N);
        vector<int> ys; ys.reserve(N);
        for (int i{0}; i < N; ++i) {
            cin >> xs[i] >> ys[i];
        }

        // Compute distance squared for each.
        vector<vector<double>> dist(N, vector<double>(N, 0.0));
        for (int i{0}; i < N; ++i) {
            for (int j{i+1}; j < N; ++j) {
                double dx{static_cast<double>(xs[i] - xs[j])};
                double dy{static_cast<double>(ys[i] - ys[j])};
                dist[i][j] = dist[j][i] = sqrt((dx * dx) + (dy * dy)) + 16.0;
            }
        }

        // Try every permutation.
        vector<int> p(N);
        iota(p.begin(), p.end(), 0);
        double solnDist{10e9};
        vector<int> solnPath(N, 0);
        while (1) {
            // Compute the network distance for the current permutation.
            double d{0};
            for (int i{0}; i + 1 < N; ++i) {
                int left{p[i]}, right{p[i+1]};
                d += dist[left][right];
            }

            if (d < solnDist) {
                solnDist = d;
                copy(p.begin(), p.end(), solnPath.begin());
            }

            if (!next_permutation(p.begin(), p.end())) {
                break;
            }
        }

        // Output solution.
        cout << "**********************************************************\n";
        cout << "Network #" << networkId << "\n";
        for (int i{0}; i + 1 < N; ++i) {
            int left{solnPath[i]}, right{solnPath[i+1]};
            cout << "Cable requirement to connect (" << xs[left] << ","
                 << ys[left] << ") to (" << xs[right] << "," << ys[right]
                 << ") is " << fixed << setprecision(2) << dist[left][right]
                 << " feet.\n";
        }
        cout << "Number of feet of cable required is "
             << fixed << setprecision(2) << solnDist << ".\n";

        cin >> N;
        networkId++;
    }

    return EXIT_SUCCESS;
}
