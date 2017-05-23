# Tests for 11727

@test "test0.txt" {
    python uva11727.py < test0.txt > output0.txt
    run diff expected0.txt output0.txt
    [ $status -eq 0 ]
}
