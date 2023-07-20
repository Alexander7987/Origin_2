#include <iostream>
#include <algorithm>
#include <vector>
#include <Windows.h>

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::vector<int> my_vector { 4, 7, 9, 14, 12 };
    std::cout << "Входные данные: ";
    std::for_each(my_vector.begin(), my_vector.end(), [](int& a) {
        std::cout << a << " ";
        });
    std::cout << std::endl;
    std::cout << "Выходные данные: ";
    std::for_each(my_vector.begin(), my_vector.end(), [](int& a) {
        if (a%2 != 0)
            a *= 3;
        std::cout << a << " ";
        });
    std::cout << std::endl;
    return 0;
}
