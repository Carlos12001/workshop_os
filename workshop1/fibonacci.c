#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototype for calculating Fibonacci numbers
int fibonacci(int n) {
  if (n < 2) return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[]) {
  // Check for the correct number of arguments
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <number> <runs>\n", argv[0]);
    return 1;
  }

  // Parse command line arguments
  int number = atoi(argv[1]);
  int runs = atoi(argv[2]);

  struct timespec start, end;
  long long nanoseconds, total = 0;

  for (int i = 0; i < runs; i++) {
    clock_gettime(CLOCK_MONOTONIC, &start);
    fibonacci(number);
    clock_gettime(CLOCK_MONOTONIC, &end);
    nanoseconds = (end.tv_sec - start.tv_sec) * 1000000000LL +
                  (end.tv_nsec - start.tv_nsec);
    total += nanoseconds;
  }

  printf("Average execution time: %lld nanoseconds\n", total / runs);
  return 0;
}
