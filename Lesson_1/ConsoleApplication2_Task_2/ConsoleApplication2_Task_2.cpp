#include <iostream>
#include <algorithm>
#include <compare>
#include <variant>
#include <vector>
#include <any>
#include <Windows.h>

std::variant<int, std::string, std::vector<int>> get_variant()
{
    std::srand(time(nullptr));
    int random_variable = std::rand() % 3;
    std::variant<int, std::string, std::vector<int>> result;
    switch (random_variable)
    {
    case 0:
        result = 5;
        break;
    case 1:
        result = "string";
        break;
    case 2:
        result = std::vector<int>{ 1, 2, 3, 4, 5 };
        break;
    default:
        break;
    }
    return result;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::variant<int, std::string, std::vector<int>> result = get_variant();
    if (std::holds_alternative<int>(result))
    {
        auto result_int = std::get<int>(result);
        std::cout << result_int * 2;
    }
    else if (std::holds_alternative<std::string>(result))
    {
        auto result_string = std::get<std::string>(result);
        std::cout << result_string;
    }
    else
    {
        auto result_vector = std::get<std::vector<int>>(result);
        std::for_each(result_vector.begin(), result_vector.end(), [result_vector](int a) {
            std::cout << a << " ";
            });
    }
    return 0;
}