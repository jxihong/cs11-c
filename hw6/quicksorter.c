#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "memcheck.h"
#include "linked_list.h"

/*
 * quicksort: sorts a linked-list using the quicksort algorithm
 * arguments: list: pointer to the head of a linked_list to sort
 * return: pointer to head of new sorted linked_list
 */
node * quicksort(node *list) {
  node *pivot; /* pointer to first node */
  
  node *smaller = NULL; /* pointer to list smaller than pivot */
  node *larger = NULL; /* pointer to list larger than pivot */ 
  node *curr; /* pointer to current node in original list */
  
  node *sorted_larger; /* pointer to sorted larger list */
  node *sorted_smaller; /* pointer to sorted smaller list */
  node *sorted; /* pointer to return, fully-sorted list */

  pivot = list; /* set pivot to head of original list */
  if (!pivot || !pivot->next) {
    return copy_list(list);
  }
  
  /* add node to smaller list if current node is smaller than pivot; else,
   * add to larger list 
   */

  for (curr = list->next; curr != NULL; curr = curr->next) {
    if (curr->data < pivot->data) {
      smaller = create_node(curr->data, smaller);
    }
    else {
      larger = create_node(curr->data, larger);
    }
  }    
  
  /* recursively sorts two sub-lists */
  sorted_smaller = quicksort(smaller); 
  sorted_larger = quicksort(larger);

  /* adds pivot to head of larger list */
  sorted_larger = create_node(pivot->data, sorted_larger);

  free_list(smaller);
  free_list(larger);
  
  /* combines two sorted sub-lists */
  sorted = append_lists(sorted_smaller, sorted_larger);
  
  free_list(sorted_smaller);
  free_list(sorted_larger);
  
  return sorted;
}
      

int main(int argc, const char* argv[]) {
  int i;
  int quiet = 0; /* flag for quiet mode */

  node *sorted_list; /* sorted list */
  node *list = NULL; /* original list */
  
  for (i = 1; i < argc; i++) {
    /* checks if input is '-q' for quiet mode */
    if (strcmp(argv[i], "-q") == 0) {
      quiet = 1;
    }
    else {
      /* add node to head of list */
      list = create_node(atoi(argv[i]), list);
    }
  }
  
  /* usage message if the list has no elements */
  if (!list) {
    fprintf(stderr, "usage: %s [-q] number 1 [number 2] ... \n", argv[0]);
    return -1;
  }

  sorted_list = quicksort(list);
  
  /* makes sure list sorted correctly */
  assert(is_sorted(sorted_list));

  if (!quiet) {
    print_list(sorted_list);
  }
  
  free_list(list);
  free_list(sorted_list);

  print_memory_leaks();
  
  return 0;
}
