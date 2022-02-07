// UVA :: 893 :: Y3K Problem
// https://onlinejudge.org/external/8/893.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (1) {
        int prediction, day, month, year;
        cin >> prediction >> day >> month >> year;
        // prediction < 1,000,000,000 which is less than 32 bit int.
        if (prediction == 0 && day == 0 && month == 0 && year == 0) {
            return EXIT_SUCCESS;
        }

        // Move forward until first of the year.
        date_t date{day, month, year};
        while (1) {
            if (date.day == 1 && date.month == 1) {
                break;
            }
            if (prediction == 0) {
                break;
            }
            increment(date);
            prediction -= 1;
        }

        // Move forward by year.
        while (prediction >= daysInYear(date)) {
            prediction -= daysInYear(date);
            date.year += 1;
        }

        // Move forward for the rest of the year.
        while (prediction) {
            increment(date);
            prediction -= 1;
        }
        cout << date.day << " " << date.month << " " << date.year << endl;
    }
}
