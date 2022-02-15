gcc -o test_timeout test_timeout.c

cd ../src/
make clean
make
cd ../test/
echo "" > ./result.txt


# test
../src/fuzzer ../test/test_timeout 5
../src/fuzzer ../test/test_timeout 10
../src/fuzzer ../test/test_timeout -5

# result
mv ./result.txt ./test_timeout_result.txt
