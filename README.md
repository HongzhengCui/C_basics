# C_basics

This repository contains two C programs: one for detecting palindromes within the digits of π (Pi), and another for solving mazes using the Lee Algorithm.

## Pi Palindrome Detector

The Pi Palindrome Detector program reads the digits of Pi from a file, searches for palindromes of increasing length, and calculates the digit distances between them. It can report the findings in a specific format, including median digit distances.
- Read the digits of the mathematical constant π (Pi) from a file (`pi_50m.txt`). (The file size is large which cannot be uploaded, you can generate this file by calculating 50 million decimal digits.)
- Search for palindromes of increasing length within the digits of Pi.
- Calculate and record the digit distances between successive palindromes.
- Sort the digit distances for each palindrome length and find the median distance.
- Report the findings in a specific format on the terminal window.

## Lee Algorithm Maze Solver
The Lee Algorithm Maze Solver program reads a maze from an ASCII text file and finds a path from the start ('S') to the target ('T') using the Lee Algorithm. The program dynamically allocates queues and stacks for efficient pathfinding.
- Accept an ASCII text file that describes a maze. The maze consists of rows of '#' (walls) and '.' (open passages) characters, with 'S' representing the start point and 'T' representing the target point.
- Use the Lee Algorithm to find a path from the start point to the target point.
- Implement a dynamically allocated queue to manage cells to be visited.
- Implement a dynamically allocated stack to store the solution path.
- Print the path coordinates if a solution is found, or a "No path found" message if no solution exists.
