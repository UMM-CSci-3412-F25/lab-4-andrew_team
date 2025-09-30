#!/bin/env bash
set -euo pipefail

# commands for execute and testing with bats test: 
# chmod +x summarize_tree/summarize_tree.sh
# bats -f '^summarize_tree\.sh ' summarize_tree_test.bats

# Check for the correct number of arguments.
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <path>"
  echo "       where <path> is the file or root of the tree you want to summarize."
  exit 1
fi

root="$1"

# count number of directories and files in root
# using find to do the traversal and wc -l to count the lines
# type d for directories, f for files
dirs=$(find "$root" -type d | wc -l)
files=$(find "$root" -type f | wc -l)

# print the results
# just try to past tests
echo "There were $dirs directories."
echo "There were $files regular files."