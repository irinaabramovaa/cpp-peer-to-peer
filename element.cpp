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

//универсальность ассамблирования
void Fem::Assembly() {
    for (int i = 0; i < n_; ++i) {
        sum_matr(stiffness_matrix_, local_matrixes_[i], {i, i});
    }

}

void Fem::CreateLocalMatrix(int a, int b, int c) {
    for (auto &m: local_matrixes_) {
        m[0][0] = a / len_ + (-b / 2); 
        m[0][1] = -a / len_ + (b / 2);
        m[1][0] = -a / len_ + (-b / 2);
        m[1][1] = a / len_ + b / 2;
    }

}

void Fem::Solve(int a, int b, int c) {
    CreateLocalMatrix(a, b, c);
    Assembly();
    thomas_method(stiffness_matrix_, free_p_, result_);
}