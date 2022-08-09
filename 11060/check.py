"""
UVA :: 11060 :: Beverages
jramaswami

Script to verify solutions.
"""


VERBOSE = False


def read_test_data(test_file):
    line = test_file.readline()
    if not line:
        return None, None, None
    N = int(line)
    beverages = []
    beverage_ids = dict()
    for i in range(N):
        b = test_file.readline().strip()
        beverage_ids[b] = i
        beverages.append(b)
    M = int(test_file.readline())
    adj = [[] for _ in beverages]
    for _ in range(M):
        a, b = test_file.readline().strip().split()
        if VERBOSE:
            print(f"{a} before {b}")
        u, v = beverage_ids[a], beverage_ids[b]
        adj[u].append(v)
    test_file.readline()
    return beverage_ids, beverages, adj


def read_topological_sort(output_file):
    output_data = output_file.readline().strip()
    i = output_data.rfind(':')
    topological_sort = [s.strip() for s in output_data[i+1:-1].split()]
    output_file.readline()
    return topological_sort


def check(beverage_ids, beverages, adj, topological_sort):
    order = [-1 for _ in beverage_ids]
    for i, b in enumerate(topological_sort):
        u = beverage_ids[b]
        order[u] = i

    ok = True
    for u, _ in enumerate(adj):
        for v in adj[u]:
            if order[u] > order[v]:
                print(f"{beverages[u]} should come before {beverages[v]}!")
                ok = False
            else:
                if VERBOSE:
                    print(f"{beverages[u]} came before {beverages[v]} ...")
    return ok


def main():
    "Main program."
    import os
    for t in range(1, 101):
        test_fname = f"./test{t}.txt"
        output_fname = f"./output{t}.txt"
        if os.path.exists(test_fname) and os.path.exists(output_fname):
            if VERBOSE:
                print(f"Checking test {t} ...")
            with open(test_fname, 'r') as test_file:
                with open(output_fname, 'r') as output_file:
                    ok = True
                    while 1:
                        beverage_ids, beverages, adj = read_test_data(test_file)
                        if beverages is None:
                            break
                        topological_sort = read_topological_sort(output_file)
                        if VERBOSE:
                            print(f"Checking {topological_sort}")
                        result = check(beverage_ids, beverages, adj, topological_sort)
                        if result:
                            if VERBOSE:
                                print(f"ok {topological_sort}")
                        else:
                            if VERBOSE:
                                print(f"FAIL {topological_sort}")
                        ok = ok or result

                    if ok:
                        print(f"Test {t} ok")
                    else:
                        print(f"Test {t} FAIL")


if __name__ == '__main__':
    main()
