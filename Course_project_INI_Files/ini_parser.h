// ����� ini_parser.h ��� ������ � ���������� ���������� ������ (������������ � ������, �.�. �������� ��������)
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
		//���� ���� ������, �� �������� �������� ������. ���� ������ ���� ��� �������� �� int � double
		T result{};
		int temp_int = 0;
		int counter_for_search = 0;
		int temp_i = 0;
		int temp_ii = 0;
		std::string s4 = ""; //���� ������� ������, ������� ����
		std::string s5 = ""; //���� ������� ��� ����������, ������� ����
		while (my_string[temp_i] != '.')
		{
			s4 += my_string[temp_i];
			temp_i++;
		}
		for (int i = temp_i + 1; i < my_string.size(); i++)
			s5 += my_string[i];


		for (int i = 0; i < vector_of_sections.size(); i++) //���� ������
		{
			if (vector_of_sections.at(i) == s4)
			{
				counter_for_search = i;
				temp_ii = 1;
				break;
			}
		}


		if (temp_ii == 1) //���� ����� ����� ������, ���� ������������� ����������
		{
			for (int i = 0; i < vector_of_value.at(counter_for_search).size(); i++) // ���� �� ������� ����������
			{
				if (vector_of_value.at(counter_for_search).at(i).first == s5) // ����� ���������� (����� � ������������ �������� ��������� �� ������)
				{
					for (int j = 0; j < vector_of_value.at(counter_for_search).at(i).second.size(); j++) //���������, ��� ������������ ��� ����� �����
					{
						if (vector_of_value.at(counter_for_search).at(i).second[j] == '.') // ���� ���� ������, �� ������������
						{
							if (std::is_same<T, double>::value)
							{
								result = std::stod(vector_of_value.at(counter_for_search).at(i).second); // ������������ ������ � double � �������� � result ������� ��� �������� double
								return result;
							}
							else
							{
								throw "The requested number type does not match the actual one"; //throw "������������� ��� ����� �� ������������� ������������";
							}
						}
					}



					if (std::is_same<T, int>::value) // ���� ���� ������, �� �����
					{
						result = std::stoi(vector_of_value.at(counter_for_search).at(i).second); // ������������ ������ � int � �������� � result ������� ��� �������� int
						return result;
					}
					else
					{
						throw "The requested number type does not match the actual one"; // throw "������������� ��� ����� �� ������������� ������������";
					}
				}
				else if (i == vector_of_value.at(counter_for_search).size() - 1)
				{
					std::cout << "There is no such variable, but there are other variables in this section: " << std::endl; //std::cout << "����� ���������� ���, �� � ���� ������ ���� ������ ����������: " << std::endl;
					std::for_each(vector_of_value.at(counter_for_search).begin(), vector_of_value.at(counter_for_search).end(), [](std::pair <std::string, std::string> my_pair) {
						std::cout << my_pair.first << std::endl;
						});
					throw "Exit from programm";
				}
			}
		}
		else //���� ��� ����� ������, �� ������� ��������������
		{
			throw "There is no such section"; // throw "����� ������ ���";
		}
	}



	// ��������! ��� ���������� ���� ������ ��������� �������������, �.�. ���� T ����� ����� int, double � �.�., � ���������� � ����� �������� �������, �� � �� ��������
	// C++ ������ �������������� � �����, ����� ������ C2440!
	// ��������! ���� ������������ ����� �������� ������, ��, ���� � ���������� �������� �����, ��� ����� ���������� � ������ � ���������� ����� ������!
	template<>
	std::string get_value(std::string my_string)
	{

		int counter_for_search = 0;
		int temp_i = 0;
		int temp_ii = 0;
		std::string s4 = ""; //���� ������� ������, ������� ����
		std::string s5 = ""; //���� ������� ��� ����������, ������� ����
		while (my_string[temp_i] != '.')
		{
			s4 += my_string[temp_i];
			temp_i++;
		}
		for (int i = temp_i + 1; i < my_string.size(); i++)
			s5 += my_string[i];


		for (int i = 0; i < vector_of_sections.size(); i++) //���� ������
		{
			if (vector_of_sections.at(i) == s4)
			{
				counter_for_search = i;
				temp_ii = 1;
				break;
			}
		}


		if (temp_ii == 1) //���� ����� ����� ������, ���� ������������� ����������
		{
			for (int i = 0; i < vector_of_value.at(counter_for_search).size(); i++) // ���� �� ������� ����������
			{
				std::string gh = vector_of_value.at(counter_for_search).at(i).first;
				if (vector_of_value.at(counter_for_search).at(i).first == s5) // ���� ����� ����������, ���������, ����� ��� ��� ������ (����� � ������������ �������� ��������� �� ������)
				{
					return vector_of_value.at(counter_for_search).at(i).second;
				}
				else if (i == vector_of_value.at(counter_for_search).size() - 1)
				{
					std::cout << "There is no such variable, but there are other variables in this section: " << std::endl; //std::cout << "����� ���������� ���, �� � ���� ������ ���� ������ ����������: " << std::endl;
					std::for_each(vector_of_value.at(counter_for_search).begin(), vector_of_value.at(counter_for_search).end(), [](std::pair <std::string, std::string> my_pair) {
						std::cout << my_pair.first << std::endl;
						});
					throw "Exit from programm";
				}
			}
		}
		else //���� ��� ����� ������, �� ������� ��������������
		{
			throw "There is no such section"; // throw "����� ������ ���";
		}
	}
};