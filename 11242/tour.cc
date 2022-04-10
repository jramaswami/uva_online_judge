// UVA :: 11242 :: Tour de France
// https://onlinejudge.org/external/112/11242.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

double maxSpread(const vector<double> &front, const vector<double> &back) {
    vector<double> drive;
    for (auto f : front) {
        for (auto b : back) {
            double d{b / f};
            drive.push_back(d);
        }
    }
    sort(drive.begin(), drive.end());
    vector<double> spread;
    adjacent_difference(drive.begin(), drive.end(), back_inserter(spread),
            [](double d2, double d1) { return d2 / d1; }
    );
    return *(max_element(spread.begin() + 1, spread.end()));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int f{0}, r{0};
    cin >> f;
    while (f) {
        cin >> r;
        vector<double> front;
        front.reserve(f);
        copy_n(istream_iterator<double>(cin), f, back_inserter(front));
        vector<double> back;
        back.reserve(r);
        copy_n(istream_iterator<double>(cin), r, back_inserter(back));
        cout << fixed << setprecision(2) << maxSpread(front, back) << endl;
        cin >> f;
    }
    return EXIT_SUCCESS;
}
