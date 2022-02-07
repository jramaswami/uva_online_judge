// UVA :: 11947 :: Cancer or Scorpio?
// https://onlinejudge.org/external/8/11947.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

vector<string> signs{
    "capricorn", "aquarius", "pisces", "aries", "taurus", "gemini", "cancer",
    "leo", "virgo", "libra", "scorpio", "sagittarius", "capricorn"
};

vector<int> signBoundaries{
    0, 21, 20, 21, 21, 22, 22, 23, 22, 24, 24, 23, 23
};

struct date_t {
    int day;
    int month;
    int year;
};

bool isLeapYear(date_t date) {
    if (date.year % 4) {
        return false;
    } else if (date.year % 100) {
        return true;
    } else if (date.year % 400) {
        return false;
    }
    return true;
}

int daysInYear(date_t date) {
    if (isLeapYear(date)) {
        return 366;
    }
    return 365;
}

int daysInMonth(date_t date) {
    switch (date.month) {
        case 1:  // Jan
        case 3:  // Mar
        case 5:  // May
        case 7:  // Jul
        case 8:  // Aug
        case 10: // Oct
        case 12: // Dec
            return 31;
            break;
        case 2:  // Feb
            if (isLeapYear(date)) {
                return 29;
            } else {
                return 28;
            }
            break;
        default:
            return 30;
            break;
    }
}

void increment(date_t &date) {
    date.day += 1;
    if (date.day > daysInMonth(date)) {
        date.day = 1;
        date.month += 1;
        if (date.month >= 13) {
            date.month = 1;
            date.year += 1;
        }
    }
}

string birthSign(date_t &date) {
    int signIndex = date.month;
    if (date.day < signBoundaries[signIndex]) signIndex--;
    return signs[signIndex];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;
    string line;
    getline(cin, line);  // Read the rest of the line.
    int gestation = 40 * 7;
    for (int t = 1; t <= testCases; t++) {
        getline(cin, line);
        int month = stoi(line.substr(0, 2));
        int day = stoi(line.substr(2, 2));
        int year = stoi(line.substr(4, 4));
        date_t date{day, month, year};
        for (int d = 0; d < gestation; d++) {
            increment(date);
        }
        cout << t << " " << setw(2) << setfill('0') << date.month
             << "/" << setw(2) << setfill('0') << date.day
             << "/" << setw(4) << setfill('0') << date.year
             << " " << birthSign(date) << endl;
    }
}
