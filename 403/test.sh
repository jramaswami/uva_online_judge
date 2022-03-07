echo "Will run blood.py ..."
for i in {1..100}
do
    if test -f "test$i.txt"; then
        echo "Running test $i ..."
        python3 postscript.py < test$i.txt > output$i.txt
        diff expected$i.txt output$i.txt
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
