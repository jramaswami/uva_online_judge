"""
Tests of UVA 11727
"""

import unittest
import uva11727 as uva


class TestUVA11727(unittest.TestCase):
    """Tests for UVA 11727"""

    def test_1(self):
        """Test 1"""
        self.assertEqual(2000, uva.median(1000, 2000, 3000))

    def test_2(self):
        """Test 2"""
        self.assertEqual(2000, uva.median(2000, 1000, 3000))

    def test_3(self):
        """Test 3"""
        self.assertEqual(2000, uva.median(1000, 3000, 2000))

    def test_4(self):
        """Test 4"""
        self.assertEqual(2000, uva.median(3000, 2000, 1000))

    def test_5(self):
        """Test 5"""
        self.assertEqual(2000, uva.median(2000, 1000, 3000))

    def test_6(self):
        """Test 6"""
        self.assertEqual(2000, uva.median(3000, 1000, 2000))


if __name__ == '__main__':
    unittest.main()
