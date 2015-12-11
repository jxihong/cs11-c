/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *
 *       Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"

/*** Hash function. ***/

/* hash: takes in a string and returns a hash index
 * arguments: s: string to be hashed
 * return: int representing hash value from 0 TO NSLOTS
 */
int hash(char *s)
{
  int sum = 0; /* sum of character values */
  for (; *s != '\0'; s++) {
    sum += (int) (*s);
  }
  return sum % NSLOTS;
}


/*** Linked list utilities. ***/

/* create_node: create a single node. 
 * arguments: key: has key
 *            value: value of node
 * return: pointer to created node with key and value
 */
node *create_node(char *key, int value)
{
  node *n; /* new node to be created */
  n = (node *) malloc(sizeof(node)); 
  /* checks memory allocation */
  if (n == NULL) {
    fprintf(stderr, "Error allocating memory.\n");
    exit(1);
  }

  n->key = key;
  n->value = value;
  n->next = NULL;
  return n;
}


/* free_list: Free all the nodes of a linked list. 
 * arguments: list: pointer to list of nodes to be freed
 */
void free_list(node *list)
{
  node *n;
  while (list != NULL) {
    n = list;
    list = list->next;

    free(n->key);
    free(n);
  }
}


/*** Hash table utilities. ***/

/* create_hash_table: create a new hash table.  
 * return: pointer to empty hash table 
 */
hash_table *create_hash_table()
{
  hash_table *ht;
  ht = (hash_table *) malloc(sizeof(hash_table));
  if (ht == NULL) {
    fprintf(stderr, "Error allocating memory.\n");
    exit(1);
  }
  /* slots are initialized to NULL */
  ht->slot = (node**) calloc(NSLOTS, sizeof(node *));
  if (ht->slot == NULL) {
    fprintf(stderr, "Error allocating memory.\n");
  }
  return ht;
}


/* free_has_table: free a hash table. 
 * arguments: ht: pointer to hash table to be freed
 */
void free_hash_table(hash_table *ht)
{
  int i;
  /* frees nodes in list */
  for(i = 0; i < NSLOTS; i++) {
      free_list(ht->slot[i]);
  }
  free(ht->slot); /* frees list itself */
  free(ht);
}


/*
 * get_value: look for a key in the hash table.
 * arguments: ht: pointer to hash table
 *            key: key to look up
 * return: the associated value if there is one. Otherwise, return 0.
 */
int get_value(hash_table *ht, char *key)
{
  node *n; 
 
  n = ht->slot[hash(key)];
  /* node traverses the list under the hash value for key */
  for (n = ht->slot[hash(key)]; n != NULL; n = n->next) {
    if (strcmp(n->key, key) == 0) {
      return n->value;
    }
  }
  return 0; /* key not found */
}


/* 
 * set_value: set the value stored at a key. If key is not in the table,
 *            create a new node with value 'value'.
 * arguments: ht: pointer to hash table
 *            key: key to look up
 *            value: new value to be set to node
 */
void set_value(hash_table *ht, char *key, int value)
{
  node *n;
  
  n = ht->slot[hash(key)];
  /* if hash not found, create a new node */
  if (!n) {
    ht->slot[hash(key)] = create_node(key, value);
    return;
  }
  /* traverses the list indexed by the hash for correct key */
  for (; n != NULL; n = n->next) {
    if (strcmp(n->key, key) == 0) { /* if keys match */
      n->value = value;
      free(key); 
      break;
    }
    if (!n->next) { /* if key is not found, create new node */
      n->next = create_node(key, value);
      break;
    }
  }
}


/* 
 * print_hash_table: print out the contents of the hash table 
 *                   as key/value pairs. 
 * arguments: ht: pointer to hash table to be printed
 */
void print_hash_table(hash_table *ht)
{
  int i;
  node *n;
  for (i = 0; i < NSLOTS; i++) {
    /* prints each key/value pair as 'key value' */
    for (n = ht->slot[i]; n != NULL; n = n->next) {
      printf("%s %d\n", n->key, n->value);
    }
  }
}
