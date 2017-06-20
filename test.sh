#!/bin/bash
############################################
#Change this to the current assignment name:
SRC_NAME=src
SOL_NAME=sol
TESTS_NAME=tests
BIN_NAME=out
TEST_OUTPUT=output
############################################

SRC_FDR=./$SRC_NAME
SOL_FDR=./$SOL_NAME
TESTS_FDR=./$TESTS_NAME

BIN_FDR=./$BIN_NAME
TEST_OUTPUT_FDR=./$TEST_OUTPUT
FLAG=0

rm -rf $BIN_FDR
mkdir $BIN_FDR
rm -rf $TEST_OUTPUT_FDR
mkdir $TEST_OUTPUT_FDR

for PROGNAME in $@ 
do
  SRC=$SRC_FDR/$PROGNAME.cc
  SOL=$SOL_FDR/$PROGNAME
  MY_SOL=$BIN_FDR/$PROGNAME
  TEST=$TESTS_FDR
  TEST_RES=$TEST_OUTPUT_FDR
  COMPILE= g++ -Wall $SRC -o $MY_SOL
  TNAME=_test0

  $COMPILE


## Add more tests by changing number from 9 to whatever ##
  echo
  echo '~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Testing '$PROGNAME' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~' 
  echo
  echo '~~~~~~ Running tests: ~~~~~~'
  for i in {0..9}

## ---------------------------------------------------- ##
  do
    if [ -f $TESTS_FDR/$PROGNAME$TNAME$i.in ]; then
      echo 'Running Test0'$i':'
      $MY_SOL <$TESTS_FDR/$PROGNAME$TNAME$i.in >$TEST_RES/res0$i.out
      $SOL <$TESTS_FDR/$PROGNAME$TNAME$i.in >$TEST_RES/ressol0$i.out

      if [[ $(diff $TEST_RES/res0$i.out $TEST_RES/ressol0$i.out | head -c1 | wc -c) -ne 0 ]]; then
	FLAG=1        
	echo 'Test Result:'
        echo 'Diff '$TNAME$i '('res0$i.out, ressol0$i.out'):'
        diff $TEST_RES/res0$i.out $TEST_RES/ressol0$i.out
      else
        echo "Test Passed Successfully!"
      fi
    fi
  
  done
 
  echo '~~~~~~~~~~~~~~~~~~~~~ Running Valgrind for '$PROGNAME '~~~~~~~~~~~~~~~~~~~~~'
  echo
  echo "~~~~~ Running Valgrind ~~~~~"

## Add more tests by changing number from 9 to whatever ##

  for i in {0..9}

## ---------------------------------------------------- ##
  do
    if [[ $(ls $TESTS_NAME | grep $PROGNAME$TNAME$i.in | head -c1 | wc -c) -ne 0 ]]; then
   
      valgrind $MY_SOL <$TESTS_FDR/$PROGNAME$TNAME$i.in >$TEST_RES/valgrind_$PROGNAME'_'$i.out 2>&1
  
    fi
    if [[ $(grep -s -A 1 'SUMMARY:' $TEST_RES/valgrind_$PROGNAME'_'$i.out | head -c1 | wc -c) -ne 0 ]]; then  
      echo 
      echo valgrind$i.out':'
      echo 	
      grep -s -A 1 'SUMMARY:' $TEST_RES/valgrind_$PROGNAME'_'$i.out
    fi 
  done
 echo '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
done

#delete output folder if No issues in any test
rm -rf $BIN_FDR
if [ $FLAG -eq 0 ]; then
  echo
  echo 'All tests completed successfuly. Deleting output folder...'
  rm -rf $TEST_RES  
else
  echo
  echo 'See results in '$TEST_OUTPUT 'folder'
fi
echo "Finished"

