echo "#Test atoi with multiple inputs"

multiple_main="../bin/main"
PI_dir="../test/inputs_three"
PO_dir="../bin/triangle_result"

# EXECUTE
../bin/main ../bin/test_triangle $PI_dir $PO_dir -bcov

