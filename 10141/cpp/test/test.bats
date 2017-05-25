# Tests for UVA 10141

@test "test0.txt" {
    ./uva10141 < test/test0.txt > test/output0.txt
    run diff test/output0.txt test/expected0.txt
    [ $status -eq 0 ]
}
