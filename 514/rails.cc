// UVA :: 514 :: Rails
// https://onlinejudge.org/external/5/514.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

bool solve(const vector<int> &requiredOrder) {
    size_t i{0};
    vector<int> station;
    deque<int> A(requiredOrder.size(), 0);
    iota(A.begin(), A.end(), 1);
    vector<int> B;

    while (!A.empty()) {

        /*
        cerr << "A: ";
        copy(A.begin(), A.end(), ostream_iterator<int>(cerr, " ")); cerr << endl;
        cerr << "station: ";
        copy(station.begin(), station.end(), ostream_iterator<int>(cerr, " ")); cerr << endl;
        cerr << "B: ";
        copy(B.begin(), B.end(), ostream_iterator<int>(cerr, " ")); cerr << endl;
        cerr << "requiredOrder: ";
        copy(requiredOrder.begin(), requiredOrder.end(), ostream_iterator<int>(cerr, " ")); cerr << endl;
        */

        // Move any vehicles from the station that will be in order.
        while (!station.empty() && station.back() == requiredOrder[i]) {
            B.push_back(station.back());
            station.pop_back();
            i++;
        }
        // Now move vehicle from A to station.
        station.push_back(A.front());
        A.pop_front();
    }

    // Move any vehicles left in the station that will be in order.
    while (!station.empty() && station.back() == requiredOrder[i]) {
        B.push_back(station.back());
        station.pop_back();
        i++;
    }

    return station.empty();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read the length of the arrays in this block.
    string line;
    getline(cin, line);
    int arraySize = stoi(line);
    while(arraySize) {

        // Read the blocks.
        getline(cin, line);
        while (line != "0") {
            istringstream iss(line);
            vector<int> requiredOrder;
            copy_n(istream_iterator<int>(iss), arraySize, back_inserter(requiredOrder));
            if (solve(requiredOrder)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }

            getline(cin, line);
        }
        cout << endl;

        // Read array length for next block.
        getline(cin, line);
        arraySize = stoi(line);

    }
    return EXIT_SUCCESS;
}
