#!/bin/bash

# Loop through all files in the current directory
for file in *; do
  # Skip directories and process only regular files
  if [ -f "$file" ]; then
    # Use sed to replace "ex:" with "Example:" only if it appears at the start of the line or after a period
    # The regular expression:
    # ^ex: matches "ex:" at the beginning of the line.
    # \. Example: matches "ex:" that follows a period and a space.
    sed -i -E 's/^(ex:)/Example:/g; s/(\. )ex:/\1Example:/g' "$file"
    echo "Processed: $file"
  fi
done

echo "Replacement complete."

