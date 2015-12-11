#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_NUMBERS 32

/* 
 * swap: swaps two elements in an array given their indices 
 * arguments: numbers[]: array of integers
 *            index1: int representing the index of first element 
 *                    to be swapped
 *            index2: int representing the index of second element
 */
void swap(int numbers[], int index1, int index2) {
  int temp; /* temporary variable to store smallest element when swapping */
  
  temp = numbers[index2];
  numbers[index2] = numbers[index1];
  numbers[index1] = temp;
}

/*
 * bubble_sort: sorts elements in an array by swapping elements repeatedly
 *              that are out of order
 * arguments: numbers[]: array of integers to be sorted
 *            num_elements: number of elements in array to be sorted
 */
void bubble_sort(int numbers[], int num_elements) {
  int swapped; /* flag for whether a swap occured */
  
  int i;
  /* Continue swapping while there are elements that are out of order */
  do {
    swapped = 0; 
    /* 
     * If some elements are out of order, swap then and tell function
     * that a swap occurred. 
     */
    for (i = 1; i < num_elements; i++) {
      if (numbers[i - 1] > numbers[i]) {
         swap(numbers, i - 1, i);
         swapped = 1;
      }
    }
  } while (swapped);

  /* Checks if the array is properly sorted */
  for (i = 1; i < num_elements; i++) {
    assert(numbers[i] >= numbers[i - 1]);
  }
}


/*
 * min_element_sort: sorts elements in an array by finding min elements
 *                   repeatedly and moving them to the next nonsorted 
 *                   position in array
 * arguments: numbers[]: array of integers to be sorted
 *            num_elements: number of elements in array to be sorted
 */
void min_element_sort(int numbers[], int num_elements) {
  int start, i; 
  
  for (start = 0; start < num_elements; start++) {
    int smallest; /* denotes index for the smallest element in array */
   
    smallest = start;
    /* 
     * Finds the index of the smallest element in the nonsorted part 
     * of the array
     */
    for (i = start; i < num_elements; i++) {
      if (numbers[i] < numbers[smallest]) {
         smallest = i;
      }
    }
    /* 
     * Moves the smallest element in the array to the next nonsorted 
     * position 
     */
    swap(numbers, smallest, start);
  }
  /* Checks if array is properly sorted */
  for (i = 1; i < num_elements; i++) {
    assert(numbers[i] >= numbers[i - 1]);
  }
}

/*
 * print_array: prints each element in the array, one element in each line
 * arguments: arr[]: array of integers to be printed
 *            size: number of elements in the array
 */
void print_array(int arr[], int size) {
  int i;
  
  for (i = 0; i < size; i++) {
    printf("%d\n", arr[i]);
  }
}

int main(int argc, char *argv[]) {
  int bubble = 0; /* flag for whether bubble sort should be used */
  int quiet = 0; /* flag for whether quiet mode should be used */
  
  int num_elements = 0;
  int numbers[MAX_NUMBERS];

  int i;
  for (i = 1; i < argc; i++) {
    /* If there is a '-b' in the console, turn on bubble sort */
    if ((strcmp(argv[i], "-b") == 0)) {
      bubble = 1;
    }
    /* If there is a '-q' in the console, turn on quiet mode */
    else if ((strcmp(argv[i], "-q") == 0)) {
      quiet = 1;
    }
    else {
      /* Read the number into the array */
      if (num_elements < MAX_NUMBERS) {
         numbers[num_elements] = atoi(argv[i]);
      }
      num_elements++;
    }
  }
  
  /* Prints usage message if user inputs too few or too many nubmers */
  if (num_elements <= 0 || num_elements > MAX_NUMBERS) {
    fprintf(stderr, "usage: %s [-b] [-q] number1 [number 2] ..."\
            " (maximum %d numbers)\n", argv[0], MAX_NUMBERS);
    return -1;
  }
  
  if (bubble) {
    bubble_sort(numbers, num_elements);
  }
  else {
    min_element_sort(numbers, num_elements);
  }
  
  if (!quiet) {
    print_array(numbers, num_elements);
  }

  return 0;
}
