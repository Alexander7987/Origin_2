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

    smart_array(const smart_array& arr) : n(arr.n)
    {
        create_arr = new int[n]; //выделяем память
        i = arr.i; //передаем текущий счетчик заполненности аргумента конструктора, чтобы с него начать заполнение в объекте, который создаем с нуля
        for (int j = 0; j < arr.n; j++)
            create_arr[j] = arr.create_arr[j];
    }

    void add_element(int k) //добавляем в массив
    { 
        if (i >= n || n == 0)
            throw std::exception();
        else
        {
            i++;
            create_arr[i] = k;
        }
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
        if (this != &arr) //чтобы не присваивать одинаковые объекты классов (напрмер arr_1 = arr_1)
        {
            n = arr.n;
            i = arr.i; //передаем текущий счетчик заполненности копируемого массива, чтобы с него начать заполнение в объекте, внутрь которого скопировали.
            for (int j = 0; j < n; j++)
                create_arr[j] = arr.create_arr[j];
            return *this;
        }
        else
            throw std::exception();
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
        smart_array arr_1(5);
        arr_1.add_element(1);
        arr_1.add_element(4);
        arr_1.add_element(155);

        smart_array arr_2(3);
        arr_2.add_element(44);
        arr_2.add_element(34);

        smart_array arr_3(arr_1); //создаем новый объект на основе arr_1

        arr_1 = arr_2; //копируем, удаляя идентичность arr_1

        std::cout << arr_1.get_element(1) << std::endl;
        std::cout << arr_2.get_element(1) << std::endl;

        std::cout << arr_3.get_element(1) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}