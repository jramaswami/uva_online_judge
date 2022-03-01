// UVA :: 161 :: Traffic Lights
// https://onlinejudge.org/external/1/161.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const int ON{1};
const int OFF{-1};
const int TIME_LIMIT{5 * 60 * 60};

struct Event {
    int type;
    int time;
    size_t id;

    Event(int time_, int type_, size_t id_) {
        time = time_;
        type = type_;
        id = id_;
    }

};

bool operator< (const Event &lhs, const Event &rhs) {
    if (lhs.time == rhs.time) {
        return lhs.type > rhs.type;
    } else {
        return lhs.time > rhs.time;
    }
}

int solve(const vector<int> &lights) {
    deque<bool> on(lights.size(), true);
    priority_queue<Event, vector<Event>> pq;
    // Init queue.
    for (size_t i{0}; i < lights.size(); i++) {
        // Light is on at time zero.
        // It will turn orange at lights[i] - 5;
        Event e{lights[i] - 5, OFF, i};
        pq.push(e);
    }

    // Process queue.
    while (!pq.empty()) {
        Event e = pq.top();
        pq.pop();
        if (e.type == ON) {
            on[e.id] = true;
            if (all_of(on.begin(), on.end(), [](bool t) { return t; })) {
                return e.time;
            }
            // Compute when it will turn orange.
            Event e0{e.time + lights[e.id] - 5, OFF, e.id};
            pq.push(e0);
        } else {
            on[e.id] = false;
            // Compute when it well be on again.
            // It will be orange for 5 seconds.
            // It will then be red for lights[e.id].
            Event e0{e.time + lights[e.id] + 5, ON, e.id};
            if (e0.time <= TIME_LIMIT) {
                pq.push(e0);
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    // Read all input.
    int x{0};
    vector<int> input;
    while (cin >> x) {
        input.push_back(x);
    }

    auto left = input.begin();
    auto right = find(input.begin(), input.end(), 0);
    while (left != input.end()) {
        vector<int> lights(left, right);
        if (all_of(lights.begin(), lights.end(), [](int x){return x=0;})) {
            break;
        }
        int soln = solve(lights);
        if (soln >= 0) {
            int hh{soln / (60 * 60)};
            soln -= (hh * 60 * 60);
            int mm{soln / 60};
            soln -= (mm * 60);
            int ss{soln};
            cout << setw(2) << setfill('0') << hh << ":"
                 << setw(2) << setfill('0') << mm << ":"
                 << setw(2) << setfill('0') << ss << endl;
        } else {
            cout << "Signals fail to synchronise in 5 hours" << endl;
        }
        left = right+1;
        right = find(left, input.end(), 0);
    }
    return EXIT_SUCCESS;
}
