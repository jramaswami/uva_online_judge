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


struct Solver {
    vector<Area> areas;
    vector<number_t> candidate;
    vector<number_t> soln;
    number_t minDist{LLONG_MAX};

    Solver(const vector<Area> a) {
        candidate = vector<number_t>(5, 0);
        soln = vector<number_t>(5, 26);
        areas = a;
    }

    number_t closestOffice(Area area) {
        number_t d{LLONG_MAX};
        for (auto i : candidate) {
            number_t r{i / 5};
            number_t c{i % 5};
            number_t x{area.pop * (abs(area.r - r) + abs(area.c - c))};
            d = min(d, x);
        }
        return d;
    }

    number_t computeTotalDistance() {
        number_t t{0};
        for (auto area : areas) {
            t += closestOffice(area);
        }
        return t;
    }

    void solve(size_t index) {
        if (index < candidate.size()) {
            number_t init{0};
            if (index > 0) {
                init = candidate[index - 1] + 1;
            }
            for (number_t a{init}; a < 25; ++a) {
                candidate[index] = a;
                solve(index + 1);
            }
        } else {
            number_t d = computeTotalDistance();
            if (d < minDist) {
                minDist = d;
                copy(candidate.begin(), candidate.end(), soln.begin());
            }
        }
    }

    vector<number_t> solve() {
        solve(0);
        return soln;
    }
};

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

        Solver solver(areas);
        auto soln = solver.solve();
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
