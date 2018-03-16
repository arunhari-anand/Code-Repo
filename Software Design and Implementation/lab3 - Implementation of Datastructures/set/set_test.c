/*
 * set_test.c - to test the set_t module
 *
 * This program tests all six functions in set.c and tests all the error cases
 * as well
 *
 * Compiled using class materials provided by Xia Zhou, July, 2017, including
 * bag.c, bagtest.c, and names5.c
 * Arun Anand, July 2017
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

//A struct to test the set
struct int_storage{
  int value;
};

/*
* A function that prints the int passed to it as item
*/
static void int_print (FILE *fp, const char *key, void *item);

/*
* An itemfunc that that adds the int specified as arg to the item
*/
static void int_add (void *arg, const char *key, void *item);

/*
* int_delete is the itemdelete for ints
* It does nothing
*/
static void int_delete(void *item);

/*
*This deletes the struct int_storage
*/
static void str_delete(void *item);

/*
* An "itemprint" function for the struct int_storage
* Prints the stored int
*/
static void struct_print (FILE *fp, const char *key, void *item);

/*
* all the tests are run in the main method
*/
int main()
{
  set_t *set = set_new(); //testing set_new

  if (set == NULL){
    fprintf(stderr, "set_new failed\n");
    exit(1);
  }

  //the next section tests set_insert with a set of string keys and int items
  printf("\ntesting set_insert:\n");
  int item1 = 10;
  int item2 = 20;
  int item3 = 30;
  int item4 = 40;

  const char *key1 = "Key1";
  const char *key2 = "Key2";
  const char *key3 = "Key3";
  const char *key4 = "Key4";

  set_insert(set, key1, &item1);
  set_insert(set, key2, &item2);
  set_insert(set, key3, &item3);
  set_insert(set, key4, &item4);

  // test with null set, null item, null key
  set_insert(NULL, NULL, NULL);
  set_insert(set, NULL, NULL);

  //testing set_find with both valid and invalid keys
  printf("Searching for a key that has not been inserted into the set: \n");
  char *bad = "bad";
  int *t1 = set_find(set, bad);
  if (t1 == NULL){
    printf("Key not found!\n");
  }
  else{
    printf("Error!\n");
  }

  printf("Searching for a valid key:\n");
  t1 = set_find(set, key1);
  if (t1 != NULL){
    printf("Key found, item = %d\n", *t1);
  }
  else{
    printf("Error!\n");
  }

  //testing set_print, set_iterate and set_delete
  int inc = 5;
  printf("printing the set\n");
  set_print(set, stdout, int_print);
  set_print(set, stdout, NULL);
  printf("\nadding 5 to the set\n");
  set_iterate(set, &inc, int_add);
  set_iterate(set, &inc, NULL);
  set_print(set, stdout, int_print);
  printf("deleting the set\n");
  set_delete(set, int_delete);

  //this next section tests set with a struct - int_storage.
  //This is to ensure that set_delete and itemdelete work properly
  set = set_new();
  struct int_storage *str1 = malloc(sizeof(struct int_storage));
  struct int_storage *str2 = malloc(sizeof(struct int_storage));
  struct int_storage *str3 = malloc(sizeof(struct int_storage));
  str1->value = 1;
  str2->value = 2;
  str3->value = 3;
  set_insert(set, key1, str1);
  set_insert(set, key2, str2);
  set_insert(set, key3, str3);
  printf("Testing a set with structs in it as items:\n");
  set_print(set, stdout, struct_print);
  set_delete(NULL, NULL);
  set_delete(set, str_delete);
}

/*
* A function that prints the int passed to it as item
*/
static void int_print (FILE *fp, const char *key, void *item)
{
  int *i = item;
  fprintf(fp, "Key: %s, Int: %d", key, *i);
}

/*
* An "itemprint" function for the struct int_storage
* Prints the stored int
*/
static void struct_print (FILE *fp, const char *key, void *item)
{
  struct int_storage *i = item;
  fprintf(fp, "Key: %s, Int: %d", key, i->value);
}

/*
* An itemfunc that that adds the int specified as arg to the item
*/
static void int_add (void *arg, const char *key, void *item)
{
  int *i = item;
  int *a = arg;
  *i = *a + *i;
}

/*
* int_delete is the itemdelete for ints
* It does nothing
*/
static void int_delete(void *item){}

/*
*This deletes the struct int_storage
*/
static void str_delete(void *item){
  if (item){
    free(item);
  }
}
