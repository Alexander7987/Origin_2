// CPP ��� ������������ ������ �������
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ini_parser.h>
#include <MyParserError.h>




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
			throw MyParserError(count_string);
		}


		for (int i = 0; i < s1.size(); i++)
		{
			if (s1[i] == '[' || s1[i] == ']' || s1[i] == ';')
			{
				error_string = 1;
				break;
			}
		}


		//���� � ����� ������ ��� ������ "=" � "[", "]", ��� ������
		if (error_string == 0 && for_value == 0) 
		{
			throw MyParserError(count_string);
		}



		//�������� �� ������, ���� ������ �����: "wfe rfewrf ; jlogfn". �.�. �� ����������� �� ������� ";" ���������� ���������� ������ ��� ����������
		int temp_1 = 0;
		for (int i = 0; i < s1.size(); i++)
		{
			if (s1[i] == ' ') // ���� ������, ���� ������
				continue;

			if (s1[i] != '[' && s1[i] != ']' && s1[i] != '=' && s1[i] != ';' && s1[i] != ' ') //����� ��������, ��� ��������� ������, �������� �� ������, ������� ���������, ��� ��� ��� ������ ��� ���������� ����������
			{
				temp_1 = 1;
				continue;
			}		

			if (s1[i] == '[' || s1[i] == ']' || s1[i] == '=') //���� ��� ���������� ���������� ��� ��� ������, �� ������� �� ������� ������� ������ ���� ������
			{
				break;
			}

			if (s1[i] == ';' && temp_1 == 1) // ���� ���� �������, �� ����� ���� � �������� 1, �, ���� ��������� ';', ��� � ���� ������
				throw MyParserError(count_string);

		}



		/// ������ ��������� � ������ ���� �����///
		for (int i = 0; i < s1.size(); i++)
		{
			if (s1[i] == ';')//����������� �� ���������� ��� ������, �������������, ������� �� ������ ������
				break;


			temp_int = static_cast<int>(s1[i]); //�� ����������� ���� �������� � ����� ����� ����, ����, � " ", "_", ".", "="
			if ((temp_int >= 0 && temp_int <= 31) || (temp_int >= 33 && temp_int <= 45) || temp_int == 47 || (temp_int >= 58 && temp_int <= 60) || (temp_int >= 62 && temp_int <= 64) || temp_int == 92 || temp_int == 94 || temp_int == 96 || (temp_int >= 123 && temp_int <= 127)) //��������� ������� �����������
			{
				throw MyParserError(count_string);
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
				throw MyParserError(count_string);
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
					throw MyParserError(count_string);
				}
				point_one = 1;
				continue; //����� ����� continue ����� ������
			}


			if (s1[i] == '[' && point_one == 1) //������, ����� � �������� ������ ��� ���� ����������� "["
			{
				throw MyParserError(count_string);
			}


			if (point_one == 1 && s1[i] != ']' && i != s1.size() - 1) //����� ������ �������� ������. � ������ "]" �� �� ������ � ���������� � �������� ������
				//���� ��� ��������� ������, �� ������ "]", �� ������������ � if (i == s1.size() - 1 && point_one == 1)
			{
				if (s1[i] == '=') //�� ����������� ���� "=" � �������� ������
				{
					throw MyParserError(count_string);
				}
				s2 += s1[i];
				continue;
			}


			if (s1[i] == ']' && point_one == 1) //2 - ������ ������� � ������������� ����� � ���� ������ ��������
			{
				if (s2 == "") //������ ������, ���� ������ �� �������� ��������, �������� � ����� ��������: []
				{
					throw MyParserError(count_string);
				}
				point_one = 2;
				continue; //���� ����� ����� continue ���� for ����������� � ��� �������� ������ (����� ' '), �� ������� ������ � if (point_one == 2 && (s1[i] != ' ' || s1[i] != '/n'))
			}


			if (point_one == 2 && (s1[i] != ' ' && s1[i] != '/n')) //2 - ������ ������� � ������������� ����� � ���� ������ �������� ����� �������� � ���������
			{
				throw MyParserError(count_string);
			}


			if (i == s1.size() - 1 && point_one == 1) //���� ��� ����������� ������, �� ��� ������
			{
				throw MyParserError(count_string);
			}


			if (point_one == 0 && s1[i] == ']') //���� ��� ����������� ������, �� ��� ������
			{
				throw MyParserError(count_string);
			}
		} //����� �� ����� ������ ������� ������



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
					throw MyParserError(count_string);
				}
				if (s2[i] == ' ' && temp == 1) //���������� ��� ������� ����� ��������
					continue;


				if (s2[i] == '=' && i == s2.size() - 1) //���� "=" ��������� � ������, �� �������� ��� ���������� ���
				{
					if (s3 == "") //��� ���������� �� ������ ���� ������
					{
						throw MyParserError(count_string);
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
						throw MyParserError(count_string);
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
								throw MyParserError(count_string);
							}
							flag_for_point = 1; // ������, ��� ����� ����� ������� ���� �����-�� �����
							counter = 2;
							continue;
						}
						if (s3[j] == ' ' && (counter == 1 || counter == 2)) // ��������� ������ ��� ���� ����� ����� ������� ������� � ����� (���� ��� �����, �� counter == 1 ��� 2)
						{
							if (flag_for_point == 1 && j == s3.size() - 1) //������, ����� ����� ���� ��������� ��������
							{
								throw MyParserError(count_string);
							}
							counter = 3;
							continue;
						}
						if (counter == 2 && temp_int == 46) //�� ����������� ����� ������ ������� "."
						{
							throw MyParserError(count_string);
						}
						if (counter == 3 && (temp_int >= 48 && temp_int <= 57)) // ���� ���� ����� ����� ��������, ��� ������
						{
							throw MyParserError(count_string);
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
	//if (e != -1) //�������� ��������� � ����� �� ����� � �����������
	//{
		//throw e;
	//}
	f.close();
}
