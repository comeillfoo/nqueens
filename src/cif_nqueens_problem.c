#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

uint32_t get_down_index(uint32_t column) { return column; }

uint32_t get_left_index(uint32_t column, uint32_t row) { return row + column; }

uint32_t get_right_index(uint32_t column, uint32_t row, uint32_t size) { return size - 1 - row + column; }

bool is_nonfree_down(uint32_t down_position, uint32_t down) {
  return down & (1 << down_position);
}

bool is_nonfree_left(uint32_t left_position, uint32_t left) {
  return left & (1 << left_position);
}

bool is_nonfree_right(uint32_t right_position, uint32_t right) {
  return right & (1 << right_position);
}

bool is_placeable(uint32_t down_pos, uint32_t left_pos, uint32_t right_pos, uint32_t* down, uint32_t* left, uint32_t* right) {
  return !is_nonfree_down(down_pos, *down)
          && !is_nonfree_left(left_pos, *left)
          && !is_nonfree_right(right_pos, *right);
}


bool _is_solved(uint32_t board_size, uint32_t row, uint32_t* down, uint32_t* left, uint32_t* right) {
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

      if (_is_solved(board_size, row + 1, down, left, right)) return true;

      *down = clear_kth_bit(*down, down_p);
      *left = clear_kth_bit(*left, left_p);
      *right = clear_kth_bit(*right, right_p);
    }
  }
  // backtrack
  return false;
}

bool has_solution(uint32_t board_size) {
  uint32_t* down; uint32_t* left; uint32_t* right;

  // can't be unite into one line because of each other redirecting
  down = malloc(sizeof(uint32_t));
  left = malloc(sizeof(uint32_t));
  right = malloc(sizeof(uint32_t));

  *down = *left = *right = 0;
  return _is_solved(board_size, 0, down, left, right);
}

bool _solve_nqueens(uint32_t board_size, uint32_t row, uint32_t* down, uint32_t* left, uint32_t* right, uint32_t* board) {
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
      if (_solve_nqueens(board_size, row + 1, down, left, right, board))
        return true;

      board[row] = clear_kth_bit(board[row], column);
      *down = clear_kth_bit(*down, down_p);
      *left = clear_kth_bit(*left, left_p);
      *right = clear_kth_bit(*right, right_p);
    }
  }
  return false;
}

bool solve_nqueens_on_board(uint32_t* board, uint32_t size) {
  uint32_t* down; uint32_t* left; uint32_t* right;

  down = malloc(sizeof(uint32_t));
  left = malloc(sizeof(uint32_t));
  right = malloc(sizeof(uint32_t));

  *down = *left = *right = 0;

  return _solve_nqueens(size, 0, down, left, right, board);
}

void print_first_bits(uint32_t number, uint32_t length) {
  for (uint32_t i = 0; i < length; ++i) {
    printf(" %c ", number & 1? 'Q' : '_');
    number >>= 1;
  }
}

void print_nqueens_solution(uint32_t for_size) {
  uint32_t board[for_size];

  for (uint32_t i = 0; i < for_size; ++i) board[i] = 0;

  if (!solve_nqueens_on_board(board, for_size))
    printf("solution doesn't exits\n");
  else {
    printf("solution:\n    ");
    for (uint32_t column = 0; column < for_size; ++column)
      printf("% 2u ", column);
    printf("\n");

    for (uint32_t row = 0; row < for_size; ++row) {
      printf("% 2u: ", row);
      print_first_bits(board[row], for_size);
      printf("\n");
    }
  }
  printf("\n");
}

bool brute_is_placeable(int32_t board_size, int32_t board[][board_size], int32_t row, int32_t column) {
  int32_t i, j;
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


bool _brute_solve_nqueens(int32_t board_size, int32_t column, int32_t board[][board_size]) {
  if (column >= board_size) return true;

  for (uint32_t row = 0; row < board_size; ++row) {
    if (brute_is_placeable(board_size, board, row, column)) {
      board[row][column] = 1;

      if (_brute_solve_nqueens(board_size, column + 1, board))
        return true;

      board[row][column] = 0;
    }
  }

  return false;
}

bool brute_has_solution(int32_t board_size) {
  uint32_t board[board_size][board_size];
  for (uint32_t i = 0; i < board_size; ++i)
    for (uint32_t j = 0; j < board_size; ++j)
      board[i][j] = 0;

  return _brute_solve_nqueens(board_size, 0, board);
}