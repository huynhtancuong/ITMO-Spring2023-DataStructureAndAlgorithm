#!/bin/bash

# # Test Case 1
# echo "Test Case 1: Running program with no arguments"
# ./main

# # Test Case 2
# echo "Test Case 2: Running program with input file"
# ./main < input.txt

# Test Case 3
echo "Test Case 3: Running program with input file and output file"
./main < input.txt > output.txt

# Test Case 4
echo "Test Case 4: Comparing output file with expected output file"
diff output.txt expected_output.txt

# Clean up
rm -f output.txt