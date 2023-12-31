﻿#include <iostream>
#include <memory>


template<typename T>
class my_unique_ptr
{
private:
    T* ptr;
    bool released; //добавляем флаг для безопасного использования release()
public:

    my_unique_ptr() //конструктор, принимающий сырой указатель
    {
        this->ptr = nullptr;
    }

    my_unique_ptr(T* ptr) : released(false) //как только создали объект(или переопределили с помощью функтора)
        //то присваиваем переменной released false, т.к. для этого объекта этот метод еще не был использован
    {
        this->ptr = ptr;
    }

    my_unique_ptr& operator ()(T* ptr) //функтор для переопределения объекта после использования метода release()
    {
        this->ptr = ptr;
        released = false; //т.к. создали(переопределили) заново через функтор объект
        return *this;
    }

    T& operator * () //перегружен оператор * для получения объекта
    {
        return *ptr;
    }

    my_unique_ptr(const my_unique_ptr&) = delete;  //запрет конструктора копирования
    my_unique_ptr& operator = (const my_unique_ptr&) = delete; //запрет оператора присваивания

    T* release()
    {
        if (!released)
        {
            delete ptr; // this->ptr = nullptr; - если прописываем это вместо "delete ptr", то флаг released не нужен, т.к.
            //в деструкторе вызов delete по отношению к нулевому указателю вполне легален (см. комментарий от преподавателя)
            released = true;
            return ptr;
        }
    }

    ~my_unique_ptr()
    {
        if (!released)
        delete ptr;
    }
};


int main()
{
    my_unique_ptr<int> my_ptr = new int(5);
    std::cout << *my_ptr << std::endl;
    *my_ptr = 22;
    std::cout << *my_ptr << std:: endl;
    my_ptr.release();
    my_ptr (new int(8));
    std::cout << *my_ptr << std::endl;
    return 0;
}