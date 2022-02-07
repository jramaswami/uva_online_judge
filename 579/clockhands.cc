// UVA :: 579 :: Clock Hands
// https://onlinejudge.org/external/5/579.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (1) {
        getline(cin, line);
        // 0:00 is the marker for end of input.
        if (line.compare("0:00") == 0) {
            return EXIT_SUCCESS;
        }
        // Read and parse input.
        size_t colonPos = line.find(":");
        int hour = stoi(line.substr(0, colonPos));
        int mins = stoi(line.substr(colonPos + 1, string::npos));
        // There are 12 hours so each contributs 360 / 12 = 30 degrees to the
        // hour hand.
        // There are 60 minutes in each hour, so the minutes contribute
        // 30 / 60 = 0.5 degrees to the hour hand.
        double hourAngle = (hour * 30) + (0.5 * mins);
        while (hourAngle >= 360.0) {
            hourAngle -= 360.0;
        }
        // There are 60 minutes for each hour so minutes contribute
        // 360 / 60 = 6 degrees to the minute hand.
        double minsAngle = (6 * mins);

        double minAngle = min(hourAngle, minsAngle);
        double maxAngle = max(hourAngle, minsAngle);
        double soln = min(maxAngle - minAngle, minAngle + 360.0 - maxAngle);
        cout << setprecision(3) << fixed << soln << endl;
    }
}
