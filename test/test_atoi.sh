echo "#Test atoi"
if [ -e "../bin/output1.txt" ]; then
    rm ../bin/output1.txt
fi

T1RE="1 0 0"
T1RR=$(../bin/main ../bin/test_atoi ../test/inputs/test_atoi_input1.txt ../bin/output1.txt)

T1PE="10"
T1PR=$(<../bin/output1.txt)

if [ "$T1RE" == "$T1RR" ]
then
    echo "Return Value: Pass (Expected: $T1RE, Actual: $T1RR)"
else
    echo "Return Value: Fail (Expected: $T1RE, Actual: $T1RR)"
fi

if [ "$T1PE" == "$T1PR" ]
then
    echo "Program Output: Pass (Expected: $T1PE, Actual: $T1PR)"
else
    echo "Program Output: Fail (Expected: $T1PE, Actual: $T1PR)"
fi

