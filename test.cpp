#include <iostream>
#include <vector>


void summ_matr(std::vector<std::vector<int>>& big, std::vector<std::vector<int>>& little, std::pair<int, int> pos) {
    for (int i = 0; i < little.size(); i++)
        for (int j = 0; j < little.size(); j++)
            big[i + pos.second][j + pos.first] += little[i][j];
}


int main() {
    std::vector<std::vector<int>> big = {
                                        {0, 0, 0 ,0}, 
                                        {0, 0, 0, 0}, 
                                        {0, 0, 0, 0},
                                        {0, 0, 0, 0}
                                    };
    std::vector<std::vector<int>> little = {
        {5, 6},
        {7, 8}
    };
    summ_matr(big, little, {1, 1});
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            std::cout << big[i][j] << ' ';
        std::cout << std::endl;
    }
    return 0;
}