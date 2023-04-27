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

# Check if the second argument is provided
# If not, notify the user
if [ $# -eq 1 ]; then
    echo "[!] Please provide the time limit in seconds!"
    exit 1
fi

# Check if the second argument is a number
# If not, notify the user
if ! [[ "$2" =~ ^[0-9]+$ ]]; then
    echo "[!] Time limit must be a number!"
    exit 1
fi

# Look for mmkp build in "cmake-build-debug" directory
# If not found, tell the user to build it first
if [ ! -d "cmake-build-debug" ]; then
    echo "[!] Please build MMKP project first!"
    exit 1
fi

# Start MMKP executable with the file as argument + measure the real time
# Save the real time to a file
/usr/bin/time -o "$1".time timeout -s 2 $2s ./cmake-build-debug/mmkp -i "$1" -t $2

# Overwrite the file with the real time
# shellcheck disable=SC2002
cat "$1".time | awk '{print $1 > "'$1'.time"}'