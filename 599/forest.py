"""
UVA :: 599 :: The Forrest for the Trees
https://onlinejudge.org/external/5/599.pdf
jramaswami
"""


import collections


class UnionFind:
    def __init__(self):
        self.id = dict()
        self.size = dict()

    def add_node(self, u):
        if u not in self.id:
            self.id[u] = u
            self.size[u] = 1

    def find(self, u):
        if u != self.id[u]:
            self.id[u] = self.find(self.id[u])
        return self.id[u]

    def union(self, u, v):
        u = self.find(u)
        v = self.find(v)
        if u != v:
            if self.size[u] < self.size[v]:
                u, v, = v, u
            self.id[v] = u
            self.size[u] += self.size[v]

def main():
    "Main program."
    import sys
    test_cases = int(sys.stdin.readline())
    for _ in range(test_cases):
        uf = UnionFind()
        # Read the edges.  Stops at line of asterisks.
        line = sys.stdin.readline().strip()
        while not line[0] == '*':
            # Edges are capital letters.
            u, v = line[1], line[3]
            uf.add_node(u)
            uf.add_node(v)
            uf.union(u, v)
            line = sys.stdin.readline().strip()
        # Read the nodes
        line = sys.stdin.readline().strip()
        nodes = []
        if line:
            nodes = line.split(',')
        acorns = trees = 0
        for u in nodes:
            uf.add_node(u)
            if uf.find(u) == u:
                if uf.size[u] == 1:
                    acorns += 1
                else:
                    trees += 1
        print(f"There are {trees} tree(s) and {acorns} acorn(s).")


if __name__ == '__main__':
    main()
