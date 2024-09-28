#include <iostream>
#include <ctime>
#include <random>

#include "element.h"


//организовать ввод ГУ через конфиг файл (json)
int main() {
    srand(time(NULL));
    int x_0 = 0;
    int x_k = 0;
    int n = 0;
    std::cin >> x_0;
    std::cin >> x_k;
    std::cin >> n;
    int start = 0;
    int a = rand() % (110 - 1 + 1) + 1;
    int b = rand() % (61 + 77 + 1) - 77;
    int c = (b == 0) ? rand() % (10 + 31 + 1) - 31 : 0;
    int d = rand() % (72 + 17 + 1) - 17;


    if (c != 0)
        b = 0;

    Fem fem_system(n, x_0, x_k);
    fem_system.Solve(a, b, c);
    auto result = fem_system.GetResult();

    return 0;
}