#include <iostream>
#include <Windows.h>

class smart_array
{
private:
    int n;
    int* create_arr;
    int i = -1;// счетчик для массива
public:
    smart_array(const int& a) : n(a)
    {
        create_arr = new int[n] {}; //выделяем память
    }


    void add_element(int k) //добавляем в массив
    {
        i++;
        if (i >= n)
            throw std::exception();
        create_arr[i] = k;
    }


    int get_element(int q) //выводим выбранный эл-нт на консоль
    {
        if (q < 0 || q > n)
            throw std::exception();
        else
            return create_arr[q];
    }

    smart_array& operator = (const smart_array& arr)
    {
        if (this != &arr)
        {
            n = arr.n;
            for (int j = 0; j < n; j++)
                create_arr[j] = arr.create_arr[j];
        }
        return *this;
    }

    ~smart_array() //удаляем после срабатывания исключения или по завершению программы.
    {
        delete[]create_arr;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array;
        std::cout << arr.get_element(1) << std::endl;
        std::cout << new_array.get_element(1) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}