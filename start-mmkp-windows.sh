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

# Then, run the executable
time timeout -s 2 60s ./cmake-build-debug/mmkp -i "$1" -t 60