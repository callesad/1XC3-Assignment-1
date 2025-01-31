//Code is by Chatgpt
/* Example 3: Precision Loss in a Function */
#include <stdio.h>
#include <math.h>

double original_function(double x) {
    return sqrt(1 - sqrt(1 - x * x));
}

double stable_function(double x) {
    return x / (1 + sqrt(1 - x * x));
}

int main() {
    double x = 1e-8;
    printf("Original function: %.15lf\n", original_function(x));
    printf("Stable function: %.15lf\n", stable_function(x));
    return 0;
}
