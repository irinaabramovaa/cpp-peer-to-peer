#include "element.h"

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