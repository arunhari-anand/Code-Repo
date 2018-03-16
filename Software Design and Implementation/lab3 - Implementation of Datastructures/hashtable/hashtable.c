/*
 * hashtable.c - implements the hashtable_t module for cs50
 *
 * A hashtable is a set of (key,item) pairs.
 * It acts just like a set, but is far more efficient for large collections.
 *
 * Compiled using class materials provided by Xia Zhou, July, 2017 including
 * bag.c, bagtest.c, and names5.c
 * Arun Anand, July 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable.h"
#include "jhash.h"
#include "memory.h"
#include "set.h"

//global data types
 typedef struct hashtable {
  struct set **table;
  int slots;
} hashtable_t;

/* Create a new (empty) hashtable; return NULL if error. */
hashtable_t *hashtable_new(const int num_slots);

/* Insert item, identified by key (string), into the given hashtable.
 * The key string is copied for use by the hashtable.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item);

/* Return the item associated with the given key;
 * return NULL if hashtable is NULL, key is NULL, key is not found.
 */
void *hashtable_find(hashtable_t *ht, const char *key);

/* Print the whole table; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL ht.
 * Print a table with no items if NULL itemprint.
 */
void hashtable_print(hashtable_t *ht, FILE *fp,
   void (*itemprint)(FILE *fp, const char *key, void *item));

   /* Iterate over all items in the table; in undefined order.
    * Call the given function on each item, with (arg, key, item).
    * If ht==NULL or itemfunc==NULL, do nothing.
    */
void hashtable_iterate(hashtable_t *ht, void *arg,
   void (*itemfunc)(void *arg, const char *key, void *item));

   /* Delete the whole hashtable; ignore NULL ht.
    * Provide a function that will delete each item (may be NULL).
    */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item));

/* Create a new (empty) hashtable; return NULL if error. */
hashtable_t *hashtable_new(const int num_slots)
{
  if (num_slots>=0){
    hashtable_t *ht = count_malloc(sizeof(hashtable_t));

    if (ht == NULL) {
      return NULL;
    }
    else {
      ht->table = count_calloc(num_slots, sizeof(struct set*));
      ht->slots = num_slots;
      return ht;
    }
  }
}

/* Insert item, identified by key (string), into the given hashtable.
 * The key string is copied for use by the hashtable.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item)
{
  if (ht != NULL && item != NULL && key != NULL && hashtable_find(ht, key) == NULL){

    unsigned long index = JenkinsHash(key, ((unsigned long) ht->slots));
    if (ht->table[index]== NULL){
      ht->table[index] = set_new();
    }

    return set_insert(ht->table[index], key, item);
  }
  return false;
}


/* Return the item associated with the given key;
 * return NULL if hashtable is NULL, key is NULL, key is not found.
 */
void *hashtable_find(hashtable_t *ht, const char *key)
{
  if (ht == NULL){
    return NULL;
  }
  else if (ht->table == NULL){
    return NULL;
  }
  else if (key == NULL){
    return NULL;
  }
  else{
    unsigned long index = JenkinsHash(key, ((unsigned long) ht->slots));
    return set_find(ht->table[index], key);

  }
}

/* Print the whole table; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL ht.
 * Print a table with no items if NULL itemprint.
 */
void hashtable_print(hashtable_t *ht, FILE *fp,
   void (*itemprint)(FILE *fp, const char *key, void *item))
{
  if (fp != NULL) {
    if (ht != NULL) {

      fputs("\n", fp);
      //traverses the array of hash slots that each stores a set
      for (int i = 0; i <ht->slots; i++) {

        if (itemprint != NULL && ht->table[i] != NULL) {  // print the set's items
        fputs("[", fp);
        set_print(ht->table[i], fp, itemprint);
        fputs("]", fp);
        //fputc(',', fp);
      }

    }


  } else {
    fputs("(null)\n", fp);
  }
}
}

/* Iterate over all items in the table; in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If ht==NULL or itemfunc==NULL, do nothing.
 */
void hashtable_iterate(hashtable_t *ht, void *arg,
   void (*itemfunc)(void *arg, const char *key, void *item) )
{
  if (ht != NULL && itemfunc != NULL){
    for (int i = 0; i <ht->slots; i++) {
      if (ht->table[i] != NULL) {
        set_iterate(ht->table[i], arg, itemfunc);
      }
    }
  }
}

/* Delete the whole hashtable; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
void hashtable_delete(hashtable_t *ht,
  void (*itemdelete)(void *item) )
{
  if (ht != NULL) {
    for (int i = 0; i <ht->slots; i++) {
      if (ht->table[i] != NULL) {		    // if possible...
        set_delete(ht->table[i], itemdelete);   // delete set
      }
    }

    count_free(ht->table);
    count_free(ht);
  }
}
