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

void Fem::Assembly() {
    for (int i = 0; i < n_; ++i) {
        stiffness_matrix_[i][i] += (local_matrixes_[i])[0][0];
        stiffness_matrix_[i][i + 1] += (local_matrixes_[i])[0][1];
        stiffness_matrix_[i + 1][i] += (local_matrixes_[i])[1][0];
        stiffness_matrix_[i + 1][i + 1] += (local_matrixes_[i])[1][1];

        /*for (int j = 0; j < 2; ++j) {
            stiffness_matrix_ []
        } */
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