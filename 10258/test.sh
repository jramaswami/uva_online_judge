exec=$(basename *.py .py)
echo "Found $exec.py"
echo "Will run python3 $exec.py ..."
for i in {1..100}
do
    if test -f "test$i.txt"; then
        echo "Running test $i ..."
        python3 $exec.py < test$i.txt > output$i.txt
        # diff -w -s -B expected$i.txt output$i.txt
        diff -s expected$i.txt output$i.txt
    fi
done
