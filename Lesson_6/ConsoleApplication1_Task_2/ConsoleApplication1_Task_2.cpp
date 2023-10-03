#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

int main()
{
    int a = 0, t = 0; 
    std::set<unsigned> mySet{}; 
    std::vector<unsigned> myVector{};
    std::cout << "[IN]: ";
    std::cin >> a;
    for (int i = 0; i < a; i++)
    {
        std::cin >> t;
        mySet.insert(t);
    } // записали в неупорядочный уникальный set, далее переписываем в вектор для применения функции std::sort(). 
    for (const auto& temp : mySet)
    {
        myVector.push_back(temp);
    }
    std::sort(myVector.begin(), myVector.end(), [](const auto& temp, const auto& temp_1) {
        return temp > temp_1;
        }); //сравниваем по второму параметру пары, т.е. по числу (usigned).
    std::cout << "[OUT]: " << std::endl;
    for (auto& temp : myVector)
    {
        std::cout << temp << std::endl;
    }
    return 0;
}
