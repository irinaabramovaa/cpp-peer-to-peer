#include <iostream>

#include "element.h"
#include "math_elements.h"

const int Fem::GetBegin() const{
    return begin_x_;
}
const int Fem::GetEnd() const {
    return end_x_;
}
const int Fem::GetLen() const{
    return len_;
}

const std::vector<double> Fem::GetResult() const {
    return result_;
}

//подумать над универсальностью, либо сделать для 1 и 3 порядков
Element Fem::CreateLocalMatrix(int a, int b, int c) {
    std::vector<std::vector<double>> local_matrix = {{0., 0.}, {0., 0.}};
    local_matrix[0][0] = -(double)a / len_ + (-b / 2.); 
    local_matrix[0][1] = (double)a / len_ + (b / 2.);
    local_matrix[1][0] = (double)a / len_ + (-b / 2.);
    local_matrix[1][1] = - (double)a / len_ + b / 2.;
    std::vector<double> r = {c * len_ / 2., double(c * len_ / 2)};
    return {local_matrix, {c * len_ / 2., double(c * len_ / 2)}};
}

//добавить правую часть ассамблирования
void Fem::Assembly(int a, int b, int c) {
    for (int i = 0; i < n_ - 1; i++) {
        Element el = CreateLocalMatrix(a, b, c);
        sum_matr(stiffness_matrix_, el.local_matrix_el, {i, i});
        free_p_[i] += el.right[0];
        free_p_[i + 1] += el.right[1];
    }
}

void Fem::GU() {}

void Fem::Solve(int a, int b, int c) {
    std::cout << len_ << std::endl;
    Assembly(a, b, c);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            std::cout << stiffness_matrix_[i][j] << ' ';
        std::cout << std::endl;
    }
    thomas_method(stiffness_matrix_, free_p_, result_);
    for (auto &c: result_)
        std::cout << c << std::endl;
}