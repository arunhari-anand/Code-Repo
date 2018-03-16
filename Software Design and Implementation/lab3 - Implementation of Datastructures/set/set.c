/*
 * set.c - the set module developed for cs50
 *
 * A set maintains an unordered collection of (key,item) pairs; any given key
 * can only occur in the set once. It starts out empty and grows as the caller
 * inserts new (key,item) pairs. The caller can retrieve items by asking for
 * their key, but cannot remove or update pairs. Items are distinguished
 * by their key.
 *
 * Compiled using class materials provided by Xia Zhou, July, 2017, including
 * bag.c, bagtest.c, and names5.c
 * Arun Anand, July 2017
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"
#include "memory.h"

//local data types
typedef struct setnode {
	void *item;
	char *key;
	struct setnode *next;
} setnode_t;

//global data types
typedef struct set {
	struct setnode *head;
} set_t;

//global functions
/* Create a new (empty) set; return NULL if error. */
set_t *set_new(void)
{
	set_t *set = count_malloc(sizeof(set_t));

	if (set == NULL) {
		return NULL;
	} else {
		set->head = NULL;
		return set;
	}
}

/* Insert item, identified by a key (string), into the given set.
 * The key string is copied for use by the set.
 * Return false if key exists, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool set_insert(set_t *set, const char *key, void *item)
{
	if (set != NULL && item != NULL && key != NULL && set_find(set, key) == NULL) {
		setnode_t *new = count_malloc(sizeof(setnode_t));

		if (new != NULL) {
			new->item = item;
			new->key = malloc(sizeof(char) * strlen(key));
			strcpy(new->key, key); //makes a local copy of the string passed
			new->next = set->head;
			set->head = new;
			return true;
		}
		return false;
	}
	return false;
}

/* Return the item associated with the given key;
 * return NULL if set is NULL, key is NULL, or key is not found.
 */
void *set_find(set_t *set, const char *key)
{
	if (set == NULL){
		return NULL;
	}
	else if (set->head == NULL){
		return NULL;
	}
	else if (key == NULL){
		return NULL;
	}
	else{
		for (struct setnode *node = set->head; node != NULL; node = node->next) {
			if (strcmp((node->key), key) == 0){
				return node->item;
			}
		}
		return NULL;
	}
}

/* Print the whole set; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL set.
 * Print a set with no items if NULL itemprint.
*/
void set_print(set_t *set, FILE *fp,
	void (*itemprint)(FILE *fp, const char *key, void *item) )
	{
		if (fp != NULL) {
			if (set != NULL) {
				fputc('{', fp);
				for (struct setnode *node = set->head; node != NULL; node = node->next) {
					// print this node
					if (itemprint != NULL) {  // print the node's item
					(*itemprint)(fp, node->key, node->item);
					fputc(';', fp);
				}
			}
			fputs("}\n", fp);
		} else {
			fputs("(null)\n", fp);
		}
	}
}

/* Iterate over all items in the set, in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If set==NULL or itemfunc==NULL, do nothing.
 */
void set_iterate(set_t *set, void *arg,
	void (*itemfunc)(void *arg, const char *key, void *item) )
	{
		if (set != NULL && itemfunc != NULL){
			for (struct setnode *node = set->head; node != NULL; node = node->next) {
				(*itemfunc)(arg, node->key, node->item);
			}
		}
	}

	/* Delete the whole set; ignore NULL set.
	 * Provide a function that will delete each item (may be NULL).
	 */
	void set_delete(set_t *set, void (*itemdelete)(void *item) )
	{
		if (set != NULL) {
			for (struct setnode *node = set->head; node != NULL; ) {
				if (itemdelete != NULL) {	    // if possible...
					(*itemdelete)(node->item);	    // delete node's item
				}
				struct setnode *next = node->next;
				count_free(node->key);
				count_free(node);
				node = next;
			}

			count_free(set);
		}
	}
