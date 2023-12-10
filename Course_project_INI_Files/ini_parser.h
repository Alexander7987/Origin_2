// Хедер ini_parser.h для класса и реализации шаблонного метода (определяется в хедере, т.к. является шаблоном)
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <variant>
#include <algorithm>




class ini_parser
{
private:
	std::string s = "";
	std::vector <std::string> vector_of_sections{};
	std::vector <std::vector <std::pair <std::string, std::string>>> vector_of_value{};
	//int e = -1;


public:

	ini_parser(std::string stemp);


	template<typename T>
	T get_value(std::string my_string)//std::variant<double, int, std::string, std::vector <std::pair <std::string, std::string>>> get_value(std::string my_string)
	{
		//ЕСЛИ СЮДА ПОПАЛИ, ТО ЗНАЧЕНИЕ ЯВЛЯЕТСЯ ЧИСЛОМ. ЭТОТ ШАБЛОН ПОКА ЧТО НАСТРОЕН НА int и double
		T result{};
		int temp_int = 0;
		int counter_for_search = 0;
		int temp_i = 0;
		int temp_ii = 0;
		std::string s4 = ""; //сюда запишем секцию, которую ищем
		std::string s5 = ""; //сюда запишем имя переменной, которую ищем
		while (my_string[temp_i] != '.')
		{
			s4 += my_string[temp_i];
			temp_i++;
		}
		for (int i = temp_i + 1; i < my_string.size(); i++)
			s5 += my_string[i];


		for (int i = 0; i < vector_of_sections.size(); i++) //ищем секцию
		{
			if (vector_of_sections.at(i) == s4)
			{
				counter_for_search = i;
				temp_ii = 1;
				break;
			}
		}


		if (temp_ii == 1) //если нашли такую секцию, ищем запрашиваемую переменную
		{
			for (int i = 0; i < vector_of_value.at(counter_for_search).size(); i++) // идем по вектору переменных
			{
				if (vector_of_value.at(counter_for_search).at(i).first == s5) // нашли переменную (ранее в конструкторе значение проверено на ошибки)
				{
					for (int j = 0; j < vector_of_value.at(counter_for_search).at(i).second.size(); j++) //ОПРЕДЕЛИМ, ЭТО ВЕЩЕСТВЕННОЕ ИЛИ ЦЕЛОЕ ЧИСЛО
					{
						if (vector_of_value.at(counter_for_search).at(i).second[j] == '.') // если сюда попали, то вещественное
						{
							if (std::is_same<T, double>::value)
							{
								result = std::stod(vector_of_value.at(counter_for_search).at(i).second); // конвертируем строку в double и передаем в result которая уже является double
								return result;
							}
							else
							{
								throw "The requested number type does not match the actual one"; //throw "Запрашиваемый тип числа не соответствует фактическому";
							}
						}
					}



					if (std::is_same<T, int>::value) // ЕСЛИ СЮДА ПОПАЛИ, ТО ЦЕЛОЕ
					{
						result = std::stoi(vector_of_value.at(counter_for_search).at(i).second); // конвертируем строку в int и передаем в result которая уже является int
						return result;
					}
					else
					{
						throw "The requested number type does not match the actual one"; // throw "Запрашиваемый тип числа не соответствует фактическому";
					}
				}
				else if (i == vector_of_value.at(counter_for_search).size() - 1)
				{
					std::cout << "There is no such variable, but there are other variables in this section: " << std::endl; //std::cout << "Такой переменной нет, но в этой секции есть другие переменные: " << std::endl;
					std::for_each(vector_of_value.at(counter_for_search).begin(), vector_of_value.at(counter_for_search).end(), [](std::pair <std::string, std::string> my_pair) {
						std::cout << my_pair.first << std::endl;
						});
					throw "Exit from programm";
				}
			}
		}
		else //если нет такой секции, то вывести предупреждение
		{
			throw "There is no such section"; // throw "Такой секции нет";
		}
	}



	// ВНИМАНИЕ! Для строкового типа делаем отдельную специализацию, т.к. если T будет равен int, double и т.п., а переменная в файле является строкой, то её по правилам
	// C++ нельзя конвертировать в число, будет ошибка C2440!
	// ВНИМАНИЕ! Если пользователь хочет получить строку, то, если в переменной записано число, оно будет превращено в строку и возвращено типом строка!
	template<>
	std::string get_value(std::string my_string)
	{

		int counter_for_search = 0;
		int temp_i = 0;
		int temp_ii = 0;
		std::string s4 = ""; //сюда запишем секцию, которую ищем
		std::string s5 = ""; //сюда запишем имя переменной, которую ищем
		while (my_string[temp_i] != '.')
		{
			s4 += my_string[temp_i];
			temp_i++;
		}
		for (int i = temp_i + 1; i < my_string.size(); i++)
			s5 += my_string[i];


		for (int i = 0; i < vector_of_sections.size(); i++) //ищем секцию
		{
			if (vector_of_sections.at(i) == s4)
			{
				counter_for_search = i;
				temp_ii = 1;
				break;
			}
		}


		if (temp_ii == 1) //если нашли такую секцию, ищем запрашиваемую переменную
		{
			for (int i = 0; i < vector_of_value.at(counter_for_search).size(); i++) // идем по вектору переменных
			{
				std::string gh = vector_of_value.at(counter_for_search).at(i).first;
				if (vector_of_value.at(counter_for_search).at(i).first == s5) // если нашли переменную, определим, число это или строка (ранее в конструкторе значение проверено на ошибки)
				{
					return vector_of_value.at(counter_for_search).at(i).second;
				}
				else if (i == vector_of_value.at(counter_for_search).size() - 1)
				{
					std::cout << "There is no such variable, but there are other variables in this section: " << std::endl; //std::cout << "Такой переменной нет, но в этой секции есть другие переменные: " << std::endl;
					std::for_each(vector_of_value.at(counter_for_search).begin(), vector_of_value.at(counter_for_search).end(), [](std::pair <std::string, std::string> my_pair) {
						std::cout << my_pair.first << std::endl;
						});
					throw "Exit from programm";
				}
			}
		}
		else //если нет такой секции, то вывести предупреждение
		{
			throw "There is no such section"; // throw "Такой секции нет";
		}
	}
};