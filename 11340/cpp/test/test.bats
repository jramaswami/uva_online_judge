# Tests for UVA 11340

@test "test0.txt" {
    ./uva11340 < test/test0.txt > test/output0.txt
    run diff test/output0.txt test/expected0.txt
    [ $status -eq 0 ]
}

@test "uHunt Test 1: UVa Online Judge" {
    ./uva11340 < test/test1.txt > test/output1.txt
    run diff test/output1.txt test/expected1.txt
    [ $status -eq 0 ]
}

@test "uHunt Test 2: brianfry713" {
    ./uva11340 < test/test2.txt > test/output2.txt
    run diff test/output2.txt test/expected2.txt
    [ $status -eq 0 ]
}
