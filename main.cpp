#include <iostream>
#include <ctime>
#include <random>
#include <fstream>

#include "element.h"

template <typename T>
void output(std::vector<T> result, std::ofstream& out) {
    for (int i = 0; i < result.size(); i++) {
        out << result[i] << std::endl;
    }
}

//организовать ввод ГУ через конфиг файл (json|txt) + скрипт, проверяющий корректность
int main() {
    srand(time(NULL));
    int x_0 = 0;
    int x_k = 0;
    int n = 0;
    // std::cin >> x_0;
    // std::cin >> x_k;
    // std::cin >> n;
    int start = 0;
    //сами коэффициеты и границы задавать через конфиг, который проверяется отдельным скриптом/функцией/классом
    int a = rand() % (110 - 1 + 1) + 1;
    int b = rand() % (61 + 77 + 1) - 77;
    int c = /*(b == 0) ?*/ rand() % (10 + 31 + 1) - 31; //: 0;
    int d = rand() % (72 + 17 + 1) - 17;
    if (c != 0)
        b = 0;
    std::cout << a << ' ' << b << ' ' << c << std::endl;
    // Fem fem_system(n, x_0, x_k);
    // fem_system.Solve(a, b, c);
    Fem fem_system(3, 4, 10);
    fem_system.Solve(7, 3, 11);
    auto result = fem_system.GetResult();


    std::ofstream res;
    res.open("result.csv");
    output(result, res);
    

    return 0;
}