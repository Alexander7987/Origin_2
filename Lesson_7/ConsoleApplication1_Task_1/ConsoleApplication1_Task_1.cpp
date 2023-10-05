#include <iostream>
#include <vector>
#include <algorithm>

void foo(std::vector<int>& myVector)
{
    sort(myVector.begin(), myVector.end());
    auto result = unique(myVector.begin(), myVector.end());
    myVector.erase(result, myVector.end());
}

int main()
{
    std::vector<int> myVector{ 1, 1, 2, 5, 6, 1, 2, 4 };
    std::cout << "[IN]: ";
    for (int i = 0; i < myVector.size(); i++)
    {
        std::cout << myVector[i] << " ";
    }
    foo(myVector);
    std::cout << std::endl << "[OUT]: ";
    for (int i = 0; i < myVector.size(); i++)
    {
        std::cout << myVector[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}


/* сложный вариант с использованием remove_if
std::vector<int>::iterator result;
auto iter = myVector.begin();
for (int i = 0; i < myVector.size(); i++)//мы можем не знать, будет ли уменьшаться размер вектора при 
    //срабатываении erase в цикле, поэтому оставляем i < myVector size()
{
    result = remove_if(next(iter), myVector.end(), [&iter](int& a) {
        return a == *iter;
        });
    myVector.erase(result, myVector.end());
    iter++;
}
sort(myVector.begin(), myVector.end());
for (int i = 0; i < myVector.size(); i++)
{
    std::cout << myVector[i] << " ";
}*/