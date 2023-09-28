#include <iostream>
#include <vector>
#include <Windows.h>


template<typename T>
class my_class
{
private:
    int sum = 0;
    int count = 0;
public:
    void operator ()(const T& my_case)
    {
        for (auto element : my_case)
        {
            if (element % 3 == 0)
            {
                count++;
                sum += element;
            }
        }
    }
    void get_sum()
    {
        std::cout << "[OUT]: get_sum = " << sum << std::endl;
    }
    void get_count()
    {
        std::cout << "[OUT]: get_count = " << count << std::endl;
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::vector<int> my_vector{ 4, 1, 3, 6, 25, 54 };
    my_class<std::vector<int>> temp;
    temp(my_vector);
    std::cout << "[IN]: ";
    for (auto i : my_vector)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    temp.get_sum();
    temp.get_count();
    return 0;
}