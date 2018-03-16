/*
* histo.c     Arun Anand     July 9, 2017
*
* This program takes no command line arguments and makes a 16 bin-histogram
* of the numbers entered in stdin, with dynamically resized bins that are powers
* of 2 in size
*
* method void add(int next_num) finds the appropriate bin of the histogram where
* the next number falls and adds one to that bin
*
* method void redoHistogram(int next_num) takes the next number, resizes the
* histogram bins such that the range is just large enough to accomodate the next
* number, and calls the add method to add the next number to the histogram
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>

int bin_size = 1; // global variable that tracks the bin size
int bins [16] = {0}; // array that holds the actual bins of the histogram
int num_bins = sizeof(bins)/sizeof(bins[0]); // array that holds the actual bins of the histogram; //constant that holds the total number of bins


/*
* this method finds the appropriate bin of the histogram where the next number
* falls and adds one to that index of the array
* The argument next_num is the next number to be added to the histogram
* This method does not return anything
*/
void add (int next_num);

/*
* this number takes the next number, resizes the
* histogram bins such that the range is just large enough to accomodate the next
* number, and calls the add method to add the next number to the histogram
* the argument next_num is the next number to be added to the histogram
* this method does not return anything
*/
void redoHistogram(int next_num);

/*
* The main method keeps accepting numbers from stdin until EOF and calls the add
* method if the number is within the range of the current histogram. If it is not,
* then redoHistogram is called. Then, the method prints the histogram
*/
int main (const int argc, const char *argv[])
{
  int next_num;
  printf("%d bins of size 1 for range [0,%d)\n", num_bins, num_bins);

  //keeps accepting numbers until EOF
  while (scanf("%d", &next_num) == 1){

    //checks for negative numbers
    if (next_num < 0){
      fprintf (stderr, "Numbers entered have to be nonnegative!\n");
      fprintf (stderr, "The negative number entered will be ignored\n");
    }

    //checks if the number falls within the range and if so, calls add
    else if (next_num < num_bins*bin_size){
      add(next_num);
    }

    //the number doesn't fall within the current range, so redoHistogram is called
    else{
      redoHistogram(next_num);
    }
  }

  //prints out the histogram
  int start, end;
  for (int i = 0; i<num_bins; i++){
    start = bin_size*i;
    end = (bin_size*(i+1))-1;
    printf("%s %d %s %d %s %d\n", "[ ", start, ": ", end, "] ", bins[i]);
  }

  return 0;
}

/*
* this method finds the appropriate bin of the histogram where the next number
* falls and adds one to that index of the array
* The argument next_num is the next number to be added to the histogram
* This method does not return anything
*/
void add(int next_num)
{
  //keeps looping through the bins until the right bin is found, and adds one to the bin
  for (int i = 0; i<num_bins; i++){
    if (next_num >= bin_size*i && next_num <= (bin_size * (i+1)-1)){
      bins[i] = bins[i] + 1;
    }
  }
}

/*
* this number takes the next number, resizes the
* histogram bins such that the range is just large enough to accomodate the next
* number, and calls the add method to add the next number to the histogram
* the argument next_num is the next number to be added to the histogram
* this method does not return anything
*/
void redoHistogram (int next_num)
{
  //bin size is doubled until the next number fits in the histogram
  while ((num_bins*bin_size)-1 < next_num){
    bin_size = bin_size * 2;
    printf("%s %d %s %d %s\n", "16 bins of size ", bin_size, " for range [0,", (num_bins*bin_size), ")" );

    //bins are collapsed such that two adjacent bins are combined into one
    for (int i = 0; i <8; i++){
      bins[i] = bins[2*i] + bins[(2*i)+1];
    }
  }

  add (next_num); //the rnage is now large enough, so add is called
}
