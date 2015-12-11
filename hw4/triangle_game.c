#include <stdio.h>
#include "triangle_routines.h"

#define BOARD_SIZE 15 /* number of pegs on board */
#define NMOVES 36 /* number of possible moves */

/* 
 * This array enumerates all the possible moves in the format, 
 * {start, jumps over, end}
 */
int moves[NMOVES][3] =
  {
    { 0,  1,  3},
    { 3,  1,  0},
    { 1,  3,  6},
    { 6,  3,  1},
    { 3,  6, 10},
    {10,  6,  3},
    { 2,  4,  7},
    { 7,  4,  2},
    { 4,  7, 11},
    {11,  7,  4},
    { 5,  8, 12},
    {12,  8,  5},
    { 0,  2,  5},
    { 5,  2,  0},
    { 2,  5,  9},
    { 9,  5,  2},
    { 5,  9, 14},
    {14,  9,  5},
    { 1,  4,  8},
    { 8,  4,  1},
    { 4,  8, 13},
    {13,  8,  4},
    { 3,  7, 12},
    {12,  7,  3},
    { 3,  4,  5},
    { 5,  4,  3},
    { 6,  7,  8},
    { 8,  7,  6},
    { 7,  8,  9},
    { 9,  8,  7},
    {10, 11, 12},
    {12, 11, 10},
    {11, 12, 13},
    {13, 12, 11},
    {12, 13, 14},
    {14, 13, 12}
  };

/* 
 * npegs: return the number of pegs on the board. 
 * arguments: board[]: array representing whether a peg is in a position
 * return: int specifying the number of pegs on the board
 */
int npegs(int board[]) {
  int ret = 0; /* number of pegs */
  int i;
  for (i = 0; i < BOARD_SIZE; i++) {
    /* if peg in position, increment number of pegs */
    if (board[i]) { 
      ret++;
    }
  }
  return ret;
}

/* valid_move: checks if the move is valid on this board,             
 * arguments: board[]: array representing whether a peg is in a position
 *            move[]: array representing the move in format
 *                    {start, jumps over, end}
 * return: 1 if the move is valid, 0 otherwise
 */
int valid_move(int board[], int move[]) {
  int valid = 0;
  int i;
  /* iterates through all possible moves */
  for (i = 0; i < NMOVES; i++) {
    if (moves[i] == move) {
      /* checks if move is possible in reference to current board position */
      if (board[move[0]] && board[move[1]] && !board[move[2]]) { 
        valid = 1;
      }
      else {
        break;
      }
    }
  }

  return valid;
}

/* make_move: make a move on the board.
 * arguments: board[]: array representing whether a peg is in a position
 *            move[]: array representing the move in format
 *                    {start, jumps over, end}
 */
void make_move(int board[], int move[]) {
  int i;
  /* makes sure move is valid */
  if (valid_move(board, move)) {
    for (i = 0; i < 3; i++) {
      /* all positions on board with pegs lose their peg, and vice versa */
      board[move[i]] = !board[move[i]];
    }
  }
}

/* unmake_move: unmake a move on this board.
 * arguments: board[]: array representing whether a peg is in a position
 *            move[]: array representing the move in format
 *                    {start, jumps over, end}
 */
void unmake_move(int board[], int move[]) {
  int i;
  /* makes sure such move can be reversed */
  if (!board[move[0]] && !board[move[1]] && board[move[2]]) {
    for (i = 0; i < 3; i++) {
      board[move[i]] = !board[move[i]];
    }
  }
}

/* 
 * solve: solve the game starting from a board.  
 * arguments: board[]: starting array, with indicators of whether a peg is
 *                     in a position
 * return: 1 if the game can be solved; otherwise return 0. After it is 
 *         solved it will print the boards making up the solution in 
 *         reverse order. 
 */
int solve(int board[]) {
  int i;
  int j;
  int solvable; /* flag for whether board is solvable */
  
  /* base case: only 0 or 1 pegs on board is solvable */
  if (npegs(board) <= 1) {
    triangle_print(board);
    return 1;
  }
  

  /* iterates and makes all possible moves */
  for (i = 0; i < BOARD_SIZE; i++) {
    for (j = 0; j < NMOVES; j++) {
      /*
       * makes a valid move, and checks if board is solvable 
       * from new position 
       */
      if (moves[j][0] == i && valid_move(board, moves[j])) {
        make_move(board, moves[j]);
        /* checks if board after move made is solvable recursively */
        solvable = solve(board);
        /* undoes the move */
        unmake_move(board, moves[j]);
        if (solvable) {
          triangle_print(board);
          return 1;
        }
      }
    }
  }
  return 0;
}

int main() {
  int board[BOARD_SIZE];
  int solvable;

  /* takes initial input of board */
  triangle_input(board);
  solvable = solve(board);

  if (!solvable) {
    printf("No solution exists\n");
  }
  
  return 0;
}
