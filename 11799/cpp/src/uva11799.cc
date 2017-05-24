// UVA :: 11799
// https://uva.onlinejudge.org/external/117/11799.pdf

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (auto t = 1; t <= T; ++t) {
        auto min_speed = 0;
        int N;
        cin >> N;
        for (auto n = 0; n < N; ++n) {
            int c;
            cin >> c;
            min_speed = max(min_speed, c);
        }
        cout << "Case " << t << ": " << min_speed << "\n";
    }
    return 0;
}
