#include <iostream>
#include <algorithm>
#include <compare>
#include <cmath>
#include <vector>
#include <functional>
#include <Windows.h>


int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::vector<double> angles;
    std::vector<std::function<void(double)>> functions;
    std::function<void(double)> function;
    double a = -1;
    while (a != 0)
    {
        std::cout << "Введите угол для вставки в вектор (или 0 для выхода): ";
        std::cin >> a;
        if (a == 0)
            break;
        a = a * 3.1415926 / 180;
        angles.push_back(a);
    }
    std::cout << "[Входные данные]: ";
    for_each(angles.begin(), angles.end(), [angles](double b) {
        std::cout << b << " ";
        });

    auto for_sin = [](double angle) {std::cout << "sin: " << sin(angle) << "  "; };
    functions.push_back(for_sin);

    auto for_cos = [](double angle) {std::cout << "cos: " << cos(angle) << "  "; };
    functions.push_back(for_cos);

    /*auto for_tan = [](double angle) {std::cout << "tg: " << tan(angle) << "  "; };
    functions.push_back(for_tan);*/

    //или можно так:
     /*auto for_sin = [](double angle) {std::cout << "sin: " << sin(angle); };
    function = for_sin;
    functions.push_back(function); */

    std::cout << std::endl << "[Выходные данные]: " << std::endl;
    for (const auto& angle : angles)
    {
        std::cout << angle << ": ";
        for (const auto& function : functions)
            function(angle);
        std::cout << std::endl;
    }
    return 0;
}