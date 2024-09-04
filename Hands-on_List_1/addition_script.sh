#!/bin/bash

# Define two numbers to add
num1=10
num2=20

# Perform the addition
result=$((num1 + num2))

# Define the output file
output_file="/tmp/addition_result.txt"

# Write the result to the file
echo "The result of adding $num1 and $num2 is: $result" > "$output_file"

# Print a message indicating the result has been written
echo "Addition operation completed. The result has been written to $output_file."
