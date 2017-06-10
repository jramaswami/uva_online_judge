# Tests for UVA 12247

@test "sample test" {
    python uva12247.py < test0.txt > output0.txt
    run diff expected0.txt output0.txt
    [ $status -eq 0 ]
}

@test "uDebug Test 1: brianfry713 input" {
    python uva12247.py < test_ud1.txt > output_ud1.txt
    run diff expected_ud1.txt output_ud1.txt
    [ $status -eq 0 ]
}

@test "uDebug Test 2: andrewins input" {
    python uva12247.py < test_ud2.txt > output_ud2.txt
    run diff expected_ud2.txt output_ud2.txt
    [ $status -eq 0 ]
}

@test "uDebug Test 3: feodorv input" {
    python uva12247.py < test_ud3.txt > output_ud3.txt
    run diff expected_ud3.txt output_ud3.txt
    [ $status -eq 0 ]
}
