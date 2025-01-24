if [ $# -eq 0 ]; then
  echo "Usage: $0 <file1> <file2> ... <fileN>"
  exit 1
fi


for file in "$@"; do
  if [ -f "$file" ]; then
    read -p "Are you sure you want to delete '$file'? (y/n): " confirm
    if [[ "$confirm" == "y" || "$confirm" == "Y" ]]; then
      rm "$file"
      echo "'$file' has been deleted."
    else
      echo "'$file' was not deleted."
    fi
  else
    echo "File '$file' does not exist."
  fi
done
