#include <iostream>
#include <Windows.h>

class smart_array
{
private:
	const int n;
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
	smart_array(const smart_array&) = delete; //запрещаем конструктор копирования
	smart_array& operator=(const smart_array&) = delete; //запрещаем оператор присваивания

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
		arr.add_element(14);
		arr.add_element(15);
		//arr.add_element(15); //случай, когда переполнение массива.
		std::cout << arr.get_element(3) << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}