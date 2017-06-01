"""
UVA :: 462 :: Bridge Hand Evaluator
https://uva.onlinejudge.org/external/4/462.pdf
"""

import sys


class Suit:
    """Represent suit in a hand."""
    def __init__(self, name):
        self.name = name
        self.ace = 0
        self.king = 0
        self.queen = 0
        self.jack = 0
        self.count = 0

    def append(self, card):
        """Add card to suit."""
        if card == 'A':
            self.ace = 4
        elif card == 'K':
            self.king = 3
        elif card == 'Q':
            self.queen = 2
        elif card == 'J':
            self.jack = 1

        self.count += 1

    def __repr__(self):
        return "%s: %d cards A=%d K=%d Q=%d J=%d" % (self.name, self.count,
                                                     self.ace, self.king,
                                                     self.queen, self.jack)


class Hand:
    """Represents bridge hand."""
    def __init__(self, data):
        self.spades = Suit('Spades')
        self.hearts = Suit('Hearts')
        self.clubs = Suit('Clubs')
        self.diamonds = Suit('Diamonds')

        for card in data.split():
            self[card[1]].append(card[0])

    def __getitem__(self, key):
        if key == 'S':
            return self.spades
        elif key == 'H':
            return self.hearts
        elif key == 'C':
            return self.clubs
        elif key == 'D':
            return self.diamonds

    def __repr__(self):
        return "%s\n%s\n%s\n%s\n" % (self.spades, self.hearts,
                                     self.clubs, self.diamonds)


def main():
    """Main program."""
    for line in sys.stdin:
        hand = Hand(line)


if __name__ == '__main__':
    main()
