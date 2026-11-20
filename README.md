# GPA Calculator

A simple console GPA calculator written in C++.

## Features

- Enter any number of courses with name, credit hours and grade
- Accepts letter grades (A+, B, C-, ...) or numeric grades (90 or 3.5)
- Input validation: bad numbers and invalid grades are rejected and asked again
- Course names can contain spaces
- Prints a course summary and the cumulative GPA, weighted by credit hours

## Build and run

You need a C++ compiler such as g++.

```
g++ src/gpa_calculator.cpp -o gpa_calculator
./gpa_calculator
```

On Windows PowerShell, run `.\gpa_calculator.exe` instead.

## Example

```
How many courses do you want to add? 2

--- Course 1 of 2 ---
Enter course name: Data Structures
Enter credit hours (e.g., 2, 3): 3
Enter grade (e.g., A, B+, or 90): A

--- Course 2 of 2 ---
Enter course name: Calculus
Enter credit hours (e.g., 2, 3): 4
Enter grade (e.g., A, B+, or 90): B+

==============================
         COURSE SUMMARY
==============================
Course: Data Structures | Credits: 3 | Grade: A (Points: 4.00)
Course: Calculus | Credits: 4 | Grade: B+ (Points: 3.30)
------------------------------
Your Cumulative GPA is: 3.60
```

## How the GPA is calculated

GPA = (sum of grade points x credit hours) / total credit hours
