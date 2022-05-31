// UVA :: 11566 :: Let’s Yum Cha!
// https://onlinejudge.org/external/115/11566.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;
using number_t = long long int;

// There are up to 11 people (10 + 1) at the party.
// The maximum to spend is $100.
// The maximum total to spend must then be 11 * $100 = $1100
const number_t INF{5000};

struct DimSum {
    number_t price{0}, totalFavor{0};
};

struct Solver {
    number_t friendCount{0}, dimSumCount{0}, spendingLimit{0};
    vector<DimSum> dimSums;

    Solver(number_t _friendCount, number_t _spendingLimitEach, number_t _teaCharge, number_t _dimSumCount) {
        friendCount = _friendCount;
        // Azrael's trick from forum.
        spendingLimit =  static_cast<number_t>(floor(static_cast<double>(_spendingLimitEach * (friendCount + 1)) / 1.1 + 1e-6) - (friendCount + 1) * _teaCharge);
        dimSumCount = _dimSumCount;
    }

    void addDimSum(DimSum _dimSum) {
        dimSums.push_back(_dimSum);
    }

    double solve() {
        // First compute the maximum favor possible.
        number_t maxFavor{0};
        for (auto dimSum : dimSums) {
            maxFavor += (2 * dimSum.totalFavor);
        }


        number_t dimSumLimit = (2 * (friendCount + 1));

        // dp[dim sums purchased][total favor] = min price
        vector<vector<number_t>> prevDp(dimSumLimit+1, vector<number_t>(maxFavor+1, INF));
        vector<vector<number_t>> nextDp(dimSumLimit+1, vector<number_t>(maxFavor+1, INF));
        // You can get zero favor with zero dollars by purchasing no dim sums.
        prevDp[0][0] = 0;

        for (auto currDimSum : dimSums) {
            for (number_t prevDSCount{0}; prevDSCount <= dimSumLimit; ++prevDSCount) {
                for (number_t prevFavor{0}; prevFavor <= maxFavor; ++prevFavor) {
                    if (prevDp[prevDSCount][prevFavor] == INF) {
                        continue;
                    }
                    // Purchase 0
                    nextDp[prevDSCount][prevFavor] = min(
                        nextDp[prevDSCount][prevFavor],
                        prevDp[prevDSCount][prevFavor]
                    );

                    // Purchase 1
                    if (prevDSCount + 1 <= dimSumLimit) {
                        number_t currFavor1{prevFavor + currDimSum.totalFavor};
                        number_t currPrice1{prevDp[prevDSCount][prevFavor] + currDimSum.price};
                        nextDp[prevDSCount+1][currFavor1] = min(
                                nextDp[prevDSCount+1][currFavor1],
                                currPrice1
                        );
                    }

                    // Purchase 2
                    if (prevDSCount + 2 <= dimSumLimit) {
                        number_t currFavor2{prevFavor + (2 * currDimSum.totalFavor)};
                        number_t currPrice2{prevDp[prevDSCount][prevFavor] + (2 * currDimSum.price)};
                        nextDp[prevDSCount+2][currFavor2] = min(
                                nextDp[prevDSCount+2][currFavor2],
                                currPrice2
                        );
                    }
                }
            }

            prevDp = nextDp;
            nextDp = vector<vector<number_t>>(dimSumLimit+1, vector<number_t>(maxFavor+1, INF));
        }

        // Find answer
        number_t bestFavor{0};
        for (number_t dsCount{0}; dsCount <= dimSumLimit; ++dsCount) {
            for (number_t favor{0}; favor <= maxFavor; ++favor) {
                // Check actual price.
                if (prevDp[dsCount][favor] <= spendingLimit) {
                    bestFavor = max(bestFavor, favor);
                }
            }
        }
        return (static_cast<double>(bestFavor) / static_cast<double>(friendCount + 1));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    number_t friendCount{0}, dimSumCount{0}, spendingLimitEach{0}, teaCharge{0};
    cin >> friendCount >> spendingLimitEach >> teaCharge >> dimSumCount;
    while (friendCount || spendingLimitEach || teaCharge || dimSumCount) {
        Solver solver(friendCount, spendingLimitEach, teaCharge, dimSumCount);
        for (number_t i{0}; i < dimSumCount; ++i) {
            DimSum dimSum;
            cin >> dimSum.price;
            for (number_t j{0}; j <= friendCount; ++j) {
                number_t favor{0};
                cin >> favor;
                dimSum.totalFavor += favor;
            }
            solver.addDimSum(dimSum);
        }

        cout << fixed << setprecision(2) << solver.solve() << "\n";

        cin >> friendCount >> spendingLimitEach >> teaCharge >> dimSumCount;
    }

    return EXIT_SUCCESS;
}
