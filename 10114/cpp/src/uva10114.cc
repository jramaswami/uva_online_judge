// UVA :: 10114
// https://uva.onlinejudge.org/external/101/10114.pdf

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string month_word(int n) {
    if (n == 1)
        return "month";
    else
        return "months";
}

int break_even(const int duration, double loan_amount, double car_value, const vector<double> &depreciation_records) {
    double payment = loan_amount / static_cast<double>(duration);
    if (car_value > loan_amount) {
        return 0;
    }
    auto curr_depreciation = depreciation_records[0];
    for (auto month = 1; month <= duration; month++) {
        loan_amount = loan_amount - payment;
        if (depreciation_records[month] > 0) {
            curr_depreciation = depreciation_records[month];
        }
        car_value = car_value * (1.0 - curr_depreciation);
        if (car_value > loan_amount) {
            return month;
        }
    }
    return duration;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    while (true) {
        int duration, records;
        double payment, loan_amount;
        cin >> duration >> payment >> loan_amount >> records;
        if (duration < 0) {
            break;
        }

        vector<double> depreciation_records(duration+1, 0);
        for (auto r = 0; r < records; ++r) {
            int month;
            double depr;
            cin >> month >> depr;
            depreciation_records[month] = depr;
        }

        double car_value = (loan_amount + payment) * (1.0 - depreciation_records[0]);
        auto result = break_even(duration, loan_amount, car_value, depreciation_records);
        cout << result << " " << month_word(result) << endl;
    }
    return 0;
}
