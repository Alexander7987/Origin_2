#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

int main()
{
    int count = 0; // счетчик повторений одной буквы
    std::string s = "Hello World!!";
    std::unordered_map<char, unsigned> myMap {}; //ключ - буква, значение - кол-во этих букв в тексте
    std::vector<std::pair<char, unsigned>> myVector{};
    for (int i = 0; i < s.size(); i++)
    {
        for (int j = 0; j < s.size(); j++)
        {
            if (s[i] == s[j])
            {
                count++;
            }
        }
        myMap.emplace(s[i], count);
        count = 0;
    } // мы записали в неупорядочный уникальный map все данные о буквах и их количествах. За ключ мы взяли букву, и, т.к. map уникальный (не мультимап), то буквы в 
    // записанном контейнере не повторяются (что нам важно для вывода), повторяются лишь значения (что нам не важно для вывода). 
    // далее переписываем в вектор для применения функции std::sort(). 
    for (const auto& temp : myMap) 
    {
        myVector.push_back(temp);
    }
    std::sort(myVector.begin(), myVector.end(), [](const auto& temp, const auto& temp_1) {
        return temp.second > temp_1.second;
        }); //сравниваем по второму параметру пары, т.е. по числу (usigned).
    for (auto& temp : myVector)
    {
        std::cout << temp.first << ": " << temp.second << std::endl;
    }
    return 0;
}
