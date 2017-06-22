# Tests for UVA 10038

@test "test0.txt" {
    ./uva10038 < test/test0.txt > test/output0.txt
    run diff test/output0.txt test/expected0.txt
    [ $status -eq 0 ]
}

@test "uDebug Test 1: uDebug" {
    ./uva10038 < test/test1.txt > test/output1.txt
    run diff test/output1.txt test/expected1.txt
    [ $status -eq 0 ]
}

@test "uDebug Test 2: Zeronfinity" {
    ./uva10038 < test/test2.txt > test/output2.txt
    run diff test/output2.txt test/expected2.txt
    [ $status -eq 0 ]
}

