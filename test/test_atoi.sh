gcc -o test_atoi test_atoi.c
cd ../src/
make clean
make
cd ../test/
echo "" > ./result.txt


# test
../src/fuzzer < "../test/test_atoi 10"
../src/fuzzer < "../test/test_atoi 20"
../src/fuzzer < "../test/test_atoi abc"
../src/fuzzer < "../test/test_atoi 30"
../src/fuzzer "../test/test_atoi "

# result
mv ./result.txt ./test_atoi_result.txt
