import sys
import time
import argparse

# Set the recursion limit
sys.setrecursionlimit(200000)

def fibonacci(n):
    """ Recursively calculates the nth Fibonacci number. """
    if n < 2:
        return n
    return fibonacci(n-1) + fibonacci(n-2)

if __name__ == "__main__":
    # Set up ArgumentParser to accept command line arguments
    parser = argparse.ArgumentParser(description='Calculates the factorial of a number using recursion.')
    parser.add_argument('number', type=int, help='The number for which to calculate the factorial.')
    parser.add_argument('runs', type=int, help='The number of times to execute the calculation.')
    args = parser.parse_args()
    
    total = []
    for i in range(args.runs):
        start_time = time.perf_counter_ns()
        fibonacci(args.number)
        end_time = time.perf_counter_ns()
        total.append(end_time - start_time)
    print(f"Average execution time: {sum(total) / args.runs} nanoseconds")

