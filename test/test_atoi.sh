echo "#Test atoi"
if [ -e "../bin/return_output1.txt" ]; then
    rm ../bin/return_output1.txt
fi
if [ -e "../bin/program_output1.txt" ]; then
    rm ../bin/program_output1.txt
fi

# Return Value Test
T1RE="./expected_outputs/return_output1.txt"
T1RR="../bin/return_output1.txt"
../bin/main ../bin/test_atoi ../test/inputs/test_input1.txt ../bin/output1.txt > $T1RR

# Program Test
T1PE="./expected_outputs/program_output1.txt"
T1PR="../bin/output1.txt"

diff $T1RE $T1RR
if [ $? -eq 0 ]
then
	echo "Return Output: Pass"
	# (Expected: $T1RE), Actual: $T1RR)
else
	echo "Return Output: Fail"
	# (Expected: $T1RE), Actual: $T1RR)
fi


diff $T1PE $T1PR
if [ $? -eq 0 ]
then
	echo "Program Output: Pass"
	# (Expected: $T1PE), Actual: $T1PR)
else
	echo "Program Output: Fail"
	# (Expected: $T1PE, Actual: $T1PR)
fi
