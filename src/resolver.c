#include <stdio.h>
#include <stdlib.h>

#include "resolver.h"
#include "bittricks.h"

/**
 * The function that get appropriate
 * position in "down" bit vector using board column number
 *
 * @param column the number of column in board
 * @return the number of position in "down" bit vector
 */
static uint32_t get_down_index(uint32_t column) { return column; }

/**
 * The function that get appropriate
 * position in "left" bit vector using board column number
 * and also its row number
 *
 * @param column the number of column in chess board
 * @param row the number of row in chess board
 * @return the number of position in "left" bit vector
 */
static uint32_t get_left_index(uint32_t column, uint32_t row) { return row + column; }

/**
 * The function that get appropriate
 * position in "right" bit vector using board column number,
 * its row number and also size of board
 *
 * @param column the number of column in chess board
 * @param row the number of row in chess board
 * @param size the size of chess board
 * @return the number of position in "right" bit vector
 */
static uint32_t get_right_index(uint32_t column, uint32_t row, uint32_t size) { return size - 1 - row + column; }

/**
 * Function checks if one particular column is not free
 * for placing queen there
 *
 * @param down_position the number of checking column
 * @param down the bit vector that shows vacant and occupied columns
 * @return sign of occupied column
 */
static bool is_nonfree_down(uint32_t down_position, uint32_t down) {
  return down & (1 << down_position);
}

/**
 * Function checks if one particular
 * left diagonal is not free for
 * placing queen there
 *
 * @param left_position the number of checking diagonal in "down" bit vector
 * @param left the bit vector that shows vacant and occupied left diagonal in the board
 * @return sign of occupied left diagonal
 */
static bool is_nonfree_left(uint32_t left_position, uint32_t left) {
  return left & (1 << left_position);
}

/**
 * Function checks if one particular
 * right diagonal is not free for
 * placing queen there
 *
 * @param right_position the number of checking diagonal in "right" bi vector
 * @param right the bit vector that shows vacant and occupied right diagonal in the board
 * @return sign of occupied right diagonal
 */
static bool is_nonfree_right(uint32_t right_position, uint32_t right) {
  return right & (1 << right_position);
}

/**
 * Function checks if we can place queen
 * on specified position
 *
 * @param down_pos the number of position in "down" bit vector
 * @param left_pos the number of position in "left" bit vector
 * @param right_pos the number of position in "right" bit vector
 * @param down link to the bit vector which signs to occupied columns on the chess board
 * @param left link to the bit vector which signs to occupied left diagonals on the chess board
 * @param right link to the bit vector which signs to occupied right diagonal on the chess board
 */
static bool is_placeable(uint32_t down_pos, uint32_t left_pos, uint32_t right_pos, uint32_t* down, uint32_t* left, uint32_t* right) {
  return !is_nonfree_down(down_pos, *down)
          && !is_nonfree_left(left_pos, *left)
          && !is_nonfree_right(right_pos, *right);
}

/**
 * Recursive function that looks for the solution
 * of n queens problem with board of special size
 * and starts with specified row
 *
 * @param board_size the width and height of square chess board
 * @param row the beginning row which from the searching starts
 * @param down link to the bit vector which signs to occupied columns on the chess board
 * @param left link to the bit vector which signs to occupied left diagonals on the chess board
 * @param right link to the bit vector which signs to occupied right diagonals on the chess board
 * @return sign of solution existing for particular board configuration
 */
static bool is_solved(uint32_t board_size, uint32_t row, uint32_t* down, uint32_t* left, uint32_t* right) {
  if (row >= board_size)
    return true;

  for (uint32_t column = 0; column < board_size; ++column) {
    uint32_t down_p = get_down_index(column);
    uint32_t left_p = get_left_index(column, row);
    uint32_t right_p = get_right_index(column, row, board_size);

    if (is_placeable(down_p, left_p, right_p, down, left, right)) {
      *down = set_kth_bit(*down, down_p);
      *left = set_kth_bit(*left, left_p);
      *right = set_kth_bit(*right, right_p);

      if (is_solved(board_size, row + 1, down, left, right)) return true;

      *down = clear_kth_bit(*down, down_p);
      *left = clear_kth_bit(*left, left_p);
      *right = clear_kth_bit(*right, right_p);
    }
  }
  // backtrack
  return false;
}

bool has_solution(uint32_t board_size) {
  uint32_t down = 0, left = 0, right = 0;
  return is_solved(board_size, 0, &down, &left, &right);
}

/**
 * Utility function that search solution for
 * n queens problem but also fills the set of bit
 * vectors that represent the chess board
 *
 * @param board_size the size of square chess board
 * @param row the number of row which solution searching must starts
 * @param down link the "down" bit vector
 * @param left link to the "left" bit vector
 * @param right link to the "right" bit vector
 * @param board the set of bit vectors that represents the board and occupied and vacant cells
 * @return sign of solution existance
 */
static bool solve_nqueens(uint32_t board_size, uint32_t row, uint32_t* down, uint32_t* left, uint32_t* right, uint32_t board[board_size]) {
  if (row >= board_size) return true;

  for (uint32_t column = 0; column < board_size; ++column) {
    uint32_t down_p, left_p, right_p;
    down_p = get_down_index(column);
    left_p = get_left_index(column, row);
    right_p = get_right_index(column, row, board_size);

    if (is_placeable(down_p, left_p, right_p, down, left, right)) {
      board[row] = set_kth_bit(board[row], column);
      *down = set_kth_bit(*down, down_p);
      *left = set_kth_bit(*left, left_p);
      *right = set_kth_bit(*right, right_p);
      if (solve_nqueens(board_size, row + 1, down, left, right, board))
        return true;

      board[row] = clear_kth_bit(board[row], column);
      *down = clear_kth_bit(*down, down_p);
      *left = clear_kth_bit(*left, left_p);
      *right = clear_kth_bit(*right, right_p);
    }
  }
  return false;
}

bool solve_nqueens_on_board(uint32_t size, uint32_t board[size]) {
  uint32_t down = 0, left = 0, right = 0;
  return solve_nqueens(size, 0, &down, &left, &right, board);
}

/**
 * Utility function that prints
 * special characters based on bitwise representation
 * of the number and take only specified number of bits
 *
 * @param number analyzed and printed bitwise representation of number
 * @param length the number of printed bits
 */
static void print_first_bits(uint32_t number, uint32_t length) {
  for (uint32_t i = 0; i < length; ++i) {
    printf(" %c ", number & 1? 'Q' : '_');
    number >>= 1;
  }
}

void print_nqueens_solution(uint32_t for_size) {
  uint32_t board[for_size];

  for (uint32_t i = 0; i < for_size; ++i) board[i] = 0;

  if (!solve_nqueens_on_board(for_size, board))
    printf("solution doesn't exits\n");
  else {
    printf("solution:\n    ");
    for (uint32_t column = 0; column < for_size; ++column)
      printf("%2u ", column);
    printf("\n");

    for (uint32_t row = 0; row < for_size; ++row) {
      printf("%2u: ", row);
      print_first_bits(board[row], for_size);
      printf("\n");
    }
  }
  printf("\n");
}

/**
 * Function that checks if queen can
 * be placed on specified row and column
 * by checking the current board configuration
 * that represents as two dimensional array
 *
 * @param board_size the size of chess board
 * @param board the representation of chess board
 * @param row proposed number of row for placing
 * @param column proposed number of column for placing
 *
 * @return sign of placing ability
 */
static bool brute_is_placeable(size_t board_size, int32_t board[][board_size], size_t row, size_t column) {
  ssize_t i, j;
  /* check this row on left side */
  for (i = 0; i < column; i++)
    if (board[row][i])
      return false;

  /* check upper diagonal on left side */
  for (i = row, j = column; i >= 0 && j >= 0; i--, j--)
    if (board[i][j])
      return false;

  /* check lower diagonal on left side */
  for (i = row, j = column; j >= 0 && i < board_size; i++, j--)
    if (board[i][j])
      return false;

  return true;
}

/**
 * Recursive function checks solution existance
 * by brute force without any data packing
 *
 * @param board_size the size of square chess board
 * @param column the number of column which the algorithm starts with
 * @param board
 * @return sign of solution existance
 */
static bool _brute_solve_nqueens(size_t board_size, size_t column, int32_t board[][board_size]) {
  if (column >= board_size) return true;

  for (size_t row = 0; row < board_size; ++row) {
    if (brute_is_placeable(board_size, board, row, column)) {
      board[row][column] = 1;

      if (_brute_solve_nqueens(board_size, column + 1, board))
        return true;

      board[row][column] = 0;
    }
  }

  return false;
}

bool brute_has_solution(size_t board_size) {
  int32_t board[board_size][board_size];
  for (size_t i = 0; i < board_size; ++i)
    for (size_t j = 0; j < board_size; ++j)
      board[i][j] = 0;

  return _brute_solve_nqueens(board_size, 0, board);
}