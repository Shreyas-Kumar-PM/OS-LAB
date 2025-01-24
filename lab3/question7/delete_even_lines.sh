#!/bin/bash

# Check if the user has provided a filename
if [ $# -ne 1 ]; then
  echo "Usage: $0 <filename>"
  exit 1
fi

# Get the filename from the command-line argument
filename=$1

# Check if the file exists
if [ ! -f "$filename" ]; then
  echo "Error: File '$filename' does not exist."
  exit 1
fi

# Use sed to delete even-numbered lines and save it back to the same file
sed -i 'n;d' "$filename"

echo "Even-numbered lines have been deleted from '$filename'."

