# Read all .time files in data/standard and data/large and compute the average time
# for each data set.  Print the results to the screen.

import os
import sys


def computeAverageTime(directory):
    # Get the list of files in the data/standard directory
    files = os.listdir(directory)
    # Remove any files that don't end in .time
    files = [f for f in files if f.endswith('.time')]
    # Get the average time for each file
    total_time = 0
    for f in files:
        # Read first line of file
        with open('data/standard/' + f, 'r') as df:
            line = df.readline()
            # Convert to float and add to total
            total_time += float(line)

            # If time > 1.0, print a warning + filename
            if float(line) > 1.0:
                print('WARNING: Time > 1.0 in file: %s' % f)

    # Print the average time
    print('Average time:', total_time / len(files))


def main():
    # Compute average time for standard data
    print('Standard data:')
    computeAverageTime('data/standard')
    # Compute average time for large data
    print('Large data:')
    computeAverageTime('data/large')


if __name__ == '__main__':
    main()
