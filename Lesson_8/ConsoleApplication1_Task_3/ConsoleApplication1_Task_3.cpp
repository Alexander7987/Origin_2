#include <iostream>
#include <memory>


template<typename T>
class my_unique_ptr
{
private:
    T* ptr;
public:

    my_unique_ptr() //конструктор, принимающий сырой указатель
    {
        this->ptr = nullptr;
    }

    my_unique_ptr(T* ptr)
    {
        this->ptr = ptr;
    }

    T& operator * () //перегружен оператор * для получения объекта
    {
        return *ptr;
    }

    my_unique_ptr(const my_unique_ptr&) = delete;  //запрет конструктора копирования
    my_unique_ptr& operator = (const my_unique_ptr&) = delete; //запрет оператора присваивания

    my_unique_ptr& release()
    {
        delete this->ptr;
        return *this;
    }

    ~my_unique_ptr()
    {
        delete ptr;
    }
};


int main()
{
    my_unique_ptr<int> my_ptr = new int(5);
    std::cout << *my_ptr << std::endl;
    my_ptr.release();
    *my_ptr = 22;
    std::cout << *my_ptr;
    return 0;
}