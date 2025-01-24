
read -p "Enter the folder path: " folder
read -p "Enter the pattern to search for: " pattern


if [ ! -d "$folder" ]; then
  echo "Error: The folder '$folder' does not exist or is not a directory."
  exit 1
fi


echo "Files containing the pattern '$pattern':"
for file in "$folder"/*; do
  if [ -f "$file" ] && grep -q "$pattern" "$file"; then
    echo "$(basename "$file")"
  fi
done

