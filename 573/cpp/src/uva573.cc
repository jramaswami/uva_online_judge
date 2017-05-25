// UVA :: 573 :: The Snail
// https://uva.onlinejudge.org/external/5/573.pdf

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    double well_height;
    cin >> well_height;
    while(well_height) {
        double climb_dist, slide_dist, fatigue_pct, fatigue_dist;
        double snail_height = 0.00;
        int day = 1;
        cin >> climb_dist >> slide_dist >> fatigue_pct;
        fatigue_dist = climb_dist * fatigue_pct / 100;
        while(true) {
            snail_height = snail_height + climb_dist;
            if (snail_height > well_height) {
                cout << "success on day " << day << "\n";
                break;
            }
            snail_height = snail_height - slide_dist;
            if (snail_height < 0) {
                cout << "failure on day " << day << "\n";
                break;
            }
            ++day;
            climb_dist -= fatigue_dist;
            if (climb_dist < 0) climb_dist = 0;
        }
        cin >> well_height;
    }
    return 0;
}
