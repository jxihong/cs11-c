#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "memcheck.h"

void random_initialize(int *cells, int size);
void print_board(int *cells, int size);
void update(int *cells, int *nextCells, int size);

/*
 * copy: copies the contents of arr2 into arr1
 * arguments: arr1: first array to be copied into
 *            arr2: second array to be copied from
 *            size: size of both arrays
 */
void copy(int *arr1, int *arr2, int size) {
  int i ;
  
  for (i = 0; i < size; i++) {
    arr1[i] = arr2[i];
  }
}

int main(int argc, const char* argv[]) {
  int i, count, generations;
  int *cells;
  int *nextCells;

  /* checks to make sure user has 3 inputs */
  if (argc != 3) {
    fprintf(stderr, "Usage: %s [cells] [generations]\n", argv[0]);
    exit(1);
  }
  
  count = atoi(argv[1]); /* number of cells in board */
  generations = atoi(argv[2]); /* number of generations to compute */
  
  /* initializes array of size count to 0's */
  cells = (int *) calloc(count, sizeof(int));
  nextCells = (int *) calloc(count, sizeof(int));

  /* checks to make sure memory is allocated properly */
  if (cells == NULL || nextCells == NULL) {
    fprintf(stderr, "Error allocating memory");
    exit(1);
  }
  
  random_initialize(cells, count);
  print_board(cells, count);

  for (i = 0; i < generations; i++) {
    /* computes new board based on update rule, and prints it */
    update(cells, nextCells, count);
    print_board(cells, count);
  }
  
  free(cells);
  free(nextCells);

  print_memory_leaks();
  return 0;
}

/*
 * random_initialize: sets each cell in a board to a random integer 0 or 1
 * arguments: cells: board to be initialized
 *            size: number of cells in the board
 */
void random_initialize(int *cells, int size) {
  int randCell; /* random number 0 or 1 */
  int i;

  srand(time(NULL));
  
  for (i = 0; i < size; i++) {
    /* sets contents of each cell to random number */
    randCell = rand() % 2;
    cells[i] = randCell;
  }  
}

/* 
 * print_board: prints the contents of the board: "." = 0, and "*" = 1
 * arguments: cells: board to be printed
 *            size: number of cells in the board
 */
void print_board(int *cells, int size) {
  int i;
  
  for (i = 0; i < size; i++) {
    /* prints cell "." for 0, and "*" for 1 */
    printf("%s", (cells[i] == 0) ? "." : "*");
  }
  printf("\n");
  
}

/*
 * update: computes the next generation of board based on the update rule:
 *         1. if the current cell is empty, and one of the two adjacent cells 
 *            is full (but not both), set the current cell to be full.
 *         2. Otherwise set the current cell to be empty.
 * arguments: cells: intial board to be updated
 *            nextCells: next board generation to be computed
 *            size: number of cells in the board
 */
void update(int *cells, int *nextCells, int size) {
  int i;
  
  for (i = 1; i < size - 1; i++) {
    /* updates cell in new board based on update rule */
    nextCells[i] = !(cells[i]) && (cells[i - 1] + cells[i + 1] == 1);
    /*
    if ((cells[i] == 0) && (cells[i - 1] + cells[i + 1] == 1)) {
      nextCells[i] = 1;
    }
    else {
      nextCells[i] = 0;
    }
    */
  }
  
  /* copies new board into initial one */
  copy(cells, nextCells, size);
}
