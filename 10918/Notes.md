# Notes for UVA 10918 :: Tri Tiling


There are eight identifiable states for a given column.  Use the bits of a
number to represent the state, where a bit of 1 means that the space is covered.

Then we can map transitions.

State 6 -> State 1
xxaa
xxx
xxx

State 5 -> State 2
xxx
xxaa
xxx

State 7 -> State 3
xxxa
xxxa
xxx

State 4 -> State 3
xxaa
xxbb
xxx

State 3 -> State 4
xxx
xxx
xxaa

State 2 -> State 5
xxaa
xxx
xxbb


State 7 -> State 6
xxx
xxxa
xxxa

State 1 -> State 6
xxx
xxaa
xxbb

State 6 -> State 7
xxaa
xxxb
xxxb

State 3 -> State 7
xxxa
xxxa
xxbb

State 0 -> State 7
xxaa
xxbb
xxcc

State 7 -> State0 (by adding no dominoes)
xxx
xxx
xxx

Using these we can come up with the state transitions.
