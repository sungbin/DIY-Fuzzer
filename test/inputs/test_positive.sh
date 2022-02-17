gcc -o test_positive test_positive.c

cd ../src/
make clean
make
cd ../test/
echo "" > ./result.txt


# test
../src/fuzzer ../test/test_positive 5
../src/fuzzer ../test/test_positive 10
../src/fuzzer ../test/test_positive -5

# result
mv ./result.txt ./test_positive_result.txt
