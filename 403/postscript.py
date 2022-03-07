"""
UVA :: 403 :: Postscript
https://onlinejudge.org/external/4/403.pdf
jramaswami
"""


import sys


C5 = {
    'A': ['.***..', '*...*.', '*****.', '*...*.', '*...*.'],
    'B': ['****..', '*...*.', '****..', '*...*.', '****..'],
    'C': ['.****.', '*...*.', '*.....', '*.....', '.****.'],
    'D': ['****..', '*...*.', '*...*.', '*...*.', '****..'],
    'E': ['*****.', '*.....', '***...', '*.....', '*****.'],
    'F': ['*****.', '*.....', '***...', '*.....', '*.....'],
    'G': ['.****.', '*.....', '*..**.', '*...*.', '.***..'],
    'H': ['*...*.', '*...*.', '*****.', '*...*.', '*...*.'],
    'I': ['*****.', '..*...', '..*...', '..*...', '*****.'],
    'J': ['..***.', '...*..', '...*..', '*..*..', '.**...'],
    'K': ['*...*.', '*..*..', '***...', '*..*..', '*...*.'],
    'L': ['*.....', '*.....', '*.....', '*.....', '*****.'],
    'M': ['*...*.', '**.**.', '*.*.*.', '*...*.', '*...*.'],
    'N': ['*...*.', '**..*.', '*.*.*.', '*..**.', '*...*.'],
    'O': ['.***..', '*...*.', '*...*.', '*...*.', '.***..'],
    'P': ['****..', '*...*.', '****..', '*.....', '*.....'],
    'Q': ['.***..', '*...*.', '*...*.', '*..**.', '.****.'],
    'R': ['****..', '*...*.', '****..', '*..*..', '*...*.'],
    'S': ['.****.', '*.....', '.***..', '....*.', '****..'],
    'T': ['*****.', '*.*.*.', '..*...', '..*...', '.***..'],
    'U': ['*...*.', '*...*.', '*...*.', '*...*.', '.***..'],
    'V': ['*...*.', '*...*.', '.*.*..', '.*.*..', '..*...'],
    'W': ['*...*.', '*...*.', '*.*.*.', '**.**.', '*...*.'],
    'X': ['*...*.', '.*.*..', '..*...', '.*.*..', '*...*.'],
    'Y': ['*...*.', '.*.*..', '..*...', '..*...', '..*...'],
    'Z': ['*****.', '...*..', '..*...', '.*....', '*****.'],
    ' ': ['......', '......', '......', '......', '......']
}


C5_W = 6
C5_H = 5
PAGE_W = PAGE_H = 60


class Page:

    def __init__(self):
        self.page = [['.' for _ in range(PAGE_W)] for _ in range(PAGE_H)]

    def _text_width(self, font, text):
        if font == 'C5':
            return C5_W * len(text)
        else:
            return len(text)

    def _inbounds(self, row, col):
        return row >= 0 and row < PAGE_H and col >= 0 and col < PAGE_W

    def _place_C5(self, row, col, char):
        for dr, char_row in enumerate(C5[char]):
            for dc, char_col in enumerate(char_row):
                r0, c0 = row + dr, col + dc
                if self._inbounds(r0, c0) and char_col != '.':
                    self.page[r0][c0] = char_col

    def center(self, font, row, text):
        """
        The ‘.C’/center command horizontally centers a string of font F on the
        page with the top row of string at row R. If the centering cannot be
        exact on the grid (ie the string takes an odd number of cells
        horizontally), the string should be centered equally on either side of
        the 31st column.
        """
        text_width = self._text_width(font, text)
        col = (PAGE_W - text_width) // 2
        if text_width % 2:
            col += 1
        self.place(font, row, col, text)

    def place(self, font, row, col, text):
        """
        The ‘.P’/place command places a string of font F whose top left corner
        is at location (R,C) with the first character in the string and
        continues horizontally to the right across the page.
        """
        if font == 'C1':
            for c in text:
                if self._inbounds(row, col) and c != ' ':
                    self.page[row][col] = c
                col += 1
        else:
            for c in text:
                self._place_C5(row, col, c)
                col += C5_W

    def left_justify(self, font, row, text):
        """
        The ‘.L’/left justify command places a string of font F whose top left
        corner is at location (R, 1) with the first character in the string and
        continues horizontally to the right across the page.
        """
        self.place(font, row, 0, text)

    def right_justify(self, font, row, text):
        """
        The ‘.R’/right justify command places a string of font F whose top
        right corner is at location (R, 60) with the last character in the
        string and continues horizontally to the left across the page
        """
        text_width = self._text_width(font, text)
        col = PAGE_W - text_width
        self.place(font, row, col, text)

    def dispatch(self, line):
        # Parse line.
        text_start = line.index('|')
        text = line[text_start+1:-1]
        tokens = line[:text_start].split()
        if len(tokens) == 4:
            command, font, row, col = tokens
            row = int(row)-1
            col = int(col)-1
        else:
            command, font, row = tokens
            row = int(row)-1
        if command == '.C':
            self.center(font, row, text)
        elif command == '.P':
            self.place(font, row, col, text)
        elif command == '.L':
            self.left_justify(font, row, text)
        elif command == '.R':
            self.right_justify(font, row, text)

    def __str__(self):
        return "\n".join("".join(row) for row in self.page) + "\n\n" + (60 * '-') + "\n"


def main():
    "Main program."
    page = Page()
    for line in sys.stdin:
        line = line.strip()
        if line == '.EOP':
            print(page)
            page = Page()
        else:
            page.dispatch(line)

if __name__ == '__main__':
    main()
