#pragma once
#include <string>
#include <vector>
#include <variant>

class ini_parser
{
public:
	ini_parser(std::string stemp);
	template<typename T>
	std::variant<double, int, std::string, std::vector <std::pair <std::string, std::string>>> get_value(std::string my_string);
};
