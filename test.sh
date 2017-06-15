#!/bin/bash

###########################################
#Change this to the current assignment name:

PROG=$1  #No spaces or qutes ""

############################################

SRC=$PROG.cc
SOL=$PROG'sol'
TEST=testing
COMPILE= g++ -Wall $SRC -o $TEST/$PROG
TNAME=_test0
Test_lim=9

$COMPILE
cd $TEST

## Add more tests by changing number from 9 to whatever ##

for i in {0..9}

## ---------------------------------------------------- ##
do
  if [ -f $PROG$TNAME$i.in ]; then
    echo 'Running Test0'$i':'
    ./$PROG <$PROG$TNAME$i.in >res0$i.out
    ./$SOL <$PROG$TNAME$i.in >ressol0$i.out
    # $(diff res0$i.out ressol0$i.out)
    if [[ $(diff res0$i.out ressol0$i.out | head -c1 | wc -c) -ne 0 ]]; then
      echo 'Test Result:'
      echo 'Diff '$TNAME$i '('res0$i.out, ressol0$i.out'):'
      diff res0$i.out ressol0$i.out
    else
      echo "Test Passed Successfully!"
    fi
  fi

done
echo "Running Valgrind:"

## Change the name of the test to match what you want to test: ##
for i in {0..9} 
do
  if [[ $(ls | grep $PROG$TNAME$i.in | head -c1 | wc -c) -ne 0 ]]; then
 
    valgrind ./$PROG <$PROG$TNAME$i.in >valgrind$i.out 2>&1
  
  fi
  if [[ $(grep -s -A 1 'SUMMARY:' valgrind$i.out | head -c1 | wc -c) -ne 0 ]]; then  
    echo 
    echo valgrind$i.out':'
    echo 	
    grep -s -A 1 'SUMMARY:' valgrind$i.out
  fi
done
cd ..
echo "Finished"
 
