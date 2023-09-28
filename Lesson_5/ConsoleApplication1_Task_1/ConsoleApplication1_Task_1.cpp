#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <cmath>

template<typename T>  //для дальнейших специализаций оставляем шаблон пустым
void power(T &temp)
{
}

template<>
void power(int &temp)
{
	temp = pow(temp, 2);
}

template<>
void power(std::vector<int> &temp)
{
	std::for_each(temp.begin(), temp.end(), [&temp](int& a) {
		a = pow(a, 2);
		});
}



int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int a, b, t;
	std::vector<int> my_vector{};
	auto print_my_vector([](const int h) {
		std::cout << h << " ";
		});
	std::cout << "Введите число для возведения в квадрат: ";
	std::cin >> a;
	std::cout << "Сколько элементов в векторе: ";
	std::cin >> b;
	for (int i = 0; i < b; i++)
	{
		std::cout << "Введите число для добавления в вектор: ";
		std::wcin >> t;
		my_vector.push_back(t);
	}
	std::cout << "[IN]: " << a << std::endl << "[OUT]: ";
	std::for_each(my_vector.begin(), my_vector.end(), print_my_vector);
	power<int>(a);
	power<std::vector<int>> (my_vector);
	std::cout << std::endl << "[IN]: " << a << std::endl << "[OUT]: ";
	std::for_each(my_vector.begin(), my_vector.end(), print_my_vector);
	return 0;
}

