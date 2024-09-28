#pragma once
#include <vector>


void thomas_method(const std::vector<std::vector<double>>& matrix, const std::vector<double>& c, std::vector<double>& solve);
template <typename f, typename s>
void sum_matr(std::vector<std::vector<f>>& big, std::vector<std::vector<s>>& little, std::pair<int, int> pos) {
    for (int i = 0; i < little.size(); i++)
        for (int j = 0; j < little.size(); j++)
            big[i + pos.second][j + pos.first] += little[i][j];
}
