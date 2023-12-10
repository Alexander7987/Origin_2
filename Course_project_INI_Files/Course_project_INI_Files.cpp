// CPP для головного файла
#include <ini_parser.h>
#include <MyParserError.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <variant>
#include <algorithm>

int main()
{
	//setlocale(LC_ALL, "Russian"); // отключаем русскую локализацию, т.к. число в файле в русской версии не воспринимается как дробное, если писать через точку. 
	//SetConsoleOutputCP(1251); // Для того, чтобы работать с дробными числами в файле, необходимо писать в числах запятую, если работаем с русской локализацией.
	//SetConsoleCP(1251);
	try
	{
		ini_parser parser("filename");
		auto value = parser.get_value <std::string> ("Section1.var_7543");
		std::cout << value;
	}
	catch (const char* ex)
	{
		std::cout << ex;
	}
	catch (const MyParserError& ex)
	{
		std::cout << ex.what();
	}

	return 0;
}