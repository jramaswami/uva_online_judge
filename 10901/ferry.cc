// UVA :: 10901 :: Ferry Loading III
// https://onlinejudge.org/external/109/10901.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

struct Car {
    size_t id;
    int queueTime;

    Car(size_t i, int q): id{i}, queueTime{q} { }
};

ostream& operator<<(ostream &os, const Car car) {
    os << "Car(" << car.id << ", " << car.queueTime << ")";
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while (testCases) {
        string line;
        size_t ferryCapacity{0}, carCount{0};
        int crossingTime{0};
        cin >> ferryCapacity >> crossingTime >> carCount;
        getline(cin, line); // Read trailing newline.
        deque<Car> leftQueue;
        deque<Car> rightQueue;
        vector<int> arrivalTimes;
        for (size_t i{0}; i < carCount; i++) {
            getline(cin, line);
            auto it = find(line.begin(), line.end(), ' ');
            int queueTime{stoi(line.substr(0, distance(line.begin(), it)))};
            string side(it+1, line.end());
            if (side == "left") {
                leftQueue.emplace_back(i, queueTime);
            } else {
                rightQueue.emplace_back(i, queueTime);
            }
            arrivalTimes.push_back(0);
        }

        bool onLeftBank{true};
        vector<Car> ferry;
        int time{0};
        while (!(leftQueue.empty() && rightQueue.empty())) {
            cerr << "Time = " << time <<  " on " << (onLeftBank ? "left bank" : "right bank") << endl;
            cerr << "L: "; copy(leftQueue.begin(), leftQueue.end(), ostream_iterator<Car>(cerr, " ")); cerr << endl;
            cerr << "R: "; copy(rightQueue.begin(), rightQueue.end(), ostream_iterator<Car>(cerr, " ")); cerr << endl;
            cerr << endl;

            if (onLeftBank) {
                // Load waiting cars.
                while(!leftQueue.empty() && leftQueue.front().queueTime <= time && ferry.size() < ferryCapacity) {
                    ferry.push_back(leftQueue.front());
                    leftQueue.pop_front();
                }
            } else {
                // Load waiting cars.
                while(!rightQueue.empty() && rightQueue.front().queueTime <= time && ferry.size() < ferryCapacity) {
                    ferry.push_back(rightQueue.front());
                    rightQueue.pop_front();
                }
            }

            // If there are no cars on the ferry wait until one arrives.
            // If there are cars, cross and deliver the cars.
            if (ferry.empty()) {
                if (onLeftBank) {
                    if (leftQueue.empty()) {
                        // Cross
                        cerr << "Crossing to right bank empty." << endl;
                        time = max(time, rightQueue.front().queueTime) + crossingTime;
                        onLeftBank = !onLeftBank;
                    } else if (!rightQueue.empty() && rightQueue.front().queueTime < leftQueue.front().queueTime) {
                        cerr << "Crossing to right bank empty to pick up car." << endl;
                        time = rightQueue.front().queueTime + crossingTime;
                        onLeftBank = !onLeftBank;
                    } else {
                        time = leftQueue.front().queueTime;
                        cerr << "Waiting on left bank until " << time << endl;
                    }
                } else {
                    if (rightQueue.empty()) {
                        // Cross
                        cerr << "Crossing to left bank empty." << endl;
                        time = max(time, leftQueue.front().queueTime) + crossingTime;
                        onLeftBank = !onLeftBank;
                    } else if (!leftQueue.empty() && leftQueue.front().queueTime < rightQueue.front().queueTime) {
                        cerr << "Crossing to left bank empty to pick up car." << endl;
                        time = leftQueue.front().queueTime + crossingTime;
                        onLeftBank = !onLeftBank;
                    } else {
                        time = rightQueue.front().queueTime;
                        cerr << "Waiting on right bank until " << time << endl;
                    }
                }
            } else {
                time += crossingTime;
                cerr << "Arriving @ " << time << ": ";
                copy(ferry.begin(), ferry.end(), ostream_iterator<Car>(cerr, ", "));
                cerr << endl;
                for (auto car : ferry) {
                    arrivalTimes[car.id] = time;
                }
                ferry.clear();
                onLeftBank = !onLeftBank;
            }
        }
        copy(arrivalTimes.begin(), arrivalTimes.end(), ostream_iterator<int>(cout, "\n"));
        --testCases;
        // Line *between* test cases.
        if (testCases) {
            cout << endl;
        }
    }

    return EXIT_SUCCESS;
}
