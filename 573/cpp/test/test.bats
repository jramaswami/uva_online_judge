# Tests for UVA 573

@test "test0.txt" {
    ./uva573 < test/test0.txt > test/output0.txt
    run diff test/output0.txt test/expected0.txt
    [ $status -eq 0 ]
}
