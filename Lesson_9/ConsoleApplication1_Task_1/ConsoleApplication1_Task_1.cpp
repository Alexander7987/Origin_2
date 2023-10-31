#include <iostream>
#include <vector>

template <typename T>
void move_vectors(T& one, T& two) //при использовании move const использовать нельзя
{
    T temp = std::move(one); //указатель temp теперь смотрит на область памяти one, а указатель one теперь указывает на нулевую область памяти
    one = std::move(two); //указатель one теперь указывает на область памяти two, а указатель two теперь указывает на нулевую область памяти
    two = std::move(temp); //указатель two теперь указывает на область памяти temp, а указатель temp теперь указывает на нулевую область памяти
}


template <typename T>
void print(const T& my_vector)
{
    for (auto n : my_vector)
    {
        std::cout << n << " ";
    }
}

int main()
{
    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;
    move_vectors(one, two);
    std::cout << "one: ";
    print(one);
    std::cout << std::endl << "two: ";
    print(two);
}

