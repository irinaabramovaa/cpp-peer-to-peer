#include "math_elements.h"


void thomas_method(const std::vector<std::vector<double>>& matrix, const std::vector<double>& c, std::vector<double>& solve) {
    auto n = matrix.size() - 1;
    std::vector<double> alpha(n, 0.);
    std::vector<double> beta (n, 0.);
    alpha[0] = - matrix[0][1] / matrix[0][0];
    beta[0] = c[0] / matrix[0][0];
    for (size_t i = 1; i < n; i++) {
        double y = (matrix[i][i - 1] * alpha[i - 1] +  matrix[i][i]);
        alpha[i] = -matrix[i][i + 1] / y;
        beta[i] = (c[i] - matrix[i][i - 1] * beta [i - 1]) / y;
    }
    solve[n] = (c[n] - matrix[n][n - 1] * beta[n - 1]) / (matrix[n][n - 1] * alpha[n - 1] +  matrix[n][n]);
    for (int i = n - 1; i >= 0; i--) {
        solve[i] = alpha[i] * solve[i + 1] + beta[i];
    }

}