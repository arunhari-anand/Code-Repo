#!/bin/bash
#
#regress.sh - performs regression testing of a shell script program
#
#usage: regress.sh dirname testfile0 testfile1...
#arguments: dirname - the directory containing the test results
#testfile? - testfiles that run the shell script in question
#
#input: none
#output: prints where the test results are Saved
#creates a directory to save all the newly run testresults
#prints out the differences between dirname and the newly created directory
#
#Arun Anand, July 2017

#checks to see if atleast two arguments have been included
#exits 1 if error
if [ $# -lt 2 ]; then
  echo 1>&2 Usage: regress.sh dirname testfile0
  exit 1
fi

#checks to see that if dirname exists, then it is a directory
#exits 2 if not
if [ -e "$1" ]; then
[ -d "$1" ] || (echo 1>&2 "$1 is a file, not a directory!"; exit 2)
if [ ! $? -eq 0 ]; then
  exit 2
fi
fi


#loops through the files and checks to see if they are all regular and readable
#exits 3 if one of them is irregular or unreadable
for i in ${@:2}; do
  if [ ! -e $i ]; then
    echo 1>&2 One of the files does not exist!
    exit 3
  fi
  if [ ! -f "$i" ]; then
    echo 1>&2 "$i is not regular!"
    exit 3
  fi
  if [ ! -r "$i" ]; then
    echo 1>&2 "$i is not readable!"
    exit 3
  fi
done


filename=`date '+%Y%m%d.%H%M%S'`
mkdir "$filename"


#run each testfile and save the outputs to the relevant filenames
for i in ${@:2}; do
  testname=`basename "$i"`
  less $i > "$filename/$testname.test"
  bash $i > "$filename/$testname.stdout" 2>"$filename/$testname.stderr" </dev/null
  echo $? > "$filename/$i.status"
done

#if the directory dirname does exist, then results are saved in a new file
#differences between the files are then printed out
#if dirname does exist then the directory is renamed to dirname
if [ -d "$1" ]; then
  echo "Saved test results in $filename"
  echo "Comparing $filename with $1"
  diff -q "$1" "$filename" || exit 4
  echo "no differences"
else
  mv "$filename" "$1"
  if [ ! $? -eq 0 ]; then
    echo "failed to save test results in $1"
    echo "results remain in $filename"
  fi
  echo "Saved test results in $1"
fi

exit 0
