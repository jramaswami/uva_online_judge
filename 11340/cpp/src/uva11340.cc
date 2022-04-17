// UVA :: 11340
// https://uva.onlinejudge.org/external/113/11340.pdf

#include <cstdio>
#include <vector>

using namespace std;

int main() {
    int N;  // Number of tests
    scanf("%d\n", &N);
    for (auto n = 0; n < N; ++n) {
        vector<int> table(128, 0);
        int K;  // Number of characters in table.
        scanf("%d\n", &K);
        for (auto k = 0; k < K; ++k) {
            char c;
            int v;
            scanf("%c %d\n", &c, &v);
            table[c] = v;
        }
        int M;
        scanf("%d\n", &M);
        auto result = 0;
        int c = getchar();
        int m = 0;
        while (c != EOF && m < M) {
            result += table[c];
            c = getchar();
            if (c == '\n') ++m;
        }
        printf("%0.2f$\n", static_cast<double>(result) / 100.0 );
    }
    return 0;
}
