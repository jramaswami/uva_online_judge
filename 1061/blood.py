"""
UVA :: 1061 :: Consanguine Calculations
https://onlinejudge.org/external/10/1061.pdf
jramaswami
"""


import sys
import collections


COMBINATIONS = [
    ('A+', 'AA++'), ('A+', 'AA+-'), ('A+', 'AO++'), ('A+', 'AO+-'),
    ('A-', 'AA--'), ('A-', 'AO--'),
    ('AB+', 'AB++'), ('AB+', 'AB+-'),
    ('AB-', 'AB--'),
    ('B+', 'BB++'), ('B+', 'BB+-'), ('B+', 'BO++'), ('B+', 'BO+-'),
    ('B-', 'BB--'), ('B-', 'BO--'),
    ('O+', 'OO++'), ('O+', 'OO+-'),
    ('O-', 'OO--')
]


ALL_ALLELES = list(sorted(set(a for _, a in COMBINATIONS)))


def main():
    "Main program."

    def possible_alleles(blood_type):
        return [a for bt, a in COMBINATIONS if bt == blood_type]

    def possible_blood_types(allele):
        return [bt for bt, a in COMBINATIONS if a == allele]

    def combine_alleles(p1, p2):
        p1abo1, p1abo2, p1rh1, p1rh2 = p1
        p2abo1, p2abo2, p2rh1, p2rh2 = p2

        for abo1 in [p1abo1, p1abo2]:
            for abo2 in [p2abo1, p2abo2]:
                for rh1 in [p1rh1, p1rh2]:
                    for rh2 in [p2rh1, p2rh2]:
                        callele = [
                            min(abo1, abo2), max(abo1, abo2),
                            min(rh1, rh2), max(rh1, rh2)
                        ]
                        yield "".join(callele)

    case = 1
    while 1:

        line = sys.stdin.readline().strip()
        if not line:
            continue
        if line == 'E N D':
            break

        parent1, parent2, child = line.split()
        if parent1 == '?' or parent2 == '?':
            swapped = False
            if parent1 == '?':
                swapped = True
                parent1, parent2 = parent2, parent1

            result = set()
            for p1a in possible_alleles(parent1):
                for p2a in ALL_ALLELES:
                    for ca in combine_alleles(p1a, p2a):
                        if child in possible_blood_types(ca):
                            result.update(possible_blood_types(p2a))
            parent2 = "IMPOSSIBLE"
            if result:
                if len(result) > 1:
                    S = ", ".join(t for t in result)
                    parent2 = "{" + S + "}"
                else:
                    parent2 = "".join(t for t in result)
            if swapped:
                parent1, parent2 = parent2, parent1
        else:
            result = set()
            for p1a in possible_alleles(parent1):
                for p2a in possible_alleles(parent2):
                    for ca in combine_alleles(p1a, p2a):
                        result.update(possible_blood_types(ca))
            child = "IMPOSSIBLE"
            if result:
                if len(result) > 1:
                    S = ", ".join(t for t in result)
                    child = "{" + S + "}"
                else:
                    child = "".join(t for t in result)

        print(f"Case {case}: {parent1} {parent2} {child}")

        case += 1


if __name__ == '__main__':
    main()
