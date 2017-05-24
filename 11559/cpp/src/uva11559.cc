// UVA :: 11559
// https://uva.onlinejudge.org/external/115/11559.pdf

#include <iostream>
#include <limits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int participants, budget, hotels, weeks;
    while (cin >> participants) {
        cin >> budget >> hotels >> weeks;
        int min_cost = numeric_limits<int>::max();
        for (auto h = 0; h < hotels; ++h) {
            int cost;
            cin >> cost;
            for (auto w = 0; w < weeks; ++w) {
                int beds;
                cin >> beds;
                if (beds >= participants && participants * cost < min_cost) {
                    min_cost = participants * cost;
                }
            }
        }
        if (min_cost == numeric_limits<int>::max() || min_cost > budget) {
            cout << "stay home" << endl;
        } else {
            cout << min_cost << endl;
        }
    }
    return 0;
}
