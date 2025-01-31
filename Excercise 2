//Code is by Chatgpt
/* Example 2: Quadratic Equation */
#include <stdio.h>
#include <math.h>

void solve_quadratic(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        printf("No real roots\n");
        return;
    }
    double sqrt_discriminant = sqrt(discriminant);
    double root1 = (-b - sqrt_discriminant) / (2 * a);
    double root2 = (-b + sqrt_discriminant) / (2 * a);
    if (fabs(b) > fabs(sqrt_discriminant)) {
        root1 = -2 * c / (b + sqrt_discriminant);
        root2 = -2 * c / (b - sqrt_discriminant);
    }
    printf("Roots: %.15lf, %.15lf\n", root1, root2);
}

int main() {
    solve_quadratic(1, 10e8, 1);
    return 0;
}
