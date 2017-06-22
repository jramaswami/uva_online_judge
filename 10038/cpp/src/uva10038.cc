// UVA :: 10038
// https://uva.onlinejudge.org/external/100/10038.pdf

#include <bitset>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string line;
    bitset<3001> jolly;
    while (getline(cin, line)) {
        jolly.reset();
        istringstream is(line);
        int prev = 0;
        int array_length;
        is >> array_length;
        for (auto n = 0; n < array_length; ++n) {
            int i;
            is >> i;
            if (n > 0) {
                jolly.set(abs(prev - i));
            }
            prev = i;
        }
        bool is_jolly = true;
        for (auto i = 1; i < array_length; ++i) {
            if (!jolly.test(i)) {
                is_jolly = false;
                break;
            }
        }
        if (is_jolly) {
            cout << "Jolly" << endl;;
        } else {
            cout << "Not jolly" << endl;
        }
    }
    return 0;
}
