/*
 * File:   resolver.h
 * Author: comeillfoo
 */

#ifndef RESOLVER_H
#define RESOLVER_H

#include <stdint.h>
#include <stdbool.h>

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
 * Function that searches for solution
 * of n queens problem and fills the solution
 * to passed set of bit vectors
 *
 * @param size the size of chess board
 * @param board set of bit vectors that represent the chess board
 */
bool solve_nqueens_on_board(uint32_t size, uint32_t board[size]);

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
 * Function looks for the solution
 * for the chess board with specified
 * size and doesn't make any data packing
 *
 * @param board_size the size of square chess board
 * @return sign of solution existance
 */
bool brute_has_solution(size_t board_size);

#endif /* RESOLVER_H */

