echo "#Test timeout"

cd ../bin/
T1RE="1 0x4 0"
T1RR=$(./fuzzer ./test_timeout ../test/inputs/test_timeout_input1.txt ./output2.txt)
sleep 1

T1PE="sleep 11 secconds..."
T1PR=$(<./output2.txt)
cd ../test/

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

