#!/bin/bash

#if [ $# -lt 1]; then
#  echo "Usage: $0 <test_data>"
#  exit 1;
#fi

#TESTFILE=data/words-prepped.txt
TESTFILE=data/titles-large.txt
#TESTFILE=data/smaller.txt
#TESTFILE=data/titles-small.txt
set -e
make
if [ -f test/main ]; then
  rm test/main
fi
echo "Running java"
#java -jar test/JBlumer.jar $TESTFILE
echo "Running c"
#time bin/main $TESTFILE
echo "Started " `date`
if [ -z "$1" ]; then
  time bin/main $TESTFILE
else
  gdb bin/main -x test/debug.gdb
fi
echo "Finished " `date`
#gdb bin/main <<< "run $TESTFILE"

