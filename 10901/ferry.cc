// UVA :: 10901 :: Ferry Loading III
// https://onlinejudge.org/external/109/10901.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

const int LEFT{0};
const int RIGHT{1};
const int WAIT{2};
const vector<string> BANK_NAME{"Left", "Right"};

struct Car {
    size_t id{0};
    int queueTime{0};

    Car(size_t i, int q): id{i}, queueTime{q} { }
};

struct Ferry {
    size_t capacity{0};
    int crossingTime{0};
    int clock{0};
    int bank{LEFT};
    vector<Car> hold;

    Ferry() { }
    Ferry(size_t c, int t): capacity{c}, crossingTime{t} { }

    void load(deque<Car> &bank) {
        while (hold.size() < capacity && !bank.empty() && bank.front().queueTime <= clock) {
            hold.push_back(bank.front());
            bank.pop_front();
        }
    }

    void unload(vector<int> &arrivalTimes) {
        for (auto car: hold) {
            arrivalTimes[car.id] = clock;
        }
        hold.clear();
    }

    void waitUntil(int time) {
        if (time > clock) {
            clock = time;
        }
    }

    void cross() {
        clock += crossingTime;
        bank = (bank == LEFT ? RIGHT : LEFT);
    }

};

ostream& operator<<(ostream &os, const Ferry &ferry) {
    os << "Ferry on " << BANK_NAME[ferry.bank] << " clock " << ferry.clock;
    return os;
}

struct FerrySystem {
    Ferry ferry;
    vector<deque<Car>> banks;
    vector<int> arrivalTimes;

    FerrySystem(size_t ferryCapacity, int crossingTime, size_t carCount) {
        banks = vector<deque<Car>>(2, deque<Car>());
        ferry = Ferry(ferryCapacity, crossingTime);
        arrivalTimes = vector<int>(carCount, 0);
    }

    void enqueueLeft(size_t id, int queueTime) {
        banks[LEFT].emplace_back(id, queueTime);
    }

    void enqueueRight(size_t id, int queueTime) {
        banks[RIGHT].emplace_back(id, queueTime);
    }

    int nextBank() {
        // Which bank has the next car arriving in line.
        if (banks[LEFT].empty() && banks[RIGHT].empty()) {
            return 0;
        } else if (banks[LEFT].empty()) {
            return RIGHT;
        } else if (banks[RIGHT].empty()) {
            return LEFT;
        } else if (banks[LEFT].front().queueTime < banks[RIGHT].front().queueTime) {
            return LEFT;
        } else if (banks[LEFT].front().queueTime > banks[RIGHT].front().queueTime) {
            return RIGHT;
        }
        return WAIT;
    }

    void simulate() {
        while (!(banks[LEFT].empty() && banks[RIGHT].empty())) {
            if (banks[ferry.bank].empty() || banks[ferry.bank].front().queueTime > ferry.clock) {
                int nb = nextBank();
                if (nb == WAIT) {
                    ferry.waitUntil(banks[ferry.bank].front().queueTime);
                } else {
                    ferry.waitUntil(banks[nb].front().queueTime);
                }
            }
            ferry.load(banks[ferry.bank]);
            ferry.cross();
            ferry.unload(arrivalTimes);
        }
    }
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
        FerrySystem system(ferryCapacity, crossingTime, carCount);
        getline(cin, line); // Read trailing newline.
        for (size_t i{0}; i < carCount; i++) {
            getline(cin, line);
            auto it = find(line.begin(), line.end(), ' ');
            int queueTime{stoi(line.substr(0, distance(line.begin(), it)))};
            string side(it+1, line.end());
            if (side == "left") {
                system.enqueueLeft(i, queueTime);
            } else {
                system.enqueueRight(i, queueTime);
            }
        }

        system.simulate();
        copy(system.arrivalTimes.begin(), system.arrivalTimes.end(), ostream_iterator<int>(cout, "\n"));
        --testCases;
        // Line *between* test cases.
        if (testCases) {
            cout << endl;
        }
    }

    return EXIT_SUCCESS;
}
