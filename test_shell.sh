#!/bin/bash

echo "Testing Simple Shell 0.1"
echo "========================="

# Test 1: Basic command execution
echo "Test 1: Basic command execution"
echo "/bin/ls" | ./shell
echo

# Test 2: Error handling for non-existent command
echo "Test 2: Error handling for non-existent command"
echo "nonexistent" | ./shell
echo

# Test 3: Error handling for non-executable file
echo "Test 3: Error handling for non-executable file"
echo "shell.h" | ./shell
echo

# Test 4: Multiple commands
echo "Test 4: Multiple commands"
printf "/bin/ls\n/bin/pwd\n" | ./shell
echo

# Test 5: Empty line handling
echo "Test 5: Empty line handling"
printf "\n/bin/ls\n" | ./shell
echo

# Test 6: EOF handling (Ctrl+D simulation)
echo "Test 6: EOF handling"
printf "/bin/ls" | ./shell
echo

echo "All tests completed!"
