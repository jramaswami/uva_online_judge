// UVA :: 462 :: Bridge Hand Evaluator
// https://onlinejudge.org/external/4/462.pdf
// jramaswami

#include <bits/stdc++.h>

using namespace std;


typedef bitset<20> suit_t;

const int ACE{14}, KING{13}, QUEEN{12}, JACK{11}, TEN{10},
          CLUBS{0}, DIAMONDS{1}, HEARTS{2}, SPADES{3};


class Hand {
        vector<suit_t> suits;

        const vector<char> suitFaces{'C', 'D', 'H', 'S'};
        const vector<char> valFaces{'x', 'x', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
        const vector<string> bidMessage{"BID C", "BID D", "BID H", "BID S"};

        vector<int> suitCount{0, 0, 0, 0};
        vector<size_t> suitHighCard{0, 0, 0, 0};
        bitset<4> stopped;

        size_t findSuitIndex(char suitFace) {
            return distance(suitFaces.begin(), find(suitFaces.begin(), suitFaces.end(), suitFace));
        }

        size_t findValIndex(char valFace) {
            return distance(valFaces.begin(), find(valFaces.begin(), valFaces.end(), valFace));
        }

        int faceScore{0};
        int balanceScore{0};

        void scoreHand() {
            for (size_t suitIndex{0}; suitIndex < suitFaces.size(); suitIndex++) {
                // Each ace counts 4 points.
                if (suits[suitIndex].test(ACE)) {
                    faceScore += 4;
                    // A suit is stopped if it contains an ace
                    stopped.set(suitIndex);
                }
                // Each king counts 3 points.
                if (suits[suitIndex].test(KING)) {
                    faceScore += 3;
                    if (suitCount[suitIndex] <= 1) {
                        // Subtract a point for any king of a suit in which the
                        // hand holds no other cards.
                        faceScore--;
                    } else {
                        // A suit is stopped if it contains a king and at least
                        // one other card.
                        stopped.set(suitIndex);
                    }
                }
                // Each queen counts 2 points.
                if (suits[suitIndex].test(QUEEN)) {
                    faceScore += 2;
                    if (suitCount[suitIndex] <= 2) {
                        // Subtract a point for any queen in a suit in which
                        // the hand holds only zero or one other cards.
                        faceScore--;
                    } else {
                        // A suit is stopped if it contains a queen and at
                        // least two other cards.
                        stopped.set(suitIndex);
                    }
                }
                // Each jack counts one point.
                if (suits[suitIndex].test(JACK)) {
                    faceScore += 1;
                    if (suitCount[suitIndex] <= 3) {
                        // Subtract a point for any jack in a suit in which the
                        // hand holds only zero, one, or two other cards.
                        faceScore--;
                    }
                }

                // Add a point for each suit in which the hand contains exactly two cards.
                if (suitCount[suitIndex] == 2) {
                    balanceScore++;
                }
                // Add two points for each suit in which the hand contains exactly one card.
                // Add two points for each suit in which the hand contains no cards.
                if (suitCount[suitIndex] <= 1) {
                    balanceScore+= 2;
                }
            }
        }

    public:

        Hand(const string &line) {
            suits = vector<suit_t>(4);
            size_t i{0};
            // Read 13 cards.
            for (int card{0}; card < 13; card++) {
                size_t valIndex{findValIndex(line[i])};
                size_t suitIndex{findSuitIndex(line[i+1])};
                suitCount[suitIndex]++;
                suits[suitIndex].set(valIndex);
                suitHighCard[suitIndex] = max(suitHighCard[suitIndex], valIndex);
                i += 3;
            }
            scoreHand();
        }

        string getBid() {
            // One may open bidding in “no trump” if the hand evaluates to 16
            // or more points ignoring rules 5, 6, and 7 and if all four suits
            // are stopped. A no trump bid is always preferred over a suit bid
            // when both are possible.
            if (faceScore >= 16 && stopped.all()) {
                return "BID NO-TRUMP";
            }

            // One may open bidding in a suit if the hand evaluates to 14 or
            // more points. Bidding is always opened in one of the suits with
            // the most cards.
            if (faceScore + balanceScore >= 14) {
                size_t highSuit{0};
                int highCardCount{suitCount[0]};
                size_t highCard{suitHighCard[0]};
                for (size_t suitIndex{1}; suitIndex < 4; ++suitIndex) {
                    if (suitCount[suitIndex] > highCardCount) {
                        highCardCount = suitCount[suitIndex];
                        highCard = suitHighCard[suitIndex];
                        highSuit = suitIndex;
                    } else if (suitCount[suitIndex] == highCardCount) {
                        if (suitHighCard[suitIndex] >= highCard) {
                            highCardCount = suitCount[suitIndex];
                            highCard = suitHighCard[suitIndex];
                            highSuit = suitIndex;
                        }
                    }
                }
                return bidMessage[highSuit];
            }

            // If the hand evaluates to fewer than 14 points, then the player
            // must pass.
            return "PASS";
        }

        friend ostream& operator<< (ostream &os, const Hand &hand);
};

ostream& operator<< (ostream &os, const Hand &hand) {
    for (size_t s{0}; s < hand.suits.size(); ++s) {
        for (size_t c{2}; c < hand.valFaces.size(); ++c) {
            if (hand.suits[s].test(c)) {
                os << hand.valFaces[c] << hand.suitFaces[s] << " ";
            }
        }
    }
    return os;
}

string makeBid(const string &line) {
    string bid;
    Hand hand(line);
    return hand.getBid();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Solution code.
    string line;
    while (getline(cin, line)) {
        if (line == "") {
            break;
        }
        cout << makeBid(line) << endl;
    }
    return EXIT_SUCCESS;
}
