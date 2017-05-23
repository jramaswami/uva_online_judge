"""
UVA :: 11727 :: Cost Cutting
"""

import sys


def median(a, b, c):
    """Returns the median value of the three given values."""
    if a < b:
        if b < c:
            # a < b < c
            return b
        else:
            # a < b and c < b
            return max(a, c)
    else:
        # b < a
        if a < c:
            # b < a < c
            return a
        else:
            # b < a and c < a
            return max(b, c)


def main():
    """Main program."""
    test_cases = int(sys.stdin.readline())
    for test in range(1, test_cases+1):
        a, b, c = [int(s) for s in sys.stdin.readline().split()]
        answer = median(a, b, c)
        print("Case %d: %d" % (test, answer))

if __name__ == '__main__':
    main()
