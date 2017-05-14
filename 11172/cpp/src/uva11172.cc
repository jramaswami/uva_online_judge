// UVA :: 11172

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        int n, m;
        cin >> n >> m;
        if (n < m) {
            cout << "<\n";
        } else if (n > m) {
            cout << ">\n";
        } else {
            cout << "=\n";
        }
    }
    return 0;
}
