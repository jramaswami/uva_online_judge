"""
Tests for UVA :: 462 :: Bridge Hand Evaluator
"""

import unittest
import uva462


class Test_uva462(unittest.TestCase):
    """Tests of uva462"""

    def test_1(self):
        """Test case 1"""
        data = 'KS QS TH 8H 4H AC QC TC 5C KD QD JD 8D'
        hand = uva462.read_hand(data)
        bid = uva462.opening_bid(hand)
        self.assertEqual('BID D', bid)

    def test_2(self):
        """Test case 2"""
        data = 'AC 3C 4C AS 7S 4S AD TD 7D 5D AH 7H 5H'
        hand = uva462.read_hand(data)
        bid = uva462.opening_bid(hand)
        self.assertEqual('BID NO-TRUMP', bid)


if __name__ == '__main__':
    unittest.main()
