#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

directory="$1"

if [ ! -d "$directory" ]; then
    echo "Directory '$directory' does not exist."
    exit 1
fi

for file in "$directory"/*; do
    if [ -f "$file" ]; then
        ./raytracer "$file" --close
        mv "./result_image.png" "$file.png"
    fi
done
