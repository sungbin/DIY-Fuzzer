multiple_main="../bin/multiple_runner_main"
PI_dir="../test/bug_jsons"
PO_dir="../bin/test_mutiple_out"

echo "#Test jsmn with multiple inputs"

cd ..
make clean
make jsondump
cd test

cd /Users/sungbin/Desktop/jsmn
make clean
export ASAN_OPTIONS=detect_leaks=0
CFLAGS="-O3 -g -fsanitize=address" LDFLAGS="-fsanitize=address" make jsondump
cd -
cp /Users/sungbin/Desktop/jsmn/jsondump ../bin/


if [ ! -e $PO_dir ]; then
    mkdir -p $PO_dir
fi

$multiple_main ../bin/jsondump $PI_dir $PO_dir
