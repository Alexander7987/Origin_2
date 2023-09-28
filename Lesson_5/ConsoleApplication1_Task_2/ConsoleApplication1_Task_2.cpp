#include <iostream>
#include <Windows.h>

template<typename T>
class table
{
private:
    T** test;
    int row, column;
public:
    table(int row, int column)
    {
        this->row = row;
        this->column = column;
        test = new T* [this->row];
        for (int i = 0; i < this->row; i++)
        {
            test[i] = new T[this->column];
        }
    }
    ~table()
    {
        for (int i = 0; i < this->row; i++)
        {
            delete []test[i];
        }
        delete test;
    }

    void Size()
    {
        std::cout << std::endl << "Размер таблицы: " << this->row << " x " << this->column << std::endl;
    }

    T* operator [](const int index)
    {
       try
       {
           if (index < row)
               return test[index];
           else
               throw std::logic_error("Wrong index");
       }
       catch (std::logic_error& logic)
       {
           std::cout << logic.what();
       }
    }
    T* operator [](const int index) const
    {
        try
        {
            if (index < row)
                return test[index];
            else
                throw std::logic_error("Wrong index");
        }
        catch (std::logic_error& logic)
        {
            std::cout << logic.what();
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    table<int> test(2, 3);
    test[0][0] = 4;  //в классе перегружаем для объектов класса "[]" для того, чтобы вернуть от туда указатель на строку двумерного массива, которая, в свою очередь, является 
    // одномерным динамическим массивом, в котором располагаются уже непосредственно сами числа. Получив указатель на одномерный динамический массив применяем к нему уже обычный
    // оператор "[]" (не перегруженный), в который передаем нужный индекс по столбцам. Почему компилятор определяет вторые скобки как не перегруженные? Потому что их вызывает
    // уже указатель на одномерный динамический массив, который мы получили от перегрузки "первого" оператора [].
    std::cout << test[0][0];
    std::cout << std::endl;
    test.Size();
    return 0;
}
