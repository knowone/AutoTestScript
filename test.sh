#!/bin/bash
SRC_NAME=..
######################  USER MODIFICATIONS HERE  ##########################
  
## Replace .. with path to all source directories.
#Uncomment next line if src files are in AutoTestScript/src/
#SRC_NAME=src

## Name of folder with the school solutions:
SOL_NAME=sol

## Name of folder with all the tests:
TESTS_NAME=tests

## Highest number of tests available
MAX_TEST=9

## If school solution has a postfix after the assignment name i.e. ex4asol
## where sol is a postfix, add that postfix between the ''
## Example: SOL_ADD='sol' (for ex4asol)
SOL_ADD=''

######################  END USER MODIFICATIONS  ##########################
TEST_OUTPUT=output
BIN_NAME=out

SRC_FDR=$SRC_NAME
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
  SRC=$SRC_FDR/$PROGNAME/$PROGNAME.cc
  SOL=$SOL_FDR/$PROGNAME$SOL_ADD ##this is the name of the school solution binary.
			 # improve: Get from user parameters
  MY_SOL=$BIN_FDR/$PROGNAME
  TEST=$TESTS_FDR
  TEST_RES=$TEST_OUTPUT_FDR
  COMPILE= g++ -Wall $SRC -o $MY_SOL
  
  TNAME= ##test file names are in the form ${PROGNAME}_test0$#

  $COMPILE
  echo '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
  echo
  echo
  echo '~~~~~~~~~~~~~~~~~~~~~ Running Valgrind for '$PROGNAME '~~~~~~~~~~~~~~~~~~~~~'
  echo
  echo "     ~~~~~~~~~~~~~~~~~~~~   Running Valgrind:   ~~~~~~~~~~~~~~~~~~~~"

## Add more tests by changing number from 9 to whatever ##

  i=0
  while [ $i -le $MAX_TEST ]

## ---------------------------------------------------- ##
  do
    if [ $i -le 9 ]; then	
	TNAME='_test0'
    else			##Case where # of tests > 9
	TNAME='_test'
    fi
	## Test file name exists in the output directory, so run valgrind on it
    if [[ $(ls $TESTS_NAME | grep $PROGNAME$TNAME$i.in | head -c1 | wc -c) -ne 0 ]]; then
   
      valgrind $MY_SOL <$TESTS_FDR/$PROGNAME$TNAME$i.in >$TEST_RES/valgrind_$PROGNAME'_'$i.out 2>&1
  
    fi
##Search for SUMMARY in valgrind ouput, if exists and valgrind was perfomred (head of file is not empty)
    if [[ $(grep -s -A 1 'SUMMARY:' $TEST_RES/valgrind_$PROGNAME'_'$i.out | head -c1 | wc -c) -ne 0 ]]; then  
      echo 
      echo valgrind$i.out':'
      echo 	
      grep -s -A 1 'SUMMARY:' $TEST_RES/valgrind_$PROGNAME'_'$i.out
    fi
  i=$(( i+1 ))
  done
 echo '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
done

## Add more tests by changing number from 9 to whatever ##
## Improve: get num of tests from user. Default is 9
  echo
  echo '~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Testing Program '$PROGNAME' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~' 
  echo
  echo '         ~~~~~~~~~~~~~~~~~~~~   Running Tests:   ~~~~~~~~~~~~~~~~~~~~'
  echo
  
  i=0
  while [ $i -le $MAX_TEST ]

## ---------------------------------------------------- ##
  do
    if [ $i -le 9 ]; then	
	TNAME='_test0'
    else			##Case where # of tests > 9
	TNAME='_test'
    fi
    if [ -f $TESTS_FDR/$PROGNAME$TNAME$i.in ]; then ##If the test exists do:
      echo 'Running Test0'$i':'
      $MY_SOL <$TESTS_FDR/$PROGNAME$TNAME$i.in >$TEST_RES/res0$i.out	##Run my program
      $SOL <$TESTS_FDR/$PROGNAME$TNAME$i.in >$TEST_RES/ressol0$i.out	##Run solution

      if [[ $(diff $TEST_RES/res0$i.out $TEST_RES/ressol0$i.out | head -c1 | wc -c) -ne 0 ]]; then
	## If diff returned any result it means it found a difference:
	FLAG=1        ## Flag to not delete the test output
	echo 'Test Result:'

	##print the result:
        echo 'Diff '$TNAME$i '('res0$i.out, ressol0$i.out'):'
        diff $TEST_RES/res0$i.out $TEST_RES/ressol0$i.out
      else
        echo "Test Passed Successfully!"
      fi
    fi
  i=$(( i+1 ))
  done
 
 echo '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'

#delete output folder if No issues in any test
rm -rf $BIN_FDR
if [ $FLAG -eq 0 ]; then
  echo
  echo 'All tests completed successfuly. Deleting output folder...'
  rm -rf $TEST_RES  
else
  echo '* Some tests failed :( Scroll up to see the tests differences.'
  echo '** See full test results in '$TEST_OUTPUT 'folder'...
fi
echo "Finished!"


