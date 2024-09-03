import subprocess
import matplotlib.pyplot as plt

def run_c_program(threads, filename, word):
    """
    Run the C program with the specified number of threads.
    
    Args:
        threads (int): Number of threads to use.
        filename (str): The name of the text file to process.
        word (str): The word to search for in the file.
    
    Returns:
        float: The time taken by the C program to execute.
    """
    # Command to execute the C program with the given number of threads
    command = ['./threads', filename, word, str(threads)]
    
    # Run the command and capture the output
    result = subprocess.run(command, capture_output=True, text=True)
    
    # Parse the time taken from the program's output
    for line in result.stdout.splitlines():
        if "Time taken" in line:
            return float(line.split()[-2])  # Extract the time in seconds
    
    return None

def main():
    filename = 'thus-spake-zarathustra-nietzsche.txt'  # Name of the file to process
    word = 'Good'  # Word to search for in the file
    thread_counts = range(1, 11)  # Different numbers of threads to test
    times = []

    # Run the C program with each thread count and collect the times
    for threads in thread_counts:
        time_taken = run_c_program(threads, filename, word)
        if time_taken is not None:
            times.append(time_taken)
            print(f"Threads: {threads}, Time taken: {time_taken} seconds")
        else:
            print(f"Failed to get time for {threads} threads")

    # Plot the results
    plt.plot(thread_counts, times, marker='o')
    plt.title('Thread Count vs. Execution Time')
    plt.xlabel('Number of Threads')
    plt.ylabel('Time (seconds)')
    plt.grid(True)
    plt.savefig('threads.png')

if __name__ == "__main__":
    main()
