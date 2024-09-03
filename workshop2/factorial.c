#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void factorial(unsigned int n, mpz_t result) {
  if (n == 0 || n == 1) {
    mpz_set_ui(result, 1);  // Factorial of 0 or 1 is 1
  } else {
    mpz_t temp_result;
    mpz_init(temp_result);
    factorial(n - 1, temp_result);       // Recursive call for n-1
    mpz_mul_ui(result, temp_result, n);  // result = temp_result * n
    mpz_clear(temp_result);
  }
}

int main(int argc, char *argv[]) {
  int print_result = 0;  // Flag to determine whether to print the result

  // Check if the correct number of arguments is provided and if '-p' is one of
  // them
  if (argc < 2) {
    printf("Usage: %s <number> [-p]\n", argv[0]);
    return 1;
  }

  // Check for the '-p' option in the arguments
  for (int i = 2; i < argc; i++) {
    if (strcmp(argv[i], "-p") == 0) {
      print_result = 1;  // Set the print flag if '-p' is found
      break;
    }
  }

  unsigned int number = atoi(argv[1]);

  mpz_t result;
  mpz_init(result);
  factorial(number, result);  // Calculate factorial

  if (print_result) {
    printf("The factorial of %u is:\n", number);
    mpz_out_str(stdout, 10, result);  // Print result in base 10
    printf("\n");
  }

  mpz_clear(result);
  return 0;
}
