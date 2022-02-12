"""
UVA :: 156 :: Ananagrams
https://onlinejudge.org/external/1/156.pdf
jramaswami
"""


import collections


def main():
    "Main program."
    import sys
    words = []
    for line in sys.stdin:
        words.extend(
            (wd, tuple(sorted(c for c in wd.lower())))
            for wd in line.strip().split() if wd != '#'
        )
    keys = collections.defaultdict(list)
    for wd, key in words:
        keys[key].append(wd)
    ananagrams = [t[0] for t in keys.values() if len(t) == 1]
    ananagrams.sort(key=lambda t: tuple(ord(c) for c in t))
    print("\n".join(ananagrams))






if __name__ == '__main__':
    main()
