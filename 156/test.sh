exec="python3 ananagrams.py"
echo "Will run ./$exec ..."
for i in {1..100}
do
    if test -f "test$i.txt"; then
        echo "Running test $i ..."
        $exec < test$i.txt > output$i.txt
        # diff -w -s -B expected$i.txt output$i.txt
        diff -s expected$i.txt output$i.txt
    fi
done

# for i in {1..10}
# do
#     echo "Running random test $i ..."
#     python3 make_test.py > test_random$i.txt
#     ./$exec < test_random$i.txt > output_random$i.txt
#     diff -w -s -B expected_random$i.txt output_random$i.txt
#     if [ $? -ne 0 ]; then
#         echo "FAILED TEST"
#         break
#     fi
# done
