/*
 * counters.c - the counters module developed for cs50
 *
 *A counter set is a set of counters, each distinguished by an integer key.
 * It’s a set - each key can only occur once in the set - but instead of
 * storing (key,item) pairs, it tracks a counter for each key.
 * It starts empty. Each time counters_add is called on a given key,
 * that key’s counter is incremented. The current counter value can be
 * retrieved by asking for the relevant key.
 *
 * Compiled using class materials provided by Xia Zhou, July, 2017 including
 * bag.c, bagtest.c and names5.c
 * Arun Anand, July 2017
 */
#include <stdio.h>
#include <stdlib.h>
#include "counters.h"
#include "memory.h"

//local data types
typedef struct countersnode {
  int count;
  int key;
  struct countersnode *next;
} countersnode_t;

//global data types
typedef struct counters {
  struct countersnode *head;
} counters_t;

//global functions
/* Create a new (empty) counter structure; return NULL if error. */
counters_t *counters_new(void)
{
  counters_t *counters = count_malloc(sizeof(counters_t));

  if (counters == NULL) {
    return NULL;
  } else {
    counters->head = NULL;
    return counters;
  }
}

/* Increment the counter indicated by key; key must be >= 0.
 * If the key does not yet exist, create a counter for it and initialize to 1.
 * Ignore if ctrs is NULL or key is negative.
 * Return the new value of the counter related to the inserted key
 */
int counters_add(counters_t *ctrs, const int key)
{
  if (ctrs != NULL && key>= 0) {
    if (counters_get(ctrs, key) == 0){
      countersnode_t *new = count_malloc(sizeof(countersnode_t));

      if (new != NULL) {
        new->count = 1;
        new->key = key;
        new->next = ctrs->head;
        ctrs->head = new;
        return 1;
      }
    }
    else {
      for (struct countersnode *node = ctrs->head; node != NULL; node = node->next) {
        if (node->key == key){
          return ++(node->count);
        }
      }
    }
  }
  return 0;
}

/* Return current value of counter associated with the given key;
 * return 0 if ctrs is NULL or if key is not found.
 */
int counters_get(counters_t *ctrs, const int key)
{
  if (ctrs == NULL || key<0){
    return 0;
  }
  else if (ctrs->head == NULL){
    return 0;
  }
  else{
    //for loop used to traverse the set of countersnodes
    for (struct countersnode *node = ctrs->head; node != NULL; node = node->next) {
      if (node->key == key){
        return (node->count);
      }
    }
    return 0;
  }
}

/* Set the current value of counter associated with the given key;
 * If the key does not yet exist, create a counter for it and initialize to
 * the given value. Ignore if ctrs is NULL, if key < 0, or count < 0.
 */
void counters_set(counters_t *ctrs, const int key, int count)
{
  if (ctrs != NULL && key>= 0 && count>=0) {
    if (counters_get(ctrs, key) == 0){
      counters_add(ctrs, key);
      counters_set(ctrs, key, count);
    }
    else {
      for (struct countersnode *node = ctrs->head; node != NULL; node = node->next) {
        if (node->key == key){
          node->count = count;
        }
      }
    }
  }
  return;
}

/* Print all counters; provide the output file.
 * Ignore if NULL fp. Print (null) if NULL ctrs.
 */
void counters_print(counters_t *ctrs, FILE *fp)
  {
    if (fp != NULL) {
      if (ctrs != NULL) {
        fputc('{', fp);
        for (struct countersnode *node = ctrs->head; node != NULL; node = node->next) {

          fprintf(fp, "key: %d, count: %d; ", node->key, node->count);

      }
      fputs("}\n", fp);
    } else {
      fputs("(null)\n", fp);
    }
  }
}

/* Iterate over all counters in the set (in undefined order):
 * call itemfunc for each item, with (arg, key, count).
 * If ctrs==NULL or itemfunc==NULL, do nothing.
 */
void counters_iterate(counters_t *ctrs, void *arg,
  void (*itemfunc)(void *arg, const int key, int count))
  {
    if (ctrs != NULL && itemfunc != NULL){
      for (struct countersnode *node = ctrs->head; node != NULL; node = node->next) {
        (*itemfunc)(arg, node->key, node->count);
      }
    }
  }

  /* Delete the whole counters. ignore NULL ctrs. */
  void counters_delete(counters_t *ctrs)
  {
    if (ctrs != NULL) {
      for (struct countersnode *node = ctrs->head; node != NULL; ) {
				struct countersnode *next = node->next;
				free(node);
				node = next;
			}

      count_free(ctrs);
    }
  }
