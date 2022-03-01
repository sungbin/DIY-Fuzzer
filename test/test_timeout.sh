echo "#Test timeout"
if [ -e "../bin/return_output2.txt" ]; then
    rm ../bin/return_output2.txt
fi
if [ -e "../bin/program_output2.txt" ]; then
    rm ../bin/program_output2.txt
fi

# Return Value Test
T2RE="./expected_outputs/return_output2.txt"
T2RR="../bin/return_output2.txt"
../bin/main ../bin/test_timeout ../test/inputs/test_input2.txt ../bin/output2.txt > $T2RR

# Program Test
T2PE="./expected_outputs/program_output2.txt"
T2PR="../bin/output2.txt"

diff $T2RE $T2RR
if [ $? -eq 0 ]
then
	echo "Return Output: Pass"
	# (Expected: $T2RE), Actual: $T2RR)
else
	echo "Return Output: Fail"
	# (Expected: $T2RE), Actual: $T2RR)
fi


diff $T2PE $T2PR
if [ $? -eq 0 ]
then
	echo "Program Output: Pass"
	# (Expected: $T2PE), Actual: $T2PR)
else
	echo "Program Output: Fail"
	# (Expected: $T2PE, Actual: $T2PR)
fi
