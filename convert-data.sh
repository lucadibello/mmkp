#!/bin/bash

# Accepts an argument that specifies the path of the csv file to be used
# If no argument is provided, notify the user
if [ $# -eq 0 ]; then
    echo "[!] Please provide the path of the csv file to be used!"
    exit 1
fi

# If the argument is provided, check if the file exists
if [ ! -f "$1" ]; then
    echo "[!] Input txt file does not exist"
    exit 1
fi

# Then, run the executable
./cmake-build-debug/converter -i "$1"