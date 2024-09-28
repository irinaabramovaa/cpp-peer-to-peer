#pragma once
#include <vector>
#include <array>
// #include <functional>

class Element {};

using local_matrix = std::array<std::array<double, 2>, 2>;

class Fem {
private:
    int n_ = 0;
    int begin_x_ = 0;
    int end_x_ = 0;
    int len_;
    // std::function<double(double, int)> form_function_ = [](double x, int l){return 1 - x/l;};           //переменная, получающая функцию формы
    // вставлять вторую функцию формы?
    std::vector<std::vector<double>> stiffness_matrix_;
    std::vector<double> free_p_;
    std::vector<local_matrix> local_matrixes_;
    std::vector<double> result_;
    void CreateLocalMatrix(int a, int b, int c);
public:
    Fem(int n, int x0, int xk): n_(n), begin_x_(x0), end_x_(xk), len_(xk-x0) {};
    const int GetBegin() const;
    const int GetEnd() const;
    const int GetLen() const;
    const std::vector<double> GetResult() const;
    void Assembly();
    void Solve(int a, int b, int c);
};