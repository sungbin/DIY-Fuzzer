echo "#Test atoi with multiple inputs"

multiple_main="../bin/multiple_runner_main"
PI_dir="../test/inputs"
PO_dir="../bin/test_multiple"

if [ ! -e $PO_dir ]; then
    mkdir -p $PO_dir
fi


# EXECUTE
multiple_main ../bin/test_atoi $PI_dir $PO_dir

