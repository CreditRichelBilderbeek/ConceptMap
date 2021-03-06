#!/bin/bash

cpp_files=`ls *.cpp | egrep -v "^.*_test\.cpp$"`
h_files=`ls *.h`

echo $cpp_files
echo $h_files


./oclint-0.10.3/bin/oclint -o oclint.log \
  -disable-rule ShortVariableName \
  $cpp_files \
  $h_files \
  -- \
  -c -std=c++14 -fPIC \
  -I../RibiClasses/CppContainer \
  -I../RibiClasses/CppCounter \
  -I./CppDnaSequence \
  -I./CppFastaFile \
  -I../RibiClasses/CppFileIo \
  -I./CppMusic \
  -I./CppNewick \
  -I./CppPolarCoordinat \
  -I./CppRibiRinside \
  -I../RibiClasses/CppRibiRegex \
  -I./CppTestTimer \
  -I../RibiClasses/CppTrace \
  -I./CppUnits \
  -I../RibiClasses/CppXml \
  -I../BoostGraphTutorial/BoostGraphTutorial \
  -I/usr/include/c++/5 \
  -I/usr/include/x86_64-linux-gnu/c++/5 \
  -I/usr/include/qt4 \
  -I/usr/include/qt4/QtCore

cat oclint.log

# Will be 0 if success
# Will be 1 if fail
fail=`egrep "Compiler Errors" oclint.log | wc -l`

if [ $fail -eq 1 ]; 
then
  echo "OCLint: Compiler error"
  exit 1
else
  echo "OCLint: OK"
fi

# Will be 1 if success
# Will be 0 if fail
success=`egrep "FilesWithViolations=0 P1=0 P2=0 P3=0" oclint.log | wc -l`

if [ $success -eq 1 ]; 
then
  echo "OCLint: OK"
else
  echo "OCLint: Fail"
  exit 1
fi