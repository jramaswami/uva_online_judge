"""
UVA :: 10646
https://uva.onlinejudge.org/external/106/10646.pdf
"""

import sys


def card_value(card):
    """Returns value of card."""
    if card[0] in ['A', 'K', 'Q', 'J', 'T']:
        return 10
    else:
        return int(card[0])


def main():
    """Main program."""
    test_cases = int(sys.stdin.readline())
    for test_index in range(1, test_cases+1):
        deck = sys.stdin.readline().split()
        hand = deck[-25:]
        pile = deck[:-25]
        total = 0
        for index in range(3):
            top_value = card_value(hand[index])
            total += top_value
            pile = list(pile[10 - top_value:])

        pile = pile + hand[3:]
        print('Case %d: %s' % (test_index, pile[total-1]))




if __name__ == '__main__':
    main()
