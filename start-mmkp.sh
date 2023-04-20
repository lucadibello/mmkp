#!/bin/bash

# Accepts an argument that specifies the path of the csv file to be used
# If no argument is provided, notify the user
if [ $# -eq 0 ]; then
    echo "[!] Please provide the path of the csv file to be used!"
    exit 1
fi

# If the argument is provided, check if the file exists
if [ ! -f "$1" ]; then
    echo "[!] CSV file does not exist"
    exit 1
fi

# Look for mmkp build in "cmake-build-debug" directory
# If not found, tell the user to build it first
if [ ! -d "cmake-build-debug" ]; then
    echo "[!] Please build MMKP project first!"
    exit 1
fi

# Execute the MMKP executable and register the real time then, save it to a file
# The file is named after the csv file used
# The file is saved in the same directory as the csv file

# Get the directory of the csv file
csv_file_dir=$(dirname "$1")

# Get the filename of the file
csv_file_name=$(basename "$1")

# Start MMKP executable with the file as argument + measure the real time
# Save the real time to a file
output=$( { time ./cmake-build-debug/mmkp -i "$1" -t 1; } 2>&1 )


# Get the real time
# This is the output: ./cmake-build-debug/mmkp -i "$1" -t 60  0.01s user 0.00s system 93% cpu 0.009 total
# We want to get the total time 0.009 using a regex (format <number>.<number> total<end of line>) using sed
real_time=$(tail -n 1 <<< "$output" | awk '{print $12}')

# Save the real time to a file
# Create new file if it does not exist
# Overwrite the file if it exists
echo "$real_time" > "$csv_file_dir/$csv_file_name.time"

# Check for verbose flag
if [ "$2" = "-v" ]; then
    # Print the output
    echo "$output"
    echo "Total time: $real_time seconds"
fi