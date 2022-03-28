"""
UVA :: 11503 :: Virtual Friends
https://onlinejudge.org/external/115/11503.pdf
jramaswami
"""

class UnionFind:
    def __init__(self):
        self.id = dict()
        self.size = dict()

    def add_node(self, u):
        if u not in self.id:
            self.id[u] = u
            self.size[u] = 1

    def find(self, u):
        if self.id[u] != u:
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
        return self.size[u]


def main():
    "Main program."
    import sys
    test_cases = int(sys.stdin.readline())
    for _ in range(test_cases):
        edge_count = int(sys.stdin.readline())
        uf = UnionFind()
        for _ in range(edge_count):
            u, v = sys.stdin.readline().strip().split()
            uf.add_node(u)
            uf.add_node(v)
            sz = uf.union(u, v)
            print(sz)


if __name__ == '__main__':
    main()
