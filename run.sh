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
echo "Running java"
#time java -jar test/JBlumer.jar $TESTFILE -Xmx=4g
echo "Running c"
time bin/main $TESTFILE
#./main $TESTFILE
#gdb ./main -x test/debug.gdb

