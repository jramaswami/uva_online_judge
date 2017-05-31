"""
UVA :: 11507
https://uva.onlinejudge.org/external/115/11507.pdf
"""

import sys


def main():
    """Main program."""
    while True:
        wire_length = int(sys.stdin.readline())
        if wire_length == 0:
            break
        bends = sys.stdin.readline().split()
        current_direction = "+x"
        for bend in bends:
            if bend == 'No':
                continue
            if current_direction[1] == 'x':
                if current_direction[0] == '-':
                    # next direction is in opposite direction of bend
                    if bend[0] == '-':
                        current_direction = '+' + bend[1]
                    else:
                        current_direction = '-' + bend[1]
                else:
                    current_direction = bend

            elif bend[1] != current_direction[1]:
                continue
            else:
                if bend[0] == current_direction[0]:
                    current_direction = "-x"
                else:
                    current_direction = "+x"

        print(current_direction)


if __name__ == '__main__':
    main()
