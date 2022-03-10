"""
UVA :: 10258 :: Contest Scoreboard
https://onlinejudge.org/external/102/10258.pdf
jramaswami
"""


import math


class Contestant:

    def __init__(self, cid):
        self.cid = cid
        self.solved = [False for _ in range(10)]
        self.solved_count = 0
        self.timer = [math.inf for _ in range(10)]
        self.penalties = [0 for _ in range(10)]
        self.total_time = 0
        self.submissions = 0

    def record_result(self, pid, timer, result):
        self.submissions += 1
        if result == 'C':
            self.timer[pid] = min(self.timer[pid], timer)
            if not self.solved[pid]:
                self.solved[pid] = True
                self.solved_count += 1
        elif result == 'I':
            if timer < self.timer[pid]:
                self.penalties[pid] += 1

    def compute_total_time(self):
        self.total_time = sum(t + (p * 20) for s, t, p
                                           in zip(
                                               self.solved,
                                               self.timer,
                                               self.penalties
                                            )
                                            if s
        )

    def sort_key(self):
        return (-self.solved_count, self.total_time, self.cid)

    def __repr__(self):
        return f"Contestant({self.cid=} {self.submissions=} {self.solved_count=} {self.timer=} {self.penalties=} {self.total_time=})"


def main():
    "Main program."
    import sys
    import operator
    test_cases = int(sys.stdin.readline())
    sys.stdin.readline()   # Read trailing line.
    for t in range(test_cases):

        contestants = [Contestant(i) for i in range(101)]
        entry = sys.stdin.readline().strip()
        while entry:
            tokens = entry.split()
            cid, pid, timer = (int(i) for i in tokens[:-1])
            result = tokens[-1]
            contestants[cid].record_result(pid, timer, result)
            entry = sys.stdin.readline().strip()

        for contestant in contestants:
            contestant.compute_total_time()

        contestants.sort(key=operator.methodcaller('sort_key'))
        for contestant in contestants:
            if contestant.submissions:
                print(contestant.cid, contestant.solved_count, contestant.total_time)

        if t < test_cases - 1:
            print()


if __name__ == '__main__':
    main()
