#!/bin/bash

make
BIN=btc

echo
echo "Test 1 - Valid file"
echo
./$BIN validFile.txt

echo
echo "Test 2 - Invalid file"
echo
./$BIN invalidFile.txt

echo
echo "Test 3 - Invalid input"
echo
./$BIN invalidInput.txt
