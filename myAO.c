#include <stdio.h>
#include <stdlib.h>
#include "myAO.h"

// Function to allocate memory for a matrix with given dimensions
double** createMatrix(int rows, int cols) {
    double **matrix = (double **)malloc(rows * sizeof(double *));
    if (!matrix) {
        printf("Memory allocation failed! Try Again!\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (double *)malloc(cols * sizeof(double));
        if (!matrix[i]) {
            printf("Memory allocation failed! Try Again!\n");
            for (int j = 0; j < i; j++) free(matrix[j]); 
            free(matrix);
            exit(1);
        }
    }
    return matrix; 
}

// Function to deallocate memory for matrix
void releaseMatrix(double **matrix, int rows) {
    if (matrix) {
        for (int i = 0; i < rows; i++) free(matrix[i]);
        free(matrix);
    }
}

// Function to add two matrices
double** matrixAddition(double **mat1, double **mat2, int nA, int mA, int nB, int mB) {
    if (nA != nB || mA != mB) {
        printf("Error: Matrix addition requires same dimensions. Try Again!\n");
        return NULL;
    }

    double **result = createMatrix(nA, mA);
    for (int i = 0; i < nA; i++)
        for (int j = 0; j < mA; j++)
            result[i][j] = mat1[i][j] + mat2[i][j];

    return result;
}

// Function to subtract two matrices
double** matrixSubtraction(double **mat1, double **mat2, int nA, int mA, int nB, int mB) {
    if (nA != nB || mA != mB) {
        printf("Error: Matrix subtraction requires same dimensions. Try Again!\n");
        return NULL;
    }

    double **result = createMatrix(nA, mA);
    for (int i = 0; i < nA; i++)
        for (int j = 0; j < mA; j++)
            result[i][j] = mat1[i][j] - mat2[i][j];

    return result;
}

// Function to multiply two matrices
double** matrixMultiplication(double **mat1, double **mat2, int nA, int mA, int nB, int mB) {
    if (mA != nB) {
        printf("Error: Invalid dimensions for matrix multiplication. Try Again!\n");
        return NULL;
    }

    double **result = createMatrix(nA, mB);
    for (int i = 0; i < nA; i++)
        for (int j = 0; j < mB; j++) {
            result[i][j] = 0;
            for (int k = 0; k < mA; k++)
                result[i][j] += mat1[i][k] * mat2[k][j];
        }

    return result;
}

// Function to transpose a matrix
double** matrixTranspose(double **mat, int nA, int mA) {
    double **transposed = createMatrix(mA, nA);
    for (int i = 0; i < nA; i++)
        for (int j = 0; j < mA; j++)
            transposed[j][i] = mat[i][j];

    return transposed;
}

// Function to solve system of equations Ax = B with Gaussian elimination
double* solveAxB(double **matA, double *vecB, int nA) {
    double *solution = (double *)malloc(nA * sizeof(double));
    if (!solution) {
        printf("Memory allocation failed for solution vector.\n");
        return NULL;
    }

    // Forward elimination
    for (int i = 0; i < nA; i++) {
        for (int k = i + 1; k < nA; k++) {
            double factor = matA[k][i] / matA[i][i];
            for (int j = 0; j < nA; j++) matA[k][j] -= factor * matA[i][j];
            vecB[k] -= factor * vecB[i];
        }
    }

    // Back substitution
    for (int i = nA - 1; i >= 0; i--) {
        solution[i] = vecB[i];
        for (int j = i + 1; j < nA; j++) solution[i] -= matA[i][j] * solution[j];
        solution[i] /= matA[i][i];
    }

    return solution;
}
