// UVA :: 11926 :: Multitasking
// https://onlinejudge.org/external/119/11926.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const int MAX_TIME{1000000};
const int START{1};
const int STOP{-1};

struct Event {
    int time{0};
    int type{0};
    Event(int ti, int ty): time{ti}, type{ty} { };
};

bool operator< (const Event &lhs, const Event &rhs) {
    if (lhs.time == rhs.time) {
        return lhs.type < rhs.type;
    }
    return lhs.time < rhs.time;
}

bool conflictExists(vector<Event> &events) {
    sort(events.begin(), events.end());
    int active{0};
    for (auto e : events) {
        if (e.type == START) {
            active++;
        } else {
            active--;
        }
        if (active > 1) {
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int oneTimeTasks{0}, repeatingTasks{0};
    cin >> oneTimeTasks >> repeatingTasks;
    int testCase{0};
    while (oneTimeTasks || repeatingTasks) {
        testCase++;
        vector<Event> events;
        for (int i{0}; i < oneTimeTasks; i++) {
            int startTime{0}, stopTime{0};
            cin >> startTime >> stopTime;
            events.emplace_back(startTime, START);
            events.emplace_back(stopTime, STOP);
        }

        for (int i{0}; i < repeatingTasks; i++) {
            int startTime{0}, stopTime{0}, repeatTime{0};
            cin >> startTime >> stopTime >> repeatTime;
            while (startTime <= MAX_TIME) {
                events.emplace_back(startTime, START);
                events.emplace_back(stopTime, STOP);
                startTime += repeatTime;
                stopTime += repeatTime;
            }
        }
        cout << (conflictExists(events) ? "CONFLICT" : "NO CONFLICT") << endl;

        cin >> oneTimeTasks >> repeatingTasks;
    }
    return EXIT_SUCCESS;
}
