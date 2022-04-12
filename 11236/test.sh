exec=$(basename *.cc .cc)
echo "Found $exec.cc"
echo "Will run ./$exec ..."
./$exec > output.txt
diff -s expected.txt output.txt
