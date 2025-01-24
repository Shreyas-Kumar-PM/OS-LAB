#!/bin/bash

# Function to search for patterns and display lines containing the pattern
search_pattern() {
    echo "Searching for patterns in '$input_file'..."
    for pattern in "$@"; do
        echo "Lines containing '$pattern':"
        grep -n "$pattern" "$input_file"  # Search for pattern and show line numbers
        echo
    done
}

# Function to delete all occurrences of the patterns from the file
delete_pattern() {
    echo "Deleting patterns from '$input_file'..."
    for pattern in "$@"; do
        # Use sed to delete all occurrences of the pattern
        sed -i "/$pattern/d" "$input_file"
        echo "Deleted all occurrences of '$pattern'."
    done
    echo "Updated content of '$input_file':"
    cat "$input_file"
}

# Function to display the menu
display_menu() {
    echo "Choose an option:"
    echo "1. Search patterns in the input file"
    echo "2. Delete patterns from the input file"
    echo "3. Exit"
}

# Check if the script received at least one pattern argument
if [ $# -lt 1 ]; then
    echo "Usage: $0 <pattern1> <pattern2> ... <patternN> <input_file>"
    exit 1
fi

# Get the patterns and input file from the arguments
patterns=("${@:1:$(($#-1))}")
input_file="${!#}"

# Check if the input file exists
if [ ! -f "$input_file" ]; then
    echo "Error: Input file '$input_file' does not exist."
    exit 1
fi

# Start a loop to show the menu and handle user input
while true; do
    display_menu
    read -p "Enter your choice: " choice

    case $choice in
        1)
            search_pattern "${patterns[@]}"
            ;;
        2)
            delete_pattern "${patterns[@]}"
            ;;
        3)
            echo "Exiting the script."
            exit 0
            ;;
        *)
            echo "Invalid choice, please try again."
            ;;
    esac
done

