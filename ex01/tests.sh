#!/bin/bash

make && clear
BIN=RPN

echo
echo "Test 1: \"8 9 * 9 - 9 - 9 - 4 - 1 +\""
echo "Expected: 42"
echo -n "Result: "
./$BIN "8 9 * 9 - 9 - 9 - 4 - 1 +"

echo
echo "Test 2: \"7 7 * 7 -\""
echo "Expected: 42"
echo -n "Result: "
./$BIN "7 7 * 7 -"

echo
echo "Test 3: \"1 2 * 2 / 2 * 2 4 - +\""
echo "Expected: 0"
echo -n "Result: "
./$BIN "1 2 * 2 / 2 * 2 4 - +"

echo
echo "Test 4: \"(1 + 1)\""
echo "Expected: Error"
echo -n "Result: "
./$BIN "(1 + 1)"

echo
echo "Test 5: \"1 2 3 +\""
echo "Expected: Error"
echo -n "Result: "
./$BIN "1 2 3 +"

echo
echo "Test 6: \"12 3 +\""
echo "Expected: Error"
echo -n "Result: "
./$BIN "12 3 +"

echo
echo "Test 7: \"1 + 2\""
echo "Expected: Error"
echo -n "Result: "
./$BIN "1 + 2"

echo
echo "Test 8: \"1 a +\""
echo "Expected: Error"
echo -n "Result: "
./$BIN "1 a +"

echo
echo "Test 9: \"1\""
echo "Expected: Error"
echo -n "Result: "
./$BIN "1"

echo
echo "Test 10: \"1.5 + 2\""
echo "Expected: Error"
echo -n "Result: "
./$BIN "1.5 + 2"

echo
echo "Test 11: \"+ 1 1\""
echo "Expected: Error"
echo -n "Result: "
./$BIN "+ 1 1"

echo
echo "Test 12: \"1 0 /\""
echo "Expected: Error"
echo -n "Result: "
./$BIN "1 0 /"
