"""
UVA :: 787 :: Maximum Sub-sequence Product
https://onlinejudge.org/external/7/787.pdf
jramaswami
"""


import sys
import math


def solve(nums):
    "Return the maximum subarray product."

    def init(n):
        """
        Initialize variables. Returns curr_product, max_negative, min_positive.
        """
        max_negative, min_positive = -math.inf, math.inf
        if n > 0:
            min_positive = n
        elif n < 0:
            max_negative = n
        return n, max_negative, min_positive

    # print(nums, file=sys.stderr)
    soln = nums[0]
    curr_product = max_negative = min_positive = 0
    for n in nums:
        soln = max(soln, n)
        if curr_product == 0:
            curr_product, max_negative, min_positive = init(n)
            # print(f"reset {n=} {curr_product=} {max_negative=} {min_positive=} {soln=}", file=sys.stderr)
            soln = max(curr_product, soln)
        else:
            curr_product *= n
            # print(f"ok {n=} {curr_product=} {max_negative=} {min_positive=} {soln=}", file=sys.stderr)
            soln = max(curr_product, soln)
            if curr_product < 0:
                if max_negative > -math.inf:
                    soln = max(curr_product // max_negative, soln)
                max_negative = max(max_negative, curr_product)
            if curr_product > 0:
                if min_positive < math.inf:
                    soln = max(curr_product // min_positive, soln)
                min_positive = min(min_positive, curr_product)
    return soln


def main():
    "Main application."
    # Read all numbers into a list.
    all_input = []
    for line in sys.stdin:
        all_input.extend(int(n) for n in line.strip().split())

    # Process input
    nums = []
    for n in all_input:
        if n == -999999:
            print(solve(nums))
            nums = []
        else:
            nums.append(n)


if __name__ == '__main__':
    main()