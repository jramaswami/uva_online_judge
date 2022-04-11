// UVA :: 10660 :: Citizen attention offices
// https://onlinejudge.org/external/106/10660.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

struct Area {
    number_t r{0}, c{0};
    number_t pop{0};

    Area(number_t _r, number_t _c, number_t _p): r{_r}, c{_c}, pop{_p} {}
};

/*
pair<int, int> iToRC(number_t i) {
    number_t r{i / 5};
    number_t c{i % 5};
    return make_pair(r, c);
}

int rcToI(number_t r, number_t c) {
    return (5 * r) + c;
}
*/

number_t computeDistance(Area area, number_t index) {
    number_t r{index / 5};
    number_t c{index % 5};
    number_t dist{abs(area.r - r) + abs(area.c - c) * area.pop};
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int T{0};
    cin >> T;
    while (T--) {
        int N{0};
        cin >> N;
        vector<Area> areas;
        areas.reserve(N);
        for (int i{0}; i < N; ++i) {
            number_t r{0}, c{0};
            number_t p{0};
            cin >> r >> c >> p;
            areas.emplace_back(r, c, p);
        }

        vector<number_t> soln(5, 26);
        number_t minDist{LLONG_MAX};
        for (number_t a{0}; a < 25; ++a) {
            for (number_t b{a+1}; b < 25; ++b) {
                for (number_t c{b+1}; c < 25; ++c) {
                    for (number_t d{c+1}; d < 25; ++d) {
                        for (number_t e{d+1}; e < 25; ++e) {
                            vector<number_t> candidate{a, b, c, d, e};
                            number_t totalDist{0};
                            for (auto area : areas) {
                                vector<number_t> dists(5, 0);
                                transform(
                                    candidate.begin(), candidate.end(),
                                    dists.begin(),
                                    [&area](number_t i) {
                                        return computeDistance(area, i);
                                    }
                                );
                                auto it = min_element(dists.begin(), dists.end());
                                totalDist += (*it);
                            }
                            if (totalDist < minDist) {
                                minDist = totalDist;
                                soln = candidate;
                            } else if (totalDist == minDist) {
                                if (lexicographical_compare(
                                    candidate.begin(), candidate.end(),
                                    soln.begin(), soln.end()
                                )) {
                                    soln = candidate;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i{0}; i < 5; ++i) {
            cout << soln[i];
            if (i < 4) {
                cout << " ";
            }
        }
        cout << endl;
    }
    return EXIT_SUCCESS;
}
