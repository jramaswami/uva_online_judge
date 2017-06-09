# Tests for UVA 10646

@test "sample test" {
    python uva10646.py < test0.txt > output0.txt
    run diff expected0.txt output0.txt
    [ $status -eq 0 ]
}

@test "uDebug Test 1: UVa Online Judge" {
    python uva10646.py < test_ud1.txt > output_ud1.txt
    run diff -B expected_ud1.txt output_ud1.txt
    [ $status -eq 0 ]
}

@test "uDebug Test 2: Morass 666 lines" {
    python uva10646.py < test_ud2.txt > output_ud2.txt
    run diff -B expected_ud2.txt output_ud2.txt
    [ $status -eq 0 ]
}

@test "uDebug Test 3: Morass 1024 lines" {
    python uva10646.py < test_ud3.txt > output_ud3.txt
    run diff -B expected_ud3.txt output_ud3.txt
    [ $status -eq 0 ]
}
