#!/bin/bash

# Read the basic salary and TA from the user
read -p "Enter the Basic Salary: " basics
read -p "Enter the Traveling Allowance (TA): " ta

# Calculate 10% of Basics
ten_percent_basics=$(echo "$basics * 0.10" | bc)

# Calculate the Gross Salary
gs=$(echo "$basics + $ta + $ten_percent_basics" | bc)

# Output the result
echo "Gross Salary (GS) = Basics + TA + 10% of Basics"
echo "Gross Salary = $gs"

