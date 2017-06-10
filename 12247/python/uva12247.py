"""
UVA :: 12247
https://uva.onlinejudge.org/external/122/12247.pdf
"""

import sys


def winning_card(cards):
    """Returns the winning card."""
    princess = sorted(cards[:3])
    prince = sorted(cards[3:])

    min_winner = princess[1] + 1

    if prince[0] <= princess[1]:
        if prince[1] <= princess[2]:
            return -1
        else:
            min_winner = princess[2] + 1

    if prince[0] > princess[2] and prince[1] > princess[2]:
        min_winner = 1

    free = [x not in cards for x in range(53)]
    for winner in range(min_winner, 54):
        if winner == 53:
            return -1
        elif free[winner]:
            return winner
        else:
            winner += 1


def main():
    """Main program."""
    while True:
        cards = [int(s) for s in sys.stdin.readline().split()]
        if cards[0] == 0:
            break
        print(winning_card(cards))


if __name__ == '__main__':
    main()
