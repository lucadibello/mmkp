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

# Execute the MMKP verifier for the input file and read the computed value from stderr
result=$(./cmake-build-debug/verifier -i "$1" -t 60 -s verifier/stats.txt 2>&1)

# Get the objective value from last line
result=$(tail -n 1 <<< "$result")

# Now, look for the optimal value in the data/solutions.csv file and compare it with the computed value
# CSV file format: <filename>,<optimal value>
# The filename is the same as the input file
# The optimal value is the last column of the csv file

# Find filename in solutions.csv file
optimal_value=$(grep -E "^$(basename "$1"),[0-9]+" data/solutions.csv | awk -F ',' '{print $NF}')

# Check if a value has been found
foundOptimalValue=1
if [ -z "$optimal_value" ]; then
    foundOptimalValue=0
else
  # Compute the percentage difference
  percentage_difference=$(echo "scale=2; ($result - $optimal_value) * 100 / $optimal_value" | bc -l)
fi


# If the result != -1 then the solution is correct
if [ "$result" != "-1" ]; then
    # If the optimal value has been found, print the percentage difference
    if [ "$foundOptimalValue" -eq 1 ]; then
        echo "[$1] Solution is correct! The computed value is $result/$optimal_value ($percentage_difference%)"
    else
        echo "[$1] Solution is correct! The computed value is $result (optimal value not found...)"
    fi
else
    if [ "$foundOptimalValue" -eq 1 ]; then
        echo "[$1] Solution is not feasible! The solution would be $optimal_value..."
    else
        echo "[$1] Solution is not feasible!"
    fi
fi