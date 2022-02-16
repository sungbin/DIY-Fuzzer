echo "" > ./result.txt

# test
../bin/fuzzer ../test/test_atoi ../test/test_atoi_input1.txt # 10
# ../bin/fuzzer ../test/test_atoi ../test/test_atoi_input2.txt # abc
# ../bin/fuzzer ../test/test_atoi ../test/test_atoi_input3.txt # (blank)

# result
mv ./result.txt ./test_atoi_result.txt
