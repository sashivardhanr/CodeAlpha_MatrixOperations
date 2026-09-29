/*
 * CodeAlpha C Programming Internship
 * Task 2: Matrix Operations
 *
 * Implements Matrix Addition, Matrix Multiplication and Transpose
 * using 2D arrays and separate functions for each operation.
 *
 * Features:
 *   - Menu-driven interface
 *   - Dimension checks (addition needs equal sizes, multiplication needs
 *     columns of A == rows of B)
 *   - Input validation for every value entered
 *
 * Compile: gcc -Wall -Wextra -o matrix matrix_operations.c
 * Run    : ./matrix        (Windows: matrix.exe)
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

#define MAX_SIZE    10      /* largest allowed rows / columns          */
#define ELEM_LIMIT  1000    /* elements must be in [-1000, 1000] so the
                               results never overflow an int            */

/* ------------------------------------------------------------------ */
/*  Input helpers                                                      */
/* ------------------------------------------------------------------ */

/* Reads an integer in [min, max]; keeps asking until the input is valid. */
static int readInt(const char *prompt, int min, int max)
{
    char line[128];
    char *end;
    long value;

    for (;;) {
        printf("%s", prompt);
        if (fgets(line, sizeof line, stdin) == NULL) {
            printf("\nInput ended. Exiting.\n");
            exit(EXIT_SUCCESS);
        }

        errno = 0;
        value = strtol(line, &end, 10);
        if (end == line || errno == ERANGE) {
            printf("  Invalid input. Please enter a whole number.\n");
            continue;
        }
        while (isspace((unsigned char)*end)) {
            end++;
        }
        if (*end != '\0') {
            printf("  Invalid input. Please enter a whole number.\n");
            continue;
        }
        if (value < min || value > max) {
            printf("  Please enter a value between %d and %d.\n", min, max);
            continue;
        }
        return (int)value;
    }
}

/* ------------------------------------------------------------------ */
/*  Matrix functions                                                   */
/* ------------------------------------------------------------------ */

/* Asks for the number of rows and columns of a matrix. */
static void readDimensions(char name, int *rows, int *cols)
{
    char prompt[64];

    snprintf(prompt, sizeof prompt, "Rows of matrix %c    (1-%d): ", name, MAX_SIZE);
    *rows = readInt(prompt, 1, MAX_SIZE);
    snprintf(prompt, sizeof prompt, "Columns of matrix %c (1-%d): ", name, MAX_SIZE);
    *cols = readInt(prompt, 1, MAX_SIZE);
}

/* Reads all elements of a matrix from the user. */
static void readMatrix(int m[MAX_SIZE][MAX_SIZE], int rows, int cols, char name)
{
    char prompt[64];
    int i, j;

    printf("\nEnter the elements of matrix %c (%d x %d), values from %d to %d:\n",
           name, rows, cols, -ELEM_LIMIT, ELEM_LIMIT);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            snprintf(prompt, sizeof prompt, "  %c[%d][%d] = ", name, i + 1, j + 1);
            m[i][j] = readInt(prompt, -ELEM_LIMIT, ELEM_LIMIT);
        }
    }
}

/* Prints a matrix in a neat grid. */
static void displayMatrix(int m[MAX_SIZE][MAX_SIZE], int rows, int cols, const char *title)
{
    int i, j;

    printf("\n%s (%d x %d):\n", title, rows, cols);
    for (i = 0; i < rows; i++) {
        printf("  ");
        for (j = 0; j < cols; j++) {
            printf("%8d", m[i][j]);
        }
        printf("\n");
    }
}

/* result = a + b  (both matrices are rows x cols) */
static void addMatrices(int a[MAX_SIZE][MAX_SIZE], int b[MAX_SIZE][MAX_SIZE],
                        int result[MAX_SIZE][MAX_SIZE], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

/* result = a * b  (a is r1 x c1, b is c1 x c2, result is r1 x c2) */
static void multiplyMatrices(int a[MAX_SIZE][MAX_SIZE], int b[MAX_SIZE][MAX_SIZE],
                             int result[MAX_SIZE][MAX_SIZE], int r1, int c1, int c2)
{
    int i, j, k;

    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (k = 0; k < c1; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

/* result = transpose of a  (a is rows x cols, result is cols x rows) */
static void transposeMatrix(int a[MAX_SIZE][MAX_SIZE], int result[MAX_SIZE][MAX_SIZE],
                            int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[j][i] = a[i][j];
        }
    }
}

/* ------------------------------------------------------------------ */
/*  Menu handlers                                                      */
/* ------------------------------------------------------------------ */

static void doAddition(void)
{
    int a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE][MAX_SIZE], sum[MAX_SIZE][MAX_SIZE];
    int rows, cols;

    printf("\n--- Matrix Addition ---\n");
    printf("Both matrices must have the same dimensions.\n");
    readDimensions('A', &rows, &cols);

    readMatrix(a, rows, cols, 'A');
    readMatrix(b, rows, cols, 'B');

    addMatrices(a, b, sum, rows, cols);

    displayMatrix(a, rows, cols, "Matrix A");
    displayMatrix(b, rows, cols, "Matrix B");
    displayMatrix(sum, rows, cols, "A + B");
}

static void doMultiplication(void)
{
    int a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE][MAX_SIZE], product[MAX_SIZE][MAX_SIZE];
    int r1, c1, r2, c2;

    printf("\n--- Matrix Multiplication ---\n");
    printf("Columns of A must equal rows of B.\n");
    readDimensions('A', &r1, &c1);
    readDimensions('B', &r2, &c2);

    if (c1 != r2) {
        printf("\nError: cannot multiply a %d x %d matrix by a %d x %d matrix.\n",
               r1, c1, r2, c2);
        printf("Columns of A (%d) must be equal to rows of B (%d).\n", c1, r2);
        return;
    }

    readMatrix(a, r1, c1, 'A');
    readMatrix(b, r2, c2, 'B');

    multiplyMatrices(a, b, product, r1, c1, c2);

    displayMatrix(a, r1, c1, "Matrix A");
    displayMatrix(b, r2, c2, "Matrix B");
    displayMatrix(product, r1, c2, "A x B");
}

static void doTranspose(void)
{
    int a[MAX_SIZE][MAX_SIZE], t[MAX_SIZE][MAX_SIZE];
    int rows, cols;

    printf("\n--- Matrix Transpose ---\n");
    readDimensions('A', &rows, &cols);
    readMatrix(a, rows, cols, 'A');

    transposeMatrix(a, t, rows, cols);

    displayMatrix(a, rows, cols, "Original matrix");
    displayMatrix(t, cols, rows, "Transpose");
}

/* ------------------------------------------------------------------ */
/*  main                                                               */
/* ------------------------------------------------------------------ */

int main(void)
{
    int choice;

    printf("=====================================\n");
    printf("         MATRIX OPERATIONS\n");
    printf("   CodeAlpha C Programming - Task 2\n");
    printf("=====================================\n");

    do {
        printf("\n1. Matrix Addition\n");
        printf("2. Matrix Multiplication\n");
        printf("3. Matrix Transpose\n");
        printf("4. Exit\n");
        choice = readInt("Enter your choice (1-4): ", 1, 4);

        switch (choice) {
        case 1: doAddition();       break;
        case 2: doMultiplication(); break;
        case 3: doTranspose();      break;
        case 4: printf("\nGoodbye!\n"); break;
        }
    } while (choice != 4);

    return 0;
}
