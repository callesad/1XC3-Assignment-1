#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myAO.h"
#include "utility.h"

// Function to check if the string is a valid integer
int validInteger(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0; // Not an integer
        }
    }
    return 1; // It is an integer
}

int main(int argc, char *argv[]) {
    // Checks the input and ensures sufficient arguments are provided
    if (argc < 3) {
        printf("Usage: ./myAO <print_flag> <operation> <dimensions>\n");
        return 1;
    }

    // Validate print flag (0 or 1)
    if (!validInteger(argv[1]) || (atoi(argv[1]) != 0 && atoi(argv[1]) != 1)) {
        printf("Error: Invalid print flag. Must be 0 or 1. Try again!\n");
        return 1;
    }

    int printFlag = atoi(argv[1]);
    char operation = argv[2][0];

    int nA, mA, nB, mB;
    double **matA, **matB, **result;

    // Transpose operation
    if (operation == 'T') {  
        if (argc < 5) {
            printf("Error: Transpose requires <nA> <mA>. Try again!\n");
            return 1;
        }

        nA = atoi(argv[3]);
        mA = atoi(argv[4]);

        matA = createMatrix(nA, mA);
        fillRandom(matA, nA, mA);

        if (printFlag) {
            printf("Matrix A:\n");
            displayMatrix(matA, nA, mA);
        }

        result = matrixTranspose(matA, nA, mA);

        if (printFlag) {
            printf("Transposed Matrix:\n");
            displayMatrix(result, mA, nA);
        }

        releaseMatrix(matA, nA);
        releaseMatrix(result, mA);
    }
    
    // Addition, Subtraction, Multiplication
    else if (operation == '+' || operation == '-' || operation == '*') {  
        if (argc < 7) {
            printf("Error: Addition/Subtraction/Multiplication requires <nA> <mA> <nB> <mB>. Try again!\n");
            return 1;
        }

        nA = atoi(argv[3]);
        mA = atoi(argv[4]);
        nB = atoi(argv[5]);
        mB = atoi(argv[6]);

        matA = createMatrix(nA, mA);
        matB = createMatrix(nB, mB);
        fillRandomDifferent(matA, matB, nA, mA);  // Filling matrix A and B with different random values

        if (printFlag) {
            printf("Matrix A:\n");
            displayMatrix(matA, nA, mA);
            printf("Matrix B:\n");
            displayMatrix(matB, nB, mB);
        }

        // Calls the function based on the given operation
        result = NULL; 
        if (operation == '+') {
            result = matrixAddition(matA, matB, nA, mA, nB, mB);
        } else if (operation == '-') {
            result = matrixSubtraction(matA, matB, nA, mA, nB, mB);
        } else if (operation == '*') {
            result = matrixMultiplication(matA, matB, nA, mA, nB, mB);
        }

        if (result) {
            if (printFlag) {
                printf("Result Matrix:\n");
                displayMatrix(result, (operation == '*') ? nA : nA, (operation == '*') ? mB : mA);
            }
            releaseMatrix(result, (operation == '*') ? nA : nA);
        }

        releaseMatrix(matA, nA);
        releaseMatrix(matB, nB);
    }

    // Solve Ax = B
    else if (operation == 's') {  
        if (argc < 5) {
            printf("Error: Solve requires <nA> <mA>. Try again!\n");
            return 1;
        }

        nA = atoi(argv[3]);
        mA = atoi(argv[4]);

        if (nA != mA) {
            printf("Error: Matrix A should be square for solving Ax = B. Try again!\n");
            return 1;
        }

        matA = createMatrix(nA, nA);
        double *vecB = (double *)malloc(nA * sizeof(double));
        fillRandom(matA, nA, nA);

        for (int i = 0; i < nA; i++) 
            vecB[i] = (rand() % 21) - 10;

        if (printFlag) {
            printf("Matrix A:\n");
            displayMatrix(matA, nA, nA);
            printf("Vector B:\n");
            for (int i = 0; i < nA; i++) 
                printf("%6.2f\n", vecB[i]);
            printf("\n");
        }

        // Solve Ax = B
        double *solution = solveAxB(matA, vecB, nA);

        if (printFlag) {
            printf("Solution Vector x:\n");
            for (int i = 0; i < nA; i++) 
                printf("%6.2f\n", solution[i]);
            printf("\n");
        }

        free(solution);
        releaseMatrix(matA, nA);
        free(vecB);
    }
    else {
        printf("Error: This Operation is Not Supported. Try Again!'%c'.\n", operation);
        return 1;
    }

    return 0;
}
