import os
import subprocess
import time
import pandas as pd
import matplotlib.pyplot as plt

def run_program(command, priority):
    """
    Executes a given command with a specified priority using the 'nice' command.

    Parameters:
        command (str): The command to be executed along with its parameters.
        priority (int): The priority level for the process, adjusted by 'nice'.

    Returns:
        float: The execution time in seconds for the command.
    """
    # Set the process priority and execute the command
    pid = subprocess.Popen(['nice', '-n', str(priority), 'bash', '-c', command])
    start_time = time.time()
    pid.wait()
    return time.time() - start_time

# Data structure to store results for Python and C programs
results = {
    'Python': {'Priority': [], 'Time': []},
    'C': {'Priority': [], 'Time': []}
}

script_directory = os.path.dirname(os.path.abspath(__file__))

# Define the commands for the Python and C Fibonacci programs
python_command = f'python3 {script_directory}/factorial.py 10000'
c_command = f'{script_directory}/factorial 10000'

# Test the same priorities for both Python and C programs
priorities = range(-2, 3, 1)  # Priorities from 0 to 4
for priority in priorities:
    # Running Python program
    results['Python']['Priority'].append(priority)
    results['Python']['Time'].append(run_program(python_command, priority))
    
    # Running C program
    results['C']['Priority'].append(priority)
    results['C']['Time'].append(run_program(c_command, priority))

# Convert results to DataFrame for easier plotting
df_python = pd.DataFrame(results['Python'])
df_c = pd.DataFrame(results['C'])

# Create plots to visualize the execution time by priority
plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.plot(df_python['Priority'], df_python['Time'], marker='o', label='Python')
plt.title('Python Execution Time by Priority')
plt.xlabel('Priority')
plt.ylabel('Time (s)')
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(df_c['Priority'], df_c['Time'], marker='o', label='C')
plt.title('C Execution Time by Priority')
plt.xlabel('Priority')
plt.ylabel('Time (s)')
plt.legend()

plt.tight_layout()
plt.savefig('process.png')
