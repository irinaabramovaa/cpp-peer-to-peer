#pragma once
#include <vector>
#include <array>
#include <functional>
#include <map>
struct Element {
    std::vector<std::vector<double>> local_matrix_el;
    std::vector<double> right;
};

using local_matrix = std::vector<std::vector<double>>;
using form_function = std::function<double(double, int)>;

class Fem {
private:
    int a_;
    int b_;
    int c_;
    int d_; 
    int n_ = 0;
    int begin_x_ = 0;
    int end_x_ = 0;
    double len_;
    //функции формы по умолчанию первого порядка
    std::vector<form_function> form_functions_ = {[](double x, int l){return 1 - x/l;}, [](double x, int l){return x/l;}};
    std::vector<std::vector<double>> stiffness_matrix_;
    std::vector<double> free_p_;
    std::vector<double> result_;
    Element CreateLocalMatrix();
public:
    Fem(int n, int x0, int xk,
        int a, int b, int c, int d): 
                                    n_(n), begin_x_(x0), end_x_(xk), len_(double(xk-x0) / n),
                                    a_(a), b_(b), c_(c), d_(d) {
        std::cout << len_ << std::endl;
        std::vector<double> tmp(n + 1, 0);
        for (int i = 0; i < n; i++) {
            stiffness_matrix_.push_back(tmp);
            free_p_.push_back(0);
            result_.push_back(0);
        }
        stiffness_matrix_.push_back(tmp);
        free_p_.push_back(0);
        result_.push_back(0);
    };
    const int GetBegin() const; 
    const int GetEnd() const;
    const int GetLen() const;
    const std::vector<double> GetResult() const;
    void GU(std::map<int, double> gu);
    void Assembly();
    void Solve();
};