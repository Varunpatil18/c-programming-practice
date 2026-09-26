# C Programming & Systems 

This repository contains my practical C programming implementations, core systems exercises, and algorithmic utilities.

---

## Projects Included

### 1. Student Record & CGPA Analytics System (student_analytics.c)
A command-line academic tool to store, manage, and analyze student academic performance.
* Dynamic Arrays: Uses malloc, realloc, and free to expand memory dynamically as records are added.
* Searching: Implements iterative Binary Search to find students by roll number.
* Sorting & Ranking: Uses qsort with custom comparator functions to rank students by CGPA.
* Cohort Metrics: Calculates class average, highest/lowest CGPA, and distinction percentages.
* File Storage: Saves and loads all records persistently via CSV format (students_data.csv).

### 2. Bank Management System (bank_system.c)
A console-based banking management application focusing on file persistence and state handling.
* Record Management: Creates, updates, and searches user accounts using C struct.
* Transactions: Handles deposit and withdrawal logic with balance verification.
* Persistence: Reads and writes account state to local text files.

### 3. Basic Exercises (hello.c)
* Introduction to C syntax, basic I/O (printf, scanf), and compiler setup.

---

## Topics & Concepts Covered
* Dynamic Memory Allocation: Resizable arrays using malloc, realloc, and heap cleanup via free.
* Algorithms: Binary Search and QuickSort (qsort) with function pointers.
* Data Modeling: User-defined types using struct and typedef.
* File I/O: Stream handling and formatting using fopen, fscanf, fprintf, and fclose.
* Core Fundamentals: Pointers, loops, conditional statements, and console input handling.

---

## How to Compile & Run

Compile any file using GCC in your terminal:

`bash
# Student Analytics Engine
gcc student_analytics.c -o student_analytics
./student_analytics

# Bank Management System
gcc bank_system.c -o bank_system
./bank_system
