// UVA :: 11498 :: Divison of Nlogonia

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    while (true) {
        int K;
        cin >> K;
        if (K == 0) break;

        int N, M;
        cin >> N >> M;
        for (auto k = 0; k < K; ++k) {
            int X, Y;
            cin >> X >> Y;
            if (X == N || Y == M) {
                cout << "divisa\n";
            } else {
                if (Y < M) {
                    cout << "S";
                } else {
                    cout << "N";
                }
                if (X < N) {
                    cout << "O\n";
                } else {
                    cout << "E\n";
                }
            }
        }
    }

    return 0;
}
