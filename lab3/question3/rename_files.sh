#!/bin/bash

# Find all .txt files recursively in the current directory and subdirectories
find . -type f -name "*.txt" | while read -r file; do
    # Create the new file name by replacing .txt with .text
    new_name="${file%.txt}.text"
    
    # Rename the file
    mv "$file" "$new_name"
    
    # Output the renaming operation
    echo "Renamed: $file -> $new_name"
done

