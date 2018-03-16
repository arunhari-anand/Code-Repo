/*
 * counters_test.c - tests the counters.c module
 *
 * This program tests all six functions provided by counters.c
 * All error cases are tested as well
 *
 * Compiled using class materials provided by Xia Zhou, July, 2017 including
 * bag.c, bagtest.c and names5.c
 * Arun Anand, July 2017
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "counters.h"

/*
* takes an int pointer arg and adds all the counts together and puts
* the sum into *arg
*/
static void int_add (void *arg, const int key, int count);

/*
* All the testing is done in the main method.
*/
int main()
{
  counters_t *ctrs = counters_new();

  if (ctrs == NULL){
    fprintf(stderr, "set_new failed\n");
    exit(1);
  }

  //test of counters_add with positive and negative numbers with repeated keys
  printf("\ntesting counters_add:\n");
  counters_add(NULL, -89);
  counters_add(ctrs, 0);
  counters_add(ctrs, -1);
  counters_add(ctrs, 1);
  counters_add(ctrs, 0);

  //tests counters_get using valid and invalid keys
  printf("The count associated with key 0 is %d \n", counters_get(ctrs, 0));
  printf("The count associated with key 1 is %d \n", counters_get(ctrs, 1));
  printf("Attempting to get an invalid key: \n");
  int a = counters_get(ctrs, 17982);
  if (a == 0){
    printf("Key not found!\n");
  }
  else{
    printf("error!");
  }

  //tests counters_print with error cases as well
  counters_print(ctrs, stdout);
  counters_print(NULL, NULL);

  //tests counters_set with valid and invalid keys and values.
  //Also uses repetition of keys
  counters_set(ctrs, 0, 5);
  counters_set(ctrs, 1, 10);
  counters_set(ctrs, 2, 15);
  counters_set(ctrs, 3, -15);
  counters_set(ctrs, 0, 20);
  counters_set(NULL, 1, 1);

  counters_print(ctrs, stdout);
  counters_print(NULL, stdout);

  //test of counters_iterate with error cases as well
  int arg = 0;
  counters_iterate(NULL, NULL, NULL);
  counters_iterate(ctrs, &arg, int_add);
  printf("The sum of all the counts is %d\n", arg);

  //test of counters_delete with error case of NULL as well
  printf("Deleting ctrs");
  counters_delete(NULL);
  counters_delete(ctrs);
}

/*
* takes an int pointer arg and adds all the counts together and puts
* the sum into *arg
*/
static void int_add (void *arg, const int key, int count)
{
  int *a = arg;
  *a = *a + count;
}
