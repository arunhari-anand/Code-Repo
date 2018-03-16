#!/bin/bash
#
#shake.sh - searches the set of Shakespeare's sonnets for a keyword and prints
#out the names and first lines of sonnets that contain the keyword
#
#usage shake.sh searchword
#(1 argument - searchword)
#
#input: none
#output: 1 line of output printed per sonnet that contains the searchword
#prints the name of the sonnet, the first line of the sonnet and ellipses at the end
#
#Arun Hari Anand, June 30, 2017

if [ $# -ne 1 ]; then
  echo 1>&2 Usage: shake.sh searchword
  exit 1
fi

cd ~cs50/public_html/Labs/Lab1/sonnets/ ||   `echo 1>&2 Cannot find sonnets directory; exit 2`
for sonnet in *
do
  if grep -q $@ $sonnet
  then
    echo -n "$sonnet "
    echo -n `sed -n '1p' $sonnet`
    echo ...
  fi
done

exit 0
