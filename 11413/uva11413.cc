// UVA :: 11413 :: Fill the Containers
// https://onlinejudge.org/external/114/11413.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

bool possibleVolume(number_t targetVolume, int maxContainers, const vector<number_t> &vesselVolumes) {
    number_t currVolume{0}; int containerCount{0};
    for (auto v : vesselVolumes) {
        if (currVolume + v > targetVolume) {
            currVolume = v;
            containerCount++;
        } else {
            currVolume += v;
        }
    }
    containerCount++;
    return (containerCount <= maxContainers);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int vesselCount{0}, containerCount{0};
    while (cin >> vesselCount >> containerCount) {
        vector<number_t> vesselVolumes;
        vesselVolumes.reserve(vesselCount);
        copy_n(istream_iterator<number_t>(cin), vesselCount, back_inserter(vesselVolumes));

        number_t lo{*(max_element(vesselVolumes.begin(), vesselVolumes.end()))};
        number_t soln{lo};
        if (vesselCount > containerCount) {
            // Binary search for the answer.
            number_t hi{accumulate(vesselVolumes.begin(), vesselVolumes.end(), 0)};
            while (lo <= hi) {
                number_t mid{lo + ((hi - lo) / 2)};
                if (possibleVolume(mid, containerCount, vesselVolumes)) {
                    soln = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
        }
        cout << soln << endl;

    }
    return EXIT_SUCCESS;
}
