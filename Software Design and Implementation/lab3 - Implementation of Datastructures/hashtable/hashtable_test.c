/*
 * hashtable_test.c - header file for CS50 'hashtable' module
 *
 * Tests all six functions of the hashtable module, indcluing
 * error cases
 *
 * Compiled using class materials provided by Xia Zhou, July, 2017
 * Arun Anand, July 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable.h"

//A struct to test the hashtable module
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
  //test of hashtable_new
  hashtable_t *ht = hashtable_new(3);

  if (ht == NULL){
    fprintf(stderr, "hashtable_new failed\n");
    exit(1);
  }

  //test of hshtable_insert with error cases as well
  printf("\ntesting hashtable_insert:\n");
  int item1 = 1947949867;
  int item2 = 234698087;
  int item3 = 34234;
  int item4 = 4798763;

  const char *key1 = "Key1";
  const char *key2 = "Key2";
  const char *key3 = "Key3";
  const char *key4 = "Key4";

  hashtable_insert(ht, key1, &item1);
  hashtable_insert(ht, key2, &item2);
  hashtable_insert(ht, key3, &item3);
  hashtable_insert(ht, key4, &item4);

  // test with null set, null item, null key
  hashtable_insert(NULL, NULL, NULL);
  hashtable_insert(ht, NULL, NULL);
  //printf("%s", x ? "true" : "false");

  //test of hashtable_find with error cases (NULL parameters)
  char *bad = "bad";
  printf("Testing a valid key: \n");
  int *t1 = hashtable_find(ht, key1);
  printf("Found in hashtable: %d\n", *t1 );
  printf("Testing an invalid key: \n");
  t1 = hashtable_find(ht, bad);
  if (t1 == NULL){
    printf("Key not found!\n");
  }
  else{
    printf("Error!\n");
  }

  //tests hashtable_print, hashtable_iterate and hashtable_delete
  int inc = 5;
  printf("Printing the hashtable \n");
  hashtable_print(ht, stdout, int_print);
  hashtable_print(NULL, NULL, NULL);
  printf("\nIncrementing the hashtable  by 5\n");
  hashtable_iterate(ht, &inc, int_add);
  hashtable_iterate(NULL, NULL, NULL);
  hashtable_print(ht, stdout, int_print);
  printf("\nDeleting the hashtable\n");
  hashtable_delete(ht, int_delete);
  hashtable_delete(NULL, NULL);

  //tests the module with structs as items to ensure that itemdelete works
  ht = hashtable_new(2);
  struct int_storage *str1 = malloc(sizeof(struct int_storage));
  struct int_storage *str2 = malloc(sizeof(struct int_storage));
  struct int_storage *str3 = malloc(sizeof(struct int_storage));
  str1->value = 1;
  str2->value = 2;
  str3->value = 3;
  hashtable_insert(ht, key1, str1);
  hashtable_insert(ht, key2, str2);
  hashtable_insert(ht, key3, str3);
  printf("Testing the hashtable with structs as items \n");
  hashtable_print(ht, stdout, struct_print);
  hashtable_delete(ht, str_delete);
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
* frees the parameter item
*/
static void str_delete(void *item){
  if (item != NULL){
    free(item);
  }
}
