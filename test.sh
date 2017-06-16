#!/bin/bash
############################################
#Change this to the current assignment name:
SRC_NAME=src
SOL_NAME=sol
TESTS_NAME=tests
BIN_NAME=out
############################################

SRC_FDR=./$SRC_NAME
SOL_FDR=./$SOL_NAME
TESTS_FDR=./$TESTS_NAME

BIN_FDR=./$BIN_NAME
FLAG=0
rm -rf $BIN_FDR
mkdir $BIN_FDR


for PROGNAME in $@ 
do
  SRC=$SRC_FDR/$PROGNAME.cc
  SOL=$SOL_FDR/$PROGNAME
  MY_SOL=$BIN_FDR/$PROGNAME
  TEST=$TESTS_FDR
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
      $MY_SOL <$TESTS_FDR/$PROGNAME$TNAME$i.in >$BIN_FDR/res0$i.out
      $SOL <$TESTS_FDR/$PROGNAME$TNAME$i.in >$BIN_FDR/ressol0$i.out
    
    # $(diff res0$i.out ressol0$i.out)
      if [[ $(diff $BIN_FDR/res0$i.out $BIN_FDR/ressol0$i.out | head -c1 | wc -c) -ne 0 ]]; then
	$FLAG=1        
	echo 'Test Result:'
        echo 'Diff '$TNAME$i '('res0$i.out, ressol0$i.out'):'
        diff $BIN_FDR/res0$i.out $BIN_FDR/ressol0$i.out
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
   
      valgrind $MY_SOL <$TESTS_FDR/$PROGNAME$TNAME$i.in >$BIN_FDR/valgrind_$PROGNAME'_'$i.out 2>&1
  
    fi
    if [[ $(grep -s -A 1 'SUMMARY:' $BIN_FDR/valgrind_$PROGNAME'_'$i.out | head -c1 | wc -c) -ne 0 ]]; then  
      echo 
      echo valgrind$i.out':'
      echo 	
      grep -s -A 1 'SUMMARY:' $BIN_FDR/valgrind_$PROGNAME'_'$i.out
    fi 
  done
 echo '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
done

#delete output folder if No issues in any test
if [ $FLAG -eq 0 ]; then
  echo
  echo 'All tests completed successfuly. Deleting output folder...'
  rm -rf $BIN_FDR
fi
echo "Finished"

