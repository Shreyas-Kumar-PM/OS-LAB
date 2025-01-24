#!/bin/bash

# Prompt the user for the file extension and destination folder
read -p "Enter the file extension (e.g., .txt): " extension
read -p "Enter the destination folder name: " destination_folder

# Check if the destination folder exists, if not, create it
if [ ! -d "$destination_folder" ]; then
    echo "Destination folder '$destination_folder' does not exist. Creating it now."
    mkdir "$destination_folder"
fi

# Copy all files with the given extension (only from the current directory)
for file in *"$extension"; do
    # Ensure it's a regular file and not a directory
    if [ -f "$file" ]; then
        cp "$file" "$destination_folder/"
        echo "Copied: $file to $destination_folder"
    fi
done

echo "File copying complete."

