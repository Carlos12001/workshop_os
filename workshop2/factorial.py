import sys
import argparse

# Set the recursion limit
sys.setrecursionlimit(200000)
sys.set_int_max_str_digits(50000)

def factorial(n):
    """
    Recursively calculates the factorial of a given number.
    
    Args:
        n (int): The number to calculate the factorial for.
    
    Returns:
        int: The factorial of the given number.
    """
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
            description='Calculate the factorial of a given number.')
    parser.add_argument('number', type=int, 
                        help='The number to calculate the factorial for.')
    parser.add_argument('-p', '--print', action='store_true', 
                        help='Print the factorial result to the console.')
    args = parser.parse_args()
    
    result = factorial(args.number)
    if args.print:
        print(f"The factorial of {args.number} is:")
        print(result)
