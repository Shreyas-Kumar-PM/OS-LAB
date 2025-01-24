#!/bin/bash

# Check if exactly one argument (file or directory) is provided
if [ $# -ne 1 ]; then
  echo "Usage: $0 <file_or_directory>"
  exit 1
fi

# Get the file or directory path from the argument
file_or_directory=$1

# Check if the given argument is a directory
if [ -d "$file_or_directory" ]; then
  echo "$file_or_directory is a directory."

# Check if the given argument is a regular file
elif [ -f "$file_or_directory" ]; then
  echo "$file_or_directory is a regular file."

# If it's neither a directory nor a regular file
else
  echo "$file_or_directory is neither a directory nor a regular file."
fi

