#!/bin/bash

make
BIN=PmergeMe

echo
echo "Test 1 - sort 10 numbers from 0 to 9"
echo
./$BIN `shuf -i 0-9 -n 10 | xargs`

echo
echo "Test 2 - sort 1000 numbers from 0 to 999"
echo
./$BIN `shuf -i 0-999 -n 1000 | xargs`

echo
echo "Test 3 - sort 3000 numbers from 0 to 2999"
echo
./$BIN `shuf -i 0-2999 -n 3000 | xargs`

echo
echo "Test 4 - sort 10000 numbers from 0 to 9999"
echo
./$BIN `shuf -i 0-9999 -n 10000 | xargs`

echo
echo "Test 5 - sort 10 numbers from 0 to 5"
echo
./$BIN `shuf -i 0-5 -r -n 10 | xargs`

echo
echo "Error tests"
echo "Test 6 - Too big number: 10 1 2147483648"
echo
./$BIN 10 a 2 3 321 1 42 42

echo
echo "Test 7 - Non numbers: 10 a 2 3 321 1 42 42"
echo
./$BIN 10 a 2 3 321 1 42 42

echo
echo "Test 8 - All in one argument: \"42 42 0\""
echo
./$BIN "42 42 0"

echo
echo "Test 9 - Few arguments"
echo
./$BIN

echo
echo "Test 10 - Negative numbers: 10 984 -2 3 321 1 42 -42"
echo
./$BIN 10 984 -2  3 321 1 42 -42
