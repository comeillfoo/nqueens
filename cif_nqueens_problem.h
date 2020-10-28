/* 
 * File:   cif_nqueens_problem.h
 * Author: comeillfoo
 */

#ifndef CIF_NQUEENS_PROBLEM_H
#define CIF_NQUEENS_PROBLEM_H

/**
 * The function that get appropriate 
 * position in "down" bit vector using board column number
 *
 * @param column the number of column in board
 * @return the number of position in "down" bit vector
 */
uint32_t get_down_index(uint32_t column);

/**
 * The function that get appropriate
 * position in "left" bit vector using board column number
 * and also its row number
 *
 * @param column the number of column in chess board
 * @param row the number of row in chess board
 * @return the number of position in "left" bit vector
 */
uint32_t get_left_index(uint32_t column, uint32_t row);

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
uint32_t get_right_index(uint32_t column, uint32_t row, uint32_t size);
  
/**
 * Function checks if one particular column is not free
 * for placing queen there
 *
 * @param down_position the number of checking column
 * @param down the bit vector that shows vacant and occupied columns
 * @return sign of occupied column
 */
bool is_nonfree_down(uint32_t down_position, uint32_t down);

/**
 * Function checks if one particular
 * left diagonal is not free for
 * placing queen there
 *
 * @param left_position the number of checking diagonal in "down" bit vector
 * @param left the bit vector that shows vacant and occupied left diagonal in the board
 * @return sign of occupied left diagonal
 */
bool is_nonfree_left(uint32_t left_position, uint32_t left);

/**
 * Function checks if one particular
 * right diagonal is not free for
 * placing queen there
 *
 * @param right_position the number of checking diagonal in "right" bi vector
 * @param right the bit vector that shows vacant and occupied right diagonal in the board
 * @return sign of occupied right diagonal
 */
bool is_nonfree_right(uint32_t right_position, uint32_t right);

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
bool is_placeable(uint32_t down_pos, uint32_t left_pos, uint32_t right_pos, uint32_t* down, uint32_t* left, uint32_t* right);

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
bool _is_solved(uint32_t board_size, uint32_t row, uint32_t* down, uint32_t* left, uint32_t* right);

/**
 * Function checks if the chess board of
 * specified size contains a solution for
 * n queens problem and looks for it by packing
 * board representation into three bit vectors:
 * "down" - signs occupied columns (size of n)
 * "left" - signs occupied left diagonals (size of 2n-1)
 * "right" - signs occupied right diagonals (size of 2n-1)
 *
 * @param board_size the size (width or height) of square chess board
 * @return the sign of solution existance
 */
bool has_solution(uint32_t board_size);

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
bool _solve_nqueens(uint32_t board_size, uint32_t row, uint32_t* down, uint32_t* left, uint32_t* right, uint32_t* board);

/**
 * Function that searches for solution
 * of n queens problem and fills the solution
 * to passed set of bit vectors
 *
 * @param board set of bit vectors that represent the chess board
 * @param size the size of chess board
 */
bool solve_nqueens_on_board(uint32_t* board, uint32_t size);

/**
 * Utility function that prints
 * special characters based on bitwise representation
 * of the number and take only specified number of bits
 *
 * @param number analyzed and printed bitwise representation of number
 * @param length the number of printed bits
 */
void print_first_bits(uint32_t number, uint32_t length);

/**
 * Utility function that prints
 * the solution of n queens problem
 * for specified size of board
 * while solving it uses the packing data
 * into three bit vectors that improve perfomance
 *
 * @param for_size the size of chess board
 */
void print_nqueens_solution(uint32_t for_size);

/**
 * Recursive function checks solution existance
 * by brute force without any data packing
 *
 * @param board_size the size of square chess board
 * @param column the number of column which the algorithm starts with
 * @param board
 * @return sign of solution existance
 */
bool _brute_solve_nqueens(uint32_t board_size, uint32_t column, uint32_t[][board_size] board);

/**
 * Function looks for the solution
 * for the chess board with specified
 * size and doesn't make any data packing
 *
 * @param board_size the size of square chess board
 * @return sign of solution existance
 */
bool brute_has_solution(uint32_t board_size);

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
bool brute_is_placeable(uint32_t board_size, uint32_t[][board_size] board, uint32_t row, uint32_t column);

#endif /* CIF_NQUEENS_PROBLEM_H */

