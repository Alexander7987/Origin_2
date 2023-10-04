#include <iostream>
#include <Windows.h>

template<typename T>
class myVector
{
private:
    int counter = 0;
    int value_for_capacity = 0;
    T* array = nullptr;
public:

    myVector(const myVector&) = delete;
    myVector& operator = (const myVector&) = delete;

    myVector() //конструктор по умолчанию для создания пустого вектора
    {
        this->array = nullptr;
        this->counter = 0;
        this->value_for_capacity = 0;
    }

    ~myVector()
    {
        delete []array;
    }

    T at(int index)
    {
        if (index < this->counter && index >= 0)
            return array[index];
        else
            throw std::exception();
    }

    void push_back(T value)
    {
        if (array == nullptr)
        {
            this->counter++;
            this->value_for_capacity = this->counter * 2;
            array = new T[this->value_for_capacity];
            array[this->counter - 1] = value;
        }
        else if (this->counter == this->value_for_capacity - 1) //увеличиваем запас на х2 когда заполненяем последнюю ячейку вектора
        {
            this->counter++;
            T* temp = array;
            this->value_for_capacity = this->counter * 2;
            array = new T[this->value_for_capacity];
            for (int i = 0; i < this->counter - 1; i++)
            {
                array[i] = temp[i];
            }
            array[this->counter - 1] = value;
            delete temp; 
        }
        else
        {
            this->counter++;
            array[this->counter - 1] = value;
        }
    }
    int size()
    {
        return this->counter;
    }

    int capacity()
    {
        return this->value_for_capacity;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    myVector<int> vector; //явно указываем тип шаблона
    vector.push_back(5);
    vector.push_back(8);
    vector.push_back(9);
    vector.push_back(11);
    std::cout << "capacity: " << vector.capacity() << std::endl;
    std::cout << "первый элемент: " << vector.at(0) << std::endl;
    std::cout << "второй элемент: " << vector.at(1) << std::endl;
    std::cout << "третий элемент: " << vector.at(2) << std::endl;
    std::cout << "четвертый элемент: " << vector.at(3) << std::endl;
    try
    {
        vector.at(15);
    }
    catch (const std::exception& err)
    {
        std::cout << err.what() << std::endl;
    }
    std::cout << "size: " << vector.size() << std::endl;
    return 0;
}