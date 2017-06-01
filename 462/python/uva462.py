"""
UVA :: 462 :: Bridge Hand Evaluator
https://uva.onlinejudge.org/external/4/462.pdf
"""

import sys
from collections import namedtuple, Counter


CLUBS = 1

JACK = 11
QUEEN = 12
KING = 13
ACE = 14

SUIT_ABBREV = ['', 'C', 'D', 'H', 'S']
SUITS = {"S": 400, "H": 300, "D": 200, "C": 100}
FACES = dict([(str(i), i) for i in range(2, 10)])
FACES.update({'T': 10, 'J': JACK, 'Q': QUEEN, 'K': KING, 'A': ACE})

Hand = namedtuple('Hand', ['cards', 'suits'])


def is_face_card(card):
    """Return True if card is face card."""
    return card % 100 > 10


def card_value(card):
    """Returns value of card."""
    if is_face_card(card):
        return (card % 100) - 10
    else:
        return 0


def card_suit(card):
    """Returns the integer representing the suit."""
    return card // 100


def opening_bid(hand):
    """Returns the opening bid for the given hand."""
    score = 0

    stopped = [True, False, False, False, False]

    for card in hand.cards:
        if is_face_card(card):
            val = card_value(card)
            required_cards = val - 3
            if hand.suits[card_suit(card)] < required_cards:
                val = val - 1
            else:
                if val > 1:
                    stopped[card // 100] = True
            score += val

    if score >= 16 and all(stopped):
        return 'BID NO-TRUMP'

    max_suit = CLUBS
    max_num = hand.suits[CLUBS]
    for suit in hand.suits:

        if hand.suits[suit] >= max_num:
            max_suit = suit

        if hand.suits[suit] < 2:
            score += 2
        elif hand.suits[suit] == 2:
            score += 1

    if score < 14:
        return 'PASS'
    else:
        return "BID %s" % SUIT_ABBREV[max_suit]


def read_hand(line):
    """Returns integer list representing hand."""
    cards = sorted([SUITS[c[1]] + FACES[c[0]] for c in line.split()],
                   reverse=True)
    suits = Counter([c // 100 for c in cards])
    return Hand(cards, suits)


def main():
    """Main program."""
    for line in sys.stdin:
        print(opening_bid(read_hand(line)))


if __name__ == '__main__':
    main()
