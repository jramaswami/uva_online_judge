// UVA :: 637 :: Booklet Printing
// https://onlinejudge.org/external/6/637.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    int pagesToPrint{0};
    cin >> pagesToPrint;
    while (pagesToPrint) {
        int slotCount{pagesToPrint / 4};
        if (pagesToPrint % 4) slotCount++;
        slotCount *= 4;
        vector<string> slots(slotCount, "Blank");
        int pageNumber{1};
        int slotNumber{1};
        while (slotNumber < slotCount) {
            if (pageNumber <= pagesToPrint) {
                slots[slotNumber] = to_string(pageNumber);
            }
            if (slotNumber % 2) {
                slotNumber += 1;
            } else {
                slotNumber += 3;
            }
            pageNumber++;
        }
        slotNumber = 0;
        pageNumber = slotCount;
        while (slotNumber < slotCount) {
            if (pageNumber <= pagesToPrint) {
                slots[slotNumber] = to_string(pageNumber);
            }
            if (slotNumber % 2) {
                slotNumber += 1;
            } else {
                slotNumber += 3;
            }
            pageNumber--;
        }

        /*
        copy(slots.begin(), slots.end(), ostream_iterator<string>(cerr, " "));
        cerr << endl;
        */

        cout << "Printing order for " << pagesToPrint << " pages:" << endl;
        bool front{true};
        for (int slotNumber{0}; slotNumber + 1 < slotCount; slotNumber += 2) {
            if (slots[slotNumber] == "Blank" && slots[slotNumber+1] == "Blank") {
                continue;
            }
            int sheetNumber{(slotNumber / 4) + 1};
            cout << "Sheet " << sheetNumber << ", ";
            if (front) {
                cout << "front: ";
            } else {
                cout << "back : ";
            }
            cout << slots[slotNumber] << ", " << slots[slotNumber+1] << endl;
            front = !front;
        }

        cin >> pagesToPrint;
    }

    return EXIT_SUCCESS;
}
