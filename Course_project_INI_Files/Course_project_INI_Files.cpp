#include <ini_parser.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <variant>
#include <algorithm>

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	try
	{
		ini_parser parser("filename");
		auto value = parser.get_value<int>("Section4.var99");
		if (std::holds_alternative<int>(value))
		{
			auto result_int = std::get<int>(value);
			std::cout << result_int;
		}
		else if (std::holds_alternative<double>(value))
		{
			auto& result_string = std::get<double>(value);
			std::cout << result_string;
		}
		else if (std::holds_alternative<std::string>(value))
		{
			auto& result_string = std::get<std::string>(value);
			std::cout << result_string;
		}
		else if (std::holds_alternative<std::vector <std::pair <std::string, std::string>>>(value))
		{
			auto& result_vector = std::get<std::vector <std::pair <std::string, std::string>>>(value);
			std::for_each(result_vector.begin(), result_vector.end(), [](const std::pair <std::string, std::string>& my_vector) {
				std::cout << my_vector.first << std::endl;
				});
		}
	}
	catch (const int& e)
	{
		std::cout << "Проблема в строке " << e;
	}
	return 0;
}
