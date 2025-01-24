
compare_strings() {
    if [[ "$1" < "$2" ]]; then
        return 1  
    elif [[ "$1" > "$2" ]]; then
        return 2  
    else
        return 0  
    fi
}


sort_strings() {
    local arr=("$@")
    local len=${#arr[@]}

    
    for ((i = 0; i < len; i++)); do
        for ((j = 0; j < len - i - 1; j++)); do
            compare_strings "${arr[$j]}" "${arr[$((j + 1))]}"
            result=$?

            
            if [[ $result -eq 1 ]]; then
                temp="${arr[$j]}"
                arr[$j]="${arr[$((j + 1))]}"
                arr[$((j + 1))]="$temp"
            fi
        done
    done

    
    for word in "${arr[@]}"; do
        echo -n "\"$word\" "
    done
    echo
}


if [ $# -eq 0 ]; then
    echo "Usage: $0 <string1> <string2> ... <stringN>"
    exit 1
fi


sort_strings "$@"

