# Tests for UVA 11799

@test "test0.txt" {
    ./uva11799 < test/test0.txt > test/output0.txt
    run diff test/output0.txt test/expected0.txt
    [ $status -eq 0 ]
}
