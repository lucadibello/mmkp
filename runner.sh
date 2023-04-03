#!/bin/bash

# Run every .txt file in /data/large and /data/standard using ./start-mmkp.sh

# Get the current directory
current_dir=$(pwd)

# Get the directory of the csv file
input_large="$current_dir/data/large"
input_standard="$current_dir/data/standard"

# Run every .txt file in /data/large and /data/standard using ./start-mmkp.sh
echo "[!] Running MMKP for large files..."
for file in "$input_large"/*.txt; do
    ./start-mmkp.sh "$file"

    # Print OK if the file is done
    echo "[OK] $file"
done

for file in "$input_standard"/*.txt; do
    ./start-mmkp.sh "$file"

    # Print OK if the file is done
    echo "[OK] $file"
done

# Now, start mmkp verifier to verify the results of each file
echo "[!] Running MMKP verifier for large files..."
for file in "$input_large"/*.txt; do
    ./start-verifier.sh "$file"
done

echo "[!] Running MMKP verifier for standard files..."
for file in "$input_standard"/*.txt; do
    ./start-verifier.sh "$file"
done