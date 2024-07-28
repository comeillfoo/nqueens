/*
 * File:   main.c
 * Author: comeillfoo
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <time.h>

#include "cif_nqueens_problem.h"

#define MAXIMUM_BOARD_SIZE 17

struct timespec start, end;

int main(int argc, char** argv) {

  /*
  // print out existance of solution
  for (uint32_t size = 0; size < MAXIMUM_BOARD_SIZE; ++size)
    printf("does solution exist for board which size is % 2u?: %s\n", size, has_solution(size)? "true" : "false");
  printf("\n");

  // print out graphical solutions
  for (uint32_t size = 0; size < MAXIMUM_BOARD_SIZE; ++size)
    print_nqueens_solution(size);
  return 0;
  */

  printf("bit-tricked\nsize, time\n");

  // measure execution time for every calculation with bit tricks
  for (uint32_t size = 1; size < MAXIMUM_BOARD_SIZE; ++size) {
    clock_gettime(CLOCK_MONOTONIC, &start);
    has_solution(size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double differ = ((end.tv_sec - start.tv_sec) + 1e-9 * (end.tv_nsec - start.tv_nsec)) * 1e3;
    printf("%4d, %f\n", size, differ);
  }
  printf("\nnot bit-tricked\n");
  printf("size, time\n");

  // measure execution time for every calculation with bit tricks
  for (uint32_t size = 1; size < MAXIMUM_BOARD_SIZE; ++size) {
    clock_gettime(CLOCK_MONOTONIC, &start);
    brute_has_solution(size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double differ = ((end.tv_sec - start.tv_sec) + 1e-9 * (end.tv_nsec - start.tv_nsec)) * 1e3;
    printf("%4d, %f\n", size, differ);
  }

  // measure execution time for algorithm with bit tricks
  clock_gettime(CLOCK_MONOTONIC, &start);
  for (uint32_t size = 1; size < MAXIMUM_BOARD_SIZE; ++size)
    has_solution(size);
  clock_gettime(CLOCK_MONOTONIC, &end);

  double exec_time = ((end.tv_sec - start.tv_sec) + 1e-9 * (end.tv_nsec - start.tv_nsec)) * 1e3;
  printf("Full time with tricks: %f\nAverage time with tricks: %f\n\n", exec_time, exec_time / (MAXIMUM_BOARD_SIZE - 1));
  // end of measurements

  // measure execution time for algorithm without bit tricks
  clock_gettime(CLOCK_MONOTONIC, &start);
  for (int32_t size = 1; size < MAXIMUM_BOARD_SIZE; ++size)
    brute_has_solution(size);
  clock_gettime(CLOCK_MONOTONIC, &end);

  exec_time = ((end.tv_sec - start.tv_sec) + 1e-9 * (end.tv_nsec - start.tv_nsec)) * 1e3;
  printf("Full time without tricks: %f\nAverage time without tricks: %f\n", exec_time, exec_time / (MAXIMUM_BOARD_SIZE - 1));
  // end of measurements
}