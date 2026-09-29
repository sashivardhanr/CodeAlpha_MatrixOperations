# CodeAlpha_MatrixOperations

A C program for performing basic matrix operations, written as part of my CodeAlpha C Programming Internship.

## Operations

- Matrix Addition
- Matrix Multiplication
- Matrix Transpose

## Concepts Used

- 2D arrays
- Functions
- Nested loops
- Conditional statements
- Basic input validation

## How to Compile

```bash
gcc matrix_operations.c -o matrix_operations
```

## How to Run

```bash
./matrix_operations
```

## Example

```
1. Matrix Addition
2. Matrix Multiplication
3. Matrix Transpose
4. Exit
Enter your choice (1-4): 3

--- Matrix Transpose ---
Rows of matrix A    (1-10): 2
Columns of matrix A (1-10): 3
...
Original matrix (2 x 3):
       1       2       3
       4       5       6

Transpose (3 x 2):
       1       4
       2       5
       3       6
```

## Notes

- Matrix size is limited to 10 x 10.
- For multiplication, the number of columns in A must equal the number of rows in B. The program checks this and shows an error if they don't match.

## Author

Sashi Vardhan — CodeAlpha C Programming Intern
