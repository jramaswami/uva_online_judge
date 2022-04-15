// UVA :: 624 :: CD
// https://onlinejudge.org/external/6/624.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Solver {
    int cdDuration{0}, trackCount{0}, solnDuration{0};
    vector<int> trackDurations, solnTracks, trackAcc;

    Solver(int c, int t) {
        cdDuration = c;
        trackCount = t;
        trackDurations.reserve(t);
    }

    void solve(int index, int durationAcc) {
        if (index >= trackCount) {
            if (durationAcc > solnDuration) {
                solnDuration = durationAcc;
                solnTracks.resize(trackAcc.size());
                copy(trackAcc.begin(), trackAcc.end(), solnTracks.begin());
            } else if (durationAcc == solnDuration && trackAcc.size() >= solnTracks.size()) {
                solnTracks.resize(trackAcc.size());
                copy(trackAcc.begin(), trackAcc.end(), solnTracks.begin());
            }
        } else {
            // Without current track.
            solve(index + 1, durationAcc);
            // With current track.
            if (durationAcc + trackDurations[index] <= cdDuration) {
                trackAcc.push_back(index);
                solve(index + 1, durationAcc + trackDurations[index]);
                trackAcc.pop_back();
            }
        }
    }

    void solve() {
        solve(0, 0);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int c, t;
    while (cin >> c) {
        cin >> t;
        Solver solver(c, t);
        copy_n(istream_iterator<int>(cin), t,
               back_inserter(solver.trackDurations)
        );
        solver.solve();
        for (size_t i{0}; i < solver.solnTracks.size(); ++i) {
            cout << solver.trackDurations[solver.solnTracks[i]] << " ";
        }
        cout << "sum:" << solver.solnDuration << endl;
    }
    return EXIT_SUCCESS;
}
