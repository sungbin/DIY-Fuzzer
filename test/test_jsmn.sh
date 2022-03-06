exec="/Users/sungbin/Desktop/jsmn/jsondump"
exec_in="./bug.json"


cd /Users/sungbin/Desktop/jsmn
make clean
export ASAN_OPTIONS=detect_leaks=0
CFLAGS="-O3 -g -fsanitize=address" LDFLAGS="-fsanitize=address" make jsondump
cd -

cd ..
make clean
make
cd -

../bin/main $exec $exec_in ../bin/jsondump_out.txt
cat ../bin/jsondump_out.txt

