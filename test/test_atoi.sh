# test

echo "#Test1"
../bin/fuzzer ./test_atoi ../test/inputs/test_atoi_input1.txt ../bin/output1.txt # 10
echo "Expected: 10"
echo "Result: "
cat ../bin/output1.txt # TODO: diff, and print pass
echo ""

echo "#Test2"
../bin/fuzzer ./test_atoi ../test/inputs/test_atoi_input2.txt ../bin/output2.txt # abc
echo "Expected: abc"
echo "Result: "
cat ../bin/output2.txt # TODO: diff, and print pass
echo ""

echo "#Test3"
../bin/fuzzer ./test_atoi ../test/inputs/test_atoi_input3.txt ../bin/output3.txt # (blank)
echo "Expected: (blank)"
echo "Result: "
cat ../bin/output3.txt # TODO: diff, and print pass
