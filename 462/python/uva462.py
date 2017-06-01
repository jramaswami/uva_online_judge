"""
        irint(card, '=', card_val, end=" ")
UVA :: 462 :: Bridge Hand Evaluator
https://uva.onlinejudge.org/external/4/462.pdf
"""

import sys
from collections import namedtuple, Counter


Hand = namedtuple('Hand', ['cards', 'suits'])


def value_card(card):
    """Returns value of card."""
    rank = card[0]
    if rank == 'A':
        return 4
    elif rank == 'K':
        return 3
    elif rank == 'Q':
        return 2
    elif rank == 'J':
        return 1
    else:
        return 0


def is_stopped(card_val, card_suit, hand):
    """Returns True if card_suit is stopped by card_val."""
    if card_val == 4:
        return True
    elif card_val == 3 and hand.suits[card_suit] >= 2:
        return True
    elif card_val == 2 and hand.suits[card_suit] >= 3:
        return True

    return False


def opening_bid(hand):
    """Returns the opening bid for the given hand."""
    score = 0

    stopped = {'S': False, 'H': False, 'C': False, 'D': False}

    for card in hand.cards:
        card_suit = card[1]
        card_val = value_card(card)
        if card_val > 0:
            if card_val == 3 and hand.suits[card_suit] < 2:
                card_val = 2
            elif card_val == 2 and hand.suits[card_suit] < 3:
                card_val = 1
            elif card_val == 1 and hand.suits[card_suit] < 4:
                card_val = 0

            stopped[card_suit] = stopped[card_suit] or \
                is_stopped(card_val, card_suit, hand)

            score += card_val


    if score >= 16 and all(stopped.values()):
        return 'BID NO-TRUMP'


    bid_suit = 'S'
    bid_cards = 0
    for suit in ['S', 'H', 'D', 'C']:

        if hand.suits[suit] > bid_cards:
            bid_suit = suit
            bid_cards = hand.suits[suit]

        if hand.suits[suit] < 2:
            score += 2
        elif hand.suits[suit] == 2:
            score += 1

    if score < 14:
        return 'PASS'
    else:
        return "BID %s" % bid_suit


def read_hand(line):
    """Returns integer list representing hand."""
    cards = line.split()
    suits = Counter([c[1] for c in cards])
    return Hand(cards, suits)


def main():
    """Main program."""
    for line in sys.stdin:
        line = line.strip()
        if line:
            print(opening_bid(read_hand(line)))


if __name__ == '__main__':
    main()
