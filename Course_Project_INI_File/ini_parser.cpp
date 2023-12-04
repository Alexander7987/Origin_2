#include <ini_parser.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <variant>


ini_parser::ini_parser(std::string stemp)
{
	this->s = stemp + ".ini";
	int point_one = 0, point_two = 0;
	int for_value = 0;
	int temp_int = 0;
	int error_string = 0;
	int j = 0, count_string = 0;
	std::ifstream f(s);
	std::string s1 = "";
	std::string s2 = "";
	std::string s3 = "";
	int counter_for_sections = 0; // ����� ������� ������ ������� vector_of_sections

	// ������ ����� �� ������� //
	f.close();
	f.open(s);
	while (getline(f, s1))
	{
		count_string++;
		for_value = 0;
		error_string = 0;

		// ���� ������ ������, ����������
		for (int i = 0; i < s1.size(); i++)
		{
			temp_int = static_cast<int>(s1[i]);
			if (s1[i] == 32)
				error_string = 0;
			else
			{
				error_string = 1;
				break;
			}
		}
		if (error_string == 1)
		{
			error_string = 0;
		}
		else
			continue;



		// ����� ������, �������� �� ��� ������ ������ ������ ��� ����������� ����������
		for (int i = 0; i < s1.size(); i++)
		{
			if (s1[i] == '=')
				for_value++;
		}
		if (for_value > 1) //������, ����� ���� ��������� '='
		{
			e = count_string;
			break;
		}


		for (int i = 0; i < s1.size(); i++)
		{
			if (s1[i] == '[' || s1[i] == ']' || s1[i] == ';')
			{
				error_string = 1;
				break;
			}
		}


		if (error_string == 0 && for_value == 0) //���� ������ ��� ������ "=" � "[", "]", ��� ������
		{
			e = count_string;
			break;
		}


		if (e != -1) //�������� ��������� � ����� �� ����� � �����������. 
		{
			throw e;
		}

		/// ������ ��������� � ������ ���� �����///
		for (int i = 0; i < s1.size(); i++)
		{
			if (s1[i] == ';')//����������� �� ���������� ��� ������, �������������, ������� �� ������ ������
				break;


			temp_int = static_cast<int>(s1[i]); //�� ����������� ���� �������� � ����� ����� ����, ����, � " ", "_", ".", "="
			if ((temp_int >= 0 && temp_int <= 31) || (temp_int >= 33 && temp_int <= 45) || temp_int == 47 || (temp_int >= 58 && temp_int <= 60) || (temp_int >= 62 && temp_int <= 64) || temp_int == 92 || temp_int == 94 || temp_int == 96 || (temp_int >= 123 && temp_int <= 127)) //��������� ������� �����������
			{
				e = count_string;
				break;
			}


			if (s1[i] == ' ' && i != s1.size() - 1 && point_one != 1 && for_value != 1) //���� ������, �� ���������� � ������ ���� "[" ��� ������. 
				//���� ������ ������, �� ������ ������, ������� ������������ � if (s1[i] == ' ' && point_one == 1). ���� ������ ������� ���������� (���� for_value == 1),
				//�� ������ � if (s[i] == ' ' && for_value = 1), ��� ���������� ���� ������ � ������
				continue;


			if (s1[i] == ' ' && for_value == 1) //���������� ���� �������, ���� ��������� � ������, ��� ����������� ����������, ����� ����� ����� ������, ���� ��������� ��������/����������
			{
				s2 += s1[i];
				continue;
			}


			if (s1[i] == ' ' && point_one == 1) // ���� � �������� ������ ���� ������, ��� ������
			{
				e = count_string;
				break;
			}


			if (s1[i] == ' ' && i == s1.size() - 1) //���� ������ � �����, �� ���� ������
				continue;


			if (s1[i] != ';' && s1[i] != '[' && point_one != 1 && point_one != 2) //���������� ������� � ������ � ����� ������, �� ���� ����� ����� "[", �� ����� ������
			{//������� point_one != 2 ��� ����, ����� ������� � if (point_one == 2 && (s1[i] != ' ' || s1[i] != '/n'))
				s2 += s1[i]; // ������� point_one != 1 ��� ����, ����� �� ����������� � s2 �������, ������� ���������� ������ ������ [] ��� ����� ����������� "[" � �� "["
				continue;
			}


			if (s1[i] == '[' && point_one == 0) //����� ����� ������� �������� ������ (0 - ���� "[", 1 - ���� ������)
			{
				if (s2 != "") //���� ���� ������� �� �������� ������ "[", �� ��� ������
				{
					e = count_string;
					break;
				}
				point_one = 1;
				continue; //����� ����� continue ����� ������
			}


			if (s1[i] == '[' && point_one == 1) //������, ����� � �������� ������ ��� ���� ����������� "["
			{
				e = count_string;
				break;
			}


			if (point_one == 1 && s1[i] != ']' && i != s1.size() - 1) //����� ������ �������� ������. � ������ "]" �� �� ������ � ���������� � �������� ������
				//���� ��� ��������� ������, �� ������ "]", �� ������������ � if (i == s1.size() - 1 && point_one == 1)
			{
				if (s1[i] == '=') //�� ����������� ���� "=" � �������� ������
				{
					e = count_string;
					break;
				}
				s2 += s1[i];
				continue;
			}


			if (s1[i] == ']' && point_one == 1) //2 - ������ ������� � ������������� ����� � ���� ������ ��������
			{
				if (s2 == "") //������ ������, ���� ������ �� �������� ��������, �������� � ����� ��������: []
				{
					e = count_string;
					break;
				}
				point_one = 2;
				continue; //���� ����� ����� continue ���� for ����������� � ��� �������� ������ (����� ' '), �� ������� ������ � if (point_one == 2 && (s1[i] != ' ' || s1[i] != '/n'))
			}


			if (point_one == 2 && (s1[i] != ' ' && s1[i] != '/n')) //2 - ������ ������� � ������������� ����� � ���� ������ �������� ����� �������� � ���������
			{
				e = count_string;
				break;
			}


			if (i == s1.size() - 1 && point_one == 1) //���� ��� ����������� ������, �� ��� ������
			{
				e = count_string;
				break;
			}


			if (point_one == 0 && s1[i] == ']') //���� ��� ����������� ������, �� ��� ������
			{
				e = count_string;
				break;
			}
		} //����� �� ����� ������ ������� ������


		if (e != -1) //�������� ��������� � ����� �� ����� � �����������. 
		{
			throw e;
		}


		/// ����������� ������� � ����� ��������� ���� ������. ����� �� ������� ������ ���� ������ � ��������� ����� ������� ��� � ������ ��������� ///
		if (point_one == 2)
		{
			bool temp = 0;
			point_one = 0;
			for (int i = 0; i < vector_of_sections.size(); i++) //���������, ���� �� ��� ����� ������ � ������� ���� ������
			{
				if (vector_of_sections[i] == s2)
				{
					counter_for_sections = i;
					temp = 1;
					break;
				}
			}

			if (temp == 0)
			{
				vector_of_sections.push_back(s2); //�������� ��� ������ � ������ ���� ������
				vector_of_value.push_back(std::vector <std::pair <std::string, std::string>> {}); // �������� ������, � ������� �������� ���� ���_���������� + �������� ���������� ����������� ���� ������
				// �����, ����� �������� �� 219 � 220 ������� ���� ������, ����� ���� ������������ ������� ����� ������� ���� ������ � �������� ����� ������� ����������
				counter_for_sections = vector_of_sections.size() - 1;
			}
			s2 = "";
			continue;
		}


		/// ����������� ������� � ����� ��������� ����� ����������. ��� ������, ��� ���� "=" ����� ������ �� ����� ��������� �����������, ��� �������� for_value = 1; ///
		// �������� ���������� ������������ ����� ������, ����� ������ ����������� �� �������� � ������ ����� for, �.�. ��� ����� ������
		if (for_value == 1) //���� ���� ��������, �� �������� ��� ������������ ������ s2,�.�. ����� �� ����������� ���� �������� � ����� ����� ����, ����, � "_", ".", "=", " "
		{
			int flag_it_string = 0;
			int counter = 0;
			int tempp = -1;
			int temp = 0; //0 - ������ �������, 1 - ������ �������, 2 - ������ ������� ��� ������ �������� ����������
			s3 = ""; // ������ ��� ������ ��� ���������� � �� ��������
			for (int i = 0; i < s2.size(); i++)
			{
				if (s2[i] == ' ' && s3 == "" && temp != 2) //� ������ ���������� ��� ������� ���� ��� �� ������ ��������
					continue;
				if (s2[i] != ' ' && s2[i] != '=' && temp == 0) // ��������� ������ � ���������� ��� ����������
				{
					s3 += s2[i];
					continue;
				}
				if (s2[i] == ' ' && temp == 0) //��������� ������ � ������ ������� � �������� ����� ����, ��� ������ ���� �������
				{
					temp = 1;
					continue;
				}
				if (s2[i] != ' ' && temp == 1 && s2[i] != '=') //������������� ������ ������ ������� ����� ' ' � "=" ����� ��������
				{
					e = count_string;
					break;
				}
				if (s2[i] == ' ' && temp == 1) //���������� ��� ������� ����� ��������
					continue;


				if (s2[i] == '=' && i == s2.size() - 1) //���� "=" ��������� � ������, �� �������� ��� ���������� ���
				{
					if (s3 == "") //��� ���������� �� ������ ���� ������
					{
						e = count_string;
						break;
					}
					else
					{
						for (int k = 0; k < vector_of_value.at(counter_for_sections).size(); k++) // ���������, ���� �� ��� ����� ���������� � ������� ����������
						{
							if (vector_of_value.at(counter_for_sections).at(k).first == s3) // �, ���� ����, �� ������� ������ �������� �� ������
							{
								vector_of_value.at(counter_for_sections).at(k).second = "";
								tempp = 1;
								break;
							}
						}
						if (tempp == 1) //  � ����� �� �����, �.�. ��� ������ ������ ������ (�������� ��� ���������� ���)
						{
							s3 = "";
							break;
						}
						else
						{
							vector_of_value.at(counter_for_sections).push_back(std::make_pair(s3, "")); // � ���� ���, �� �������� ��� ����� ����������
							s3 = "";
							break; // � ����� �� �����, �.�. ��� ������ ������ ������ (�������� ��� ���������� ���)
						}
					}
				}


				if (s2[i] == '=' && i != s2.size() - 1) //���� "=" ����������� � ������, ��������� ��� ������ �������� ����������. ��� ����� ������������� ���� "2", �������� ��� ������ �������� ����������
				{
					if (s3 == "") //��� ���������� �� ������ ���� ������
					{
						e = count_string;
						break;
					}
					else
					{
						for (int k = 0; k < vector_of_value.at(counter_for_sections).size(); k++) // ���������, ���� �� ��� ����� ���������� � ������� ����������
						{
							if (vector_of_value.at(counter_for_sections).at(k).first == s3) // �, ���� ����, �� �� ���������� � ������, � ���� ����� �������� �������� ���� ����������
							{
								tempp = k;
								break;
							}
						}
						if (tempp != -1) // �, ���� ����, �� �� ���������� � ������, � ���� ����� �������� �������� ���� ����������
						{
							s3 = "";
							temp = 2;
							continue;
						}
						else
						{
							vector_of_value.at(counter_for_sections).push_back(std::make_pair(s3, "")); // � ���� ���, �� �������� ���� ��� ������ ��� ����� ����������
							s3 = "";
							temp = 2;
							continue;
						}
					}
				}


				if (temp == 2 && i != s2.size() - 1) // ���������� ��������. ���� �������� �������� �������, �� ����� ��������� ' '. ���� ��� ��������� ������, �� ���� � if (temp == 2 && i == s2.size() - 1)
				{
					if (s2[i] == ' ' && s3 == "") //���� ������ � ������ �������� s3 ������, �.�. ��������� ������� ��� ������ ����������, ���������� ������
						continue;
					else
					{
						temp_int = static_cast<int>(s2[i]);
						if ((temp_int >= 0 && temp_int <= 31) || (temp_int >= 33 && temp_int <= 45) || temp_int == 47 || (temp_int >= 58 && temp_int <= 127))
							flag_it_string = 1; //���� ���� ������, ������ �������� �������� �������
						s3 += s2[i];
						continue;
					}
				}


				if (temp == 2 && i == s2.size() - 1)// � ����� ����� ���������� ���������� �������� ����������. 
				{
					if (s2[i] == ' ' && s3 == "") //���� ��������� ������ ������, � ������ �������� s3 ������, �.�. � ������ ������ �������, �� ��� ������ ����������
					{
						if (tempp != -1) // ������� ����, ���� ���������� ��� ����
						{
							vector_of_value.at(counter_for_sections).at(tempp).second = s3; //�������(������� � ������ �������) ��������, ������� �������� �������
							break;
						}
						else // � ���� ���, �� ������� �������� ������������� ����������
						{
							vector_of_value.at(counter_for_sections).at(vector_of_value.at(counter_for_sections).size() - 1).second = s3; //������� ��������, ������� �������� �������
							break;
						}
						break;
					}
					else if (s2[i] != ' ') //���� ��� �� s3 �� ������, �� ��������� ������ �� ��������� �, ���� ���� ��������� ������ (��� �����), �� ����������
						s3 += s2[i];


					int size_s3 = s3.size();
					for (int m = size_s3 - 1; m >= 0; m--) // ������ � ����� ������� �� ���������� ������ s3 
					{
						if (s3[m] == ' ')
							s3.erase(m, 1);
						else
							break; //��� ������ ��������� ������ ������, ������
					}



					if (flag_it_string == 1) //����� ��� ������
					{
						if (tempp != -1) // ������� ����, ���� ���������� ��� ����
						{
							vector_of_value.at(counter_for_sections).at(tempp).second = s3; //�������(������� � ������ �������) ��������, ������� �������� �������
							break;
						}
						else // � ���� ���, �� ������� �������� ������������� ����������
						{
							vector_of_value.at(counter_for_sections).at(vector_of_value.at(counter_for_sections).size() - 1).second = s3; //������� ��������, ������� �������� �������
							break;
						}
					}

					///// ���� ��� ����� (�.�. flag_it_string = 0), ��������� ���� ���� ///////
					int flag_for_point = 0;
					for (int j = 0; j < s3.size(); j++) // ���� �� ����������� � s3 ��������
					{
						temp_int = static_cast<int>(s3[j]);
						if (temp_int >= 48 && temp_int <= 57 && counter != 3) //����� �� ����������� �������� � ����� ������ ������� "."
						{
							if (counter == 2)
							{
								flag_for_point = 0; // �������� ������, ���� ����� ����� ���� �����-�� ����� (�.�. �� ������, �� ������, ��� ��� ����)
								continue;
							}
							counter = 1;
							continue;
						}
						if (counter == 1 && temp_int == 46) //������ ����� ����� ����� �����. 46 - ��� ������� �����
						{
							if (j == s3.size() - 1) //������, ����� ����� ���� ��������� ��������
							{
								e = count_string;
								break;
							}
							flag_for_point = 1; // ������, ��� ����� ����� ������� ���� �����-�� �����
							counter = 2;
							continue;
						}
						if (s3[j] == ' ' && (counter == 1 || counter == 2)) // ��������� ������ ��� ���� ����� ����� ������� ������� � ����� (���� ��� �����, �� counter == 1 ��� 2)
						{
							if (flag_for_point == 1 && j == s3.size() - 1) //������, ����� ����� ���� ��������� ��������
							{
								e = count_string;
								break;
							}
							counter = 3;
							continue;
						}
						if (counter == 2 && temp_int == 46) //�� ����������� ����� ������ ������� "."
						{
							e = count_string;
							break;
						}
						if (counter == 3 && (temp_int >= 48 && temp_int <= 57)) // ���� ���� ����� ����� ��������, ��� ������
						{
							e = count_string;
							break;
						}
					}

					if (tempp != -1) // ������� ����, ���� ���������� ��� ����
					{
						vector_of_value.at(counter_for_sections).at(tempp).second = s3; //�������(������� � ������ �������) ��������, ������� �������� �������
						break;
					}
					else // � ���� ���, �� ������� �������� ������������� ����������
					{
						vector_of_value.at(counter_for_sections).at(vector_of_value.at(counter_for_sections).size() - 1).second = s3; //������� ��������, ������� �������� �������
						break;
					}
					s3 = ""; //�������� ��� ���������� ������
				}		
			}
		}
		for_value = 0;
		s2 = "";
	} //����� �� ����� ������ ����� �����
	if (e != -1) //�������� ��������� � ����� �� ����� � �����������
	{
		throw e;
	}
	f.close();
}






template<typename T>
std::variant<double, int, std::string, std::vector <std::pair <std::string, std::string>>> ini_parser::get_value(std::string my_string)
{
	double double_for_return = 0.0;
	int int_for_return = 0;
	int flag_it_string = 0;
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


	for (int i = 0; vector_of_sections.size(); i++) //���� ������
	{
		if (vector_of_sections.at(i) == s4)
		{
			counter_for_search = i;
			temp_ii = 1;
			break;
		}
	}
	if (temp_ii == 0) //���� ��� ����� ������, �� ������� ��������������
	{
		std::cout << "����� ������ ���";
	}

	if (temp_ii == 1) //���� ����� ����� ������, ���� ����������
	{
		for (int i = 0; i < vector_of_value.at(counter_for_search).size(); i++) // ���� �� ������� ����������
		{
			if (vector_of_value.at(counter_for_search).at(i).first == s5) // ���� ����� ����������, ���������, ����� ��� ��� ������ (����� � ������������ �������� ��������� �� ������)
			{
				for (int j = 0; j < vector_of_value.at(counter_for_search).at(i).second.size(); j++) //���� �� �������� ���������� (���� second � pair)
				{
					temp_int = static_cast<int>(vector_of_value.at(counter_for_search).at(i).second[j]);
					if ((temp_int >= 0 && temp_int <= 31) || (temp_int >= 33 && temp_int <= 45) || temp_int == 47 || (temp_int >= 58 && temp_int <= 127))
						flag_it_string = 1; //���� ���� ������, ������ �������� �������� �������
				}


				if (flag_it_string == 1) //���������� ������
					return vector_of_value.at(counter_for_search).at(i).second;


				if (flag_it_string == 0) //���������� �����
				{
					int q = 0;
					int j = 1;
					int l = 0;
					int k = 0;
					int g = 0;
					int temp_double = 0;

					for (q = 0; q < vector_of_value.at(counter_for_search).at(i).second.size(); q++) //���������, ������������ ��� ����� ��� �����
					{
						if (vector_of_value.at(counter_for_search).at(i).second[q] == '.')
						{
							temp_double = 1;
							break;
						}
					}

					if (temp_double == 1) //���� �������� � ������������ ������
					{
						q = 0;
						while (vector_of_value.at(counter_for_search).at(i).second[q] != '.') //���� ����������� ����� �����
						{
							k++; //����������� ����� �����
							q++;
						}
						q++;
						while (q != vector_of_value.at(counter_for_search).at(i).second.size()) //���� ����������� ������� �����
						{
							g++; //����������� ������� �����
							q++;
						}

						k--;
						for (int q = 0; q < vector_of_value.at(counter_for_search).at(i).second.size(); q++) // ���������� � ������������ �����
						{
							if (vector_of_value.at(counter_for_search).at(i).second[q] == '.') //����� ����� ��������� � ������������ ������� �����
							{
								l = 1;
								continue;
							}
							if (l == 0)
							{
								double_for_return += (static_cast<double>(vector_of_value.at(counter_for_search).at(i).second[q]) - static_cast<double>('0')) * (std::pow(10, k--));
								continue;
							}
							if (l == 1 && j <= g)
							{
								double_for_return += (static_cast<double>(vector_of_value.at(counter_for_search).at(i).second[q]) - static_cast <double>('0')) * (std::pow(10, -j));
								j++;
								continue;
							}
						}
						return double_for_return;
					}

					if (temp_double == 0) //���� �������� � ����� ������
					{
						q = 1;
						while (q != vector_of_value.at(counter_for_search).at(i).second.size()) //���� ����������� ������ �����
						{
							k++; //����������� ����� �����
							q++;
						}

						for (int q = 0; q < vector_of_value.at(counter_for_search).at(i).second.size(); q++)
						{
							int_for_return += (vector_of_value.at(counter_for_search).at(i).second[q] - '0') * (std::pow(10, k--));
							continue;
						}
						return int_for_return;
					}
				}
			}
			else if (i == vector_of_value.at(counter_for_search).size() - 1)
			{
				std::cout << "����� ���������� ���, �� � ���� ������ ���� ������ ����������:" << std::endl;
				return vector_of_value.at(counter_for_search);
			}
		}
	}
}