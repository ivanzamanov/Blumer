#!/bin/bash

#if [ $# -lt 1]; then
#  echo "Usage: $0 <test_data>"
#  exit 1;
#fi

TESTFILE=data/titles-large.txt
set -e
make
if [ -f test/main ]; then
  rm test/main
fi
cp bin/main test
pushd test
echo "Running java"
#time java -jar JBlumer.jar $TESTFILE -Xmx=4g
echo "Running c"
time ./main $TESTFILE
#./main $TESTFILE
#gdb ./main -x debug.gdb
cd ..

