// UVA :: 10172 :: The Lonesome Cargo Distributor
// https://onlinejudge.org/external/101/10172.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;


struct Station {
    int id{0};
    size_t capacity{0};
    int expected{0};
    deque<int> queue;

    Station(int i, size_t q): id{i}, capacity{q} { }

    bool empty() {
        return queue.empty();
    }

    bool full() {
        return capacity == 0;
    }

    int dequeue() {
        assert(!queue.empty());
        int package = queue.front();
        /* cerr << "Dequeueing package " << package << " @ " << id << endl; */
        queue.pop_front();
        capacity++;
        return package;
    }

    void deliver(int package) {
        /* cerr << "Delivering package " << package << " @ " << id << endl; */
        assert(package == id);
        expected--;
    }

    void enqueue(int package) {
        assert(capacity > 0);
        /* cerr << "Enqueing package " << package << " @ " << id << endl; */
        queue.push_back(package);
        capacity--;
    }
};

ostream& operator<<(ostream &os, const Station &station) {
    os << "Station id=" << station.id << " capacity= " << station.capacity
       << " expected=" << station.expected << " queue=";
    copy(station.queue.begin(), station.queue.end(), ostream_iterator<int>(os, " "));
    return os;
}

struct Carrier {
    size_t capacity{0};
    vector<int> stack;

    Carrier(size_t c): capacity{c} { }

    bool empty() {
        return stack.empty();
    }

    bool full() {
        return capacity == 0;
    }

    int peek() {
        return stack.back();
    }

    int pop() {
        assert(!stack.empty());
        int package = stack.back();
        /* cerr << "Unstacking " << package << " from carrier." << endl; */
        stack.pop_back();
        capacity++;
        return package;
    }

    void push(int package) {
        assert(capacity > 0);
        /* cerr << "Stacking " << package << " from carrier." << endl; */
        stack.push_back(package);
        capacity--;
    }
};

ostream& operator<<(ostream &os, const Carrier &carrier) {
    os << "Carrier capacity= " << carrier.capacity << " stack=";
    copy(carrier.stack.begin(), carrier.stack.end(), ostream_iterator<int>(os, " "));
    return os;
}

// After reaching any station (say, station X), the cargo carrier first
// attempts to unload cargo. Starting from the topmost cargo in its stack, it
// checks the tag attached to the cargo. If it finds that the cargo has
// destination X, then it unloads it (the cargo) to platform A, otherwise it
// checks to see whether the queue in platform B has any vacant position, and
// if so it puts the cargo at the rear of the queue.  This unloading procedure
// continues from the top to the bottom of the stack until one fails or the
// stack becomes empty, whichever comes first. Each successful unloading
// attempt requires exactly 1 minute, that is, unloading 3 cargoes in a station
// will require exactly 3 minutes.
bool unload(Carrier &carrier, Station &station) {
    if (carrier.empty()) {
        return false;
    }
    if (carrier.peek() == station.id) {
        station.deliver(carrier.pop());
        return true;
    }
    if (station.full()) {
        return false;
    }
    station.enqueue(carrier.pop());
    return true;
}

// After unloading is complete, the carrier begins to load. The carrier
// continues to take the cargo in front of the queue in platform B and put it
// on top of its stack until the queue is empty or the stack is full, whichever
// comes first. Each successful loading attempt also requires exactly 1 minute,
// that is, loading 4 cargoes from a station will require exactly 4 minutes.
// After loading is complete, the carrier moves to the next station in the
// ring.
int load(Carrier &carrier, Station &station) {
    if (station.empty()) {
        return false;
    }
    if (carrier.full()) {
        return false;
    }
    carrier.push(station.dequeue());
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int testCases{0};
    cin >> testCases;
    while (testCases) {
        /* cerr << "test " << testCases << endl; */

        int stationCount{0}, carrierCapacity{0}, queueCapacity{0};
        cin >> stationCount >> carrierCapacity >> queueCapacity;
        vector<Station> stations;
        stations.reserve(stationCount);
        for (int i{0}; i < stationCount; ++i) {
            stations.push_back(Station(i+1, queueCapacity));
            int queueCount{0};
            cin >> queueCount;
            for (int q{0}; q < queueCount; ++q) {
                int package{0};
                cin >> package;
                stations[i].enqueue(package);
            }
        }

        // Count the number of packages for each station and set the capacity for the station.
        for (auto station : stations) {
            for (auto package : station.queue) {
                stations[package-1].expected++;
            }
        }

        Carrier carrier(carrierCapacity);
        int time{-2};
        int currStation{0};
        while (any_of(stations.begin(), stations.end(), [](Station &s) {return s.expected > 0;})) {

            /*
            cerr << "Status at time " << time << endl;
            copy(stations.begin(), stations.end(), ostream_iterator<Station>(cerr, "\n"));
            cerr << "Carrier: " << carrier << endl;
            cerr << endl;
            */

            time += 2;

            /*
            cerr << "Arrived " << stations[currStation] << " @ " << time << endl;
            cerr << "Carrier " << carrier << endl;
            */

            // Arrive at currStation.
            while (unload(carrier, stations[currStation])) {
                time++;
            }
            while (load(carrier, stations[currStation])) {
                time++;
            }

            /*
            cerr << "Leaving " << stations[currStation] << " @ " << time << endl;
            cerr << "Carrier " << carrier << endl;
            cerr << endl;
            */

            currStation = (currStation + 1) % stationCount;
        }
        cout << time << endl;
        --testCases;
    }
    return EXIT_SUCCESS;
}
