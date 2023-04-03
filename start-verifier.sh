#!/bin/bash

# Accepts an argument that specifies the path of the txt file to be used
# If no argument is provided, notify the user
if [ $# -eq 0 ]; then
    echo "[!] Please provide the path of the txt input file to be used!"
    exit 1
fi

# If the argument is provided, check if the file exists
if [ ! -f "$1" ]; then
    echo "[!] Input file does not exist"
    exit 1
fi

# Ensure that there is a $1.out file
if [ ! -f "$1.out" ]; then
    echo "[!] Output file does not exist. You have to generate a proper solution first!"
    exit 1
fi

# Look for mmkp build in "cmake-build-debug" directory
# If not found, tell the user to build it first
if [ ! -d "cmake-build-debug" ]; then
    echo "[!] Please build MMKP project first!"
    exit 1
fi

# Execute the MMKP verifier for the input file
./cmake-build-debug/verifier -i "$1" -t 60 -s verifier/stats.txt