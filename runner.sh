#!/bin/bash

# Check if used passed the --skip-compute flag
if [ "$1" = "--skip-compute" ]; then
    echo "[!] Skipping MMKP computation"
    skip_compute=true
else
    echo "[!] Computing MMKP"
    skip_compute=false
fi

# Check if used passed the --only-standard flag
if [ "$1" = "--only-standard" ]; then
    echo "[!] Running MMKP for standard files only"
    only_standard=true
else
    echo "[!] Running MMKP for all files"
    only_standard=false
fi

# Run every .txt file in /data/large and /data/standard using ./start-mmkp.sh

if [ "$skip_compute" = false ]; then
    echo "[!] Running MMKP for large files..."

    # Delete all .out and .time files in the data/standard and data/large directories
    rm data/large/*.out
    rm data/large/*.time
    rm data/standard/*.out
    rm data/standard/*.time

    if [ "$only_standard" = false ]; then
        for file in data/large/*.txt; do
            ./start-mmkp.sh "$file"

            # Print OK if the file is done
            echo "[OK] $file"
        done
    fi

    echo "[!] Running MMKP for standard files..."
    for file in data/standard/*.txt; do
        ./start-mmkp.sh "$file"

        # Print OK if the file is done
        echo "[OK] $file"
    done
fi
# Get the current directory
current_dir=$(pwd)

# Get the directory of the csv file
input_large="$current_dir/data/large"
input_standard="$current_dir/data/standard"

# Now, start mmkp verifier to verify the results of each file
echo "[!] Running MMKP verifier for large files..."
for file in "$input_large"/*.txt; do
    ./start-verifier.sh "$file"
done

echo "[!] Running MMKP verifier for standard files..."
for file in "$input_standard"/*.txt; do
    ./start-verifier.sh "$file"
done