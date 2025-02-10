#ifndef EQUATIONS_SOLVE_H
#define EQUATIONS_SOLVE_H

// Structure to store eigenvalues and related calculations
typedef struct {
    double discriminant;
    int hasComplexRoots;
    double root1, root2;
    double RealPart, ImagPart;
} solve;

// Function Prototypes
int get_values(int* m, int limit_row, int limit_col);  // Get matrix values from user
double sum_of_dia(int* m, int limit_row, int limit_col); // Calculate sum of main diagonal
double sum_of_minor(int* m, int limit_row, int limit_col); // Calculate sum of minors
double determinant(int* m, int limit_row, int limit_col); // Calculate matrix determinant
int print_mat(int* m, int limit_row, int limit_col); // Print matrix
solve find_eigen_value(int* m, int limit_row, int limit_col); // Find eigenvalues

#endif // EQUATIONS_SOLVE_H
