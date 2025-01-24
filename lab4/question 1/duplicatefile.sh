if [ $# -ne 2 ]; then
	echo "Usage: $0 <source_file> <destination_file>"
	exit 1
fi

source_file=$1
destination_file=$2

if [ ! -f "$source_file" ]; then
	echo "Error: Source file '$source_file' does not exist."
	exit 1
fi

cp "$source_file" "$destination_file"

if [ $? -eq 0 ]; then
	echo "File '$source_file' has been successfully copied to '$destination_file'."
	exit 1
else
	echo "Error: Failed to copy the file."
	exit 1
fi

