#pragma once
#include <vector>
#include <array>
#include <functional>
struct Element {
    std::vector<std::vector<double>> local_matrix_el;
    std::vector<double> right;
};

using local_matrix = std::vector<std::vector<double>>;
using form_function = std::function<double(double, int)>;

class Fem {
private:
    int n_ = 0;
    int begin_x_ = 0;
    int end_x_ = 0;
    int len_;
    //функции формы по умолчанию первого порядка
    std::vector<form_function> form_functions_ = {[](double x, int l){return 1 - x/l;}, [](double x, int l){return x/l;}};
    std::vector<std::vector<double>> stiffness_matrix_;
    std::vector<double> free_p_;
    std::vector<double> result_;
    Element CreateLocalMatrix(int a, int b, int c);
public:
    Fem(int n, int x0, int xk): n_(n), begin_x_(x0), end_x_(xk), len_(xk-x0) {
        std::vector<double> tmp(n, 0);
        for (int i = 0; i < n; i++) {
            stiffness_matrix_.push_back(tmp);
            free_p_.push_back(0);
            result_.push_back(0);
        }
    };
    const int GetBegin() const; 
    const int GetEnd() const;
    const int GetLen() const;
    const std::vector<double> GetResult() const;
    void GU();
    void Assembly(int a, int b, int c);
    void Solve(int a, int b, int c);
};