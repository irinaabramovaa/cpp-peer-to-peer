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
Element Fem::CreateLocalMatrix() {
    std::vector<std::vector<double>> local_matrix = {{0., 0.}, {0., 0.}};
    local_matrix[0][0] = -(double)a_ / len_ + (-b_ / 2.); 
    local_matrix[0][1] = (double)a_ / len_ + (b_ / 2.);
    local_matrix[1][0] = (double)a_ / len_ + (-b_ / 2.);
    local_matrix[1][1] = - (double)a_ / len_ + b_ / 2.;
    return {local_matrix, {c_ * len_ / 2. + d_ * len_ / 2., -c_ * len_ / 2. + d_ * len_ / 2.}};
}

//добавить правую часть ассамблирования
void Fem::Assembly() {
    for (int i = 0; i < n_; i++) {
        Element el = CreateLocalMatrix(); 
        sum_matr(stiffness_matrix_, el.local_matrix_el, {i, i});
        free_p_[i] -= el.right[0];
        free_p_[i + 1] -= el.right[1];
    }
}

void Fem::GU(std::map<int, double> gu) {
    for (auto g: gu) {
        if (g.first == 1) {
            for (auto c: free_p_)
                std::cout << c << ' ';
            std::cout << std::endl;
            free_p_[1] -= stiffness_matrix_[1][0] * g.second;
            stiffness_matrix_.erase(stiffness_matrix_.begin());
            for (auto &v: stiffness_matrix_)
                v.erase(v.begin());
            n_ -= 1;
            free_p_.erase(free_p_.begin());
            result_.erase(result_.begin());
        } else if (g.first == 2) {              //производная в первой точке
            free_p_[0] += a_ * g.second;
        } else if (g.first == 3) {              //производная в последней точке
            std::cout <<free_p_[free_p_.size() - 1] << ' ' << a_ << ' ' << g.second << std::endl;
            free_p_[free_p_.size() - 1] += a_ * g.second;
        } else if (g.first == 4) {
            free_p_.pop_back();
            n_ -= 1;
            free_p_[free_p_.size() - 1] -= stiffness_matrix_[stiffness_matrix_.size() - 2][stiffness_matrix_.size() - 1] * g.second;
            stiffness_matrix_.pop_back();
            result_.pop_back();
            free_p_.pop_back();
            for (auto &v: stiffness_matrix_)
                v.pop_back();
        }
    }
    for (auto c: free_p_)
        std::cout << c << ' ';
}

void Fem::Solve() {
    thomas_method(stiffness_matrix_, free_p_, result_);
}