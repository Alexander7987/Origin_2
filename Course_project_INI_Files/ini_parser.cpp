// CPP для конструктора класса парсера
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
	int counter_for_sections = 0; // номер текущей ячейки вектора vector_of_sections

	// ЧТЕНИЕ ФАЙЛА ПО СТРОКАМ //
	f.close();
	f.open(s);
	while (getline(f, s1))
	{
		count_string++;
		for_value = 0;
		error_string = 0;

		// ЕСЛИ СТРОКА ПУСТАЯ, ПРОПУСКАЕМ
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



		// НУЖНО ПОНЯТЬ, ЯВЛЯЕТСЯ ЛИ ЭТА СТРОКА ИМЕНЕМ СЕКЦИИ ИЛИ ОБЪЯВЛЕНИЕМ ПЕРЕМЕННОЙ
		for (int i = 0; i < s1.size(); i++)
		{
			if (s1[i] == '=')
				for_value++;
		}
		if (for_value > 1) //нельзя, чтобы было несколько '='
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


		//ЕСЛИ В ИТОГЕ СТРОКА БЕЗ ЗНАКОВ "=" и "[", "]", ЭТО ОШИБКА
		if (error_string == 0 && for_value == 0) 
		{
			throw MyParserError(count_string);
		}



		//ПРОВЕРКА НА ОШИБКУ, ЕСЛИ СТРОКА ТАКАЯ: "wfe rfewrf ; jlogfn". Т.Е. НЕ ДОПУСКАЕТСЯ ДО СИМВОЛА ";" ОТСУТСТВИЕ ОБЪЯВЛЕНИЯ СЕКЦИИ ИЛИ ПЕРЕМЕННОЙ
		int temp_1 = 0;
		for (int i = 0; i < s1.size(); i++)
		{
			if (s1[i] == ' ') // если пробел, идем дальше
				continue;

			if (s1[i] != '[' && s1[i] != ']' && s1[i] != '=' && s1[i] != ';' && s1[i] != ' ') //здесь помечаем, что встретили символ, отличный от важных, которые объявляют, что это имя секции или объявление переменной
			{
				temp_1 = 1;
				continue;
			}		

			if (s1[i] == '[' || s1[i] == ']' || s1[i] == '=') //если это объявление переменной или имя секции, то выходим из данного анализа поиска этой ошибки
			{
				break;
			}

			if (s1[i] == ';' && temp_1 == 1) // елси были символы, то стоит флаг в значении 1, и, если встретили ';', это и есть ошибка
				throw MyParserError(count_string);

		}



		/// СЕКТОР ОБРАБОТКИ И ЗАПИСИ ВСЕХ СТРОК///
		for (int i = 0; i < s1.size(); i++)
		{
			if (s1[i] == ';')//комментарий не используем для чтения, следовательно, выходим из данной строки
				break;


			temp_int = static_cast<int>(s1[i]); //не допускается иных символов в файле кроме букв, цифр, и " ", "_", ".", "="
			if ((temp_int >= 0 && temp_int <= 31) || (temp_int >= 33 && temp_int <= 45) || temp_int == 47 || (temp_int >= 58 && temp_int <= 60) || (temp_int >= 62 && temp_int <= 64) || temp_int == 92 || temp_int == 94 || temp_int == 96 || (temp_int >= 123 && temp_int <= 127)) //некоторые символы недопустимы
			{
				throw MyParserError(count_string);
			}


			if (s1[i] == ' ' && i != s1.size() - 1 && point_one != 1 && for_value != 1) //если пробел, то игнорируем и дальше ищем "[" или символ. 
				//Если внутри секции, то пробел нельзя, поэтому перемещаемся в if (s1[i] == ' ' && point_one == 1). Если внутри задания переменных (если for_value == 1),
				//то уходим в if (s[i] == ' ' && for_value = 1), где записываем этот пробел в строку
				continue;


			if (s1[i] == ' ' && for_value == 1) //записываем даже пробелы, если находимся в строке, где объявляется переменная, чтобы потом найти ошибку, если несколько значений/переменных
			{
				s2 += s1[i];
				continue;
			}


			if (s1[i] == ' ' && point_one == 1) // если в названии секции есть пробел, это ошибка
			{
				throw MyParserError(count_string);
			}


			if (s1[i] == ' ' && i == s1.size() - 1) //если пробел в конце, то идем дальше
				continue;


			if (s1[i] != ';' && s1[i] != '[' && point_one != 1 && point_one != 2) //записываем символы в строку в любом случае, но если далее будет "[", то выдаём ошибку
			{//условие point_one != 2 для того, чтобы перейти в if (point_one == 2 && (s1[i] != ' ' || s1[i] != '/n'))
				s2 += s1[i]; // Условие point_one != 1 для того, чтобы не дублировать в s2 символы, которые встретятся внутри скобок [] уже после прохождения "[" и до "["
				continue;
			}


			if (s1[i] == '[' && point_one == 0) //после этого условия начинаем запись (0 - ищем "[", 1 - идет запись)
			{
				if (s2 != "") //если были символы до открытия скобки "[", то это ошибка
				{
					throw MyParserError(count_string);
				}
				point_one = 1;
				continue; //после этого continue пошла запись
			}


			if (s1[i] == '[' && point_one == 1) //нельзя, чтобы в названии секции два раза открывалась "["
			{
				throw MyParserError(count_string);
			}


			if (point_one == 1 && s1[i] != ']' && i != s1.size() - 1) //пошла запись названия секции. В случае "]" мы не должны её записывать в название секции
				//Если это последний символ, не равный "]", то перемещаемся в if (i == s1.size() - 1 && point_one == 1)
			{
				if (s1[i] == '=') //не допускается знак "=" в названии секции
				{
					throw MyParserError(count_string);
				}
				s2 += s1[i];
				continue;
			}


			if (s1[i] == ']' && point_one == 1) //2 - запись закрыта и недопускается далее в этой строке символов
			{
				if (s2 == "") //выдаем ошибку, если секция не содержит названия, например в файле написано: []
				{
					throw MyParserError(count_string);
				}
				point_one = 2;
				continue; //если после этого continue цикл for продолжится и там окажется символ (кроме ' '), то выведем ошибку в if (point_one == 2 && (s1[i] != ' ' || s1[i] != '/n'))
			}


			if (point_one == 2 && (s1[i] != ' ' && s1[i] != '/n')) //2 - запись закрыта и недопускается далее в этой строке символов кроме пробелов и табуляции
			{
				throw MyParserError(count_string);
			}


			if (i == s1.size() - 1 && point_one == 1) //если нет закрывающей скобки, то это ошибка
			{
				throw MyParserError(count_string);
			}


			if (point_one == 0 && s1[i] == ']') //если нет открывающей скобки, то это ошибка
			{
				throw MyParserError(count_string);
			}
		} //ВЫХОД ИЗ ЦИКЛА ЧТЕНИЯ ТЕКУЩЕЙ СТРОКИ



		/// ПРОДОЛЖЕНИЕ СЕКТОРА В ЧАСТИ ОБРАБОТКИ ИМЕН СЕКЦИЙ. ЗДЕСЬ ЖЕ СОЗДАЕМ ВЕКТОР ИМЕН СЕКЦИЙ И ДОБАВЛЯЕМ НОВЫЕ ВЕКТОРА ПАР В ВЕКТОР ПЕРМЕННЫХ ///
		if (point_one == 2)
		{
			bool temp = 0;
			point_one = 0;
			for (int i = 0; i < vector_of_sections.size(); i++) //проверяем, есть ли уже такая секция в векторе имен секций
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
				vector_of_sections.push_back(s2); //добавили имя секции в вектор имен секций
				vector_of_value.push_back(std::vector <std::pair <std::string, std::string>> {}); // добавили вектор, в котором хранятся ПАРЫ имя_переменной + значение переменной добавленной выше секции
				// ВАЖНО, ЧТОБЫ ОПЕРАЦИИ НА 219 И 220 СТРОКАХ БЫЛИ ВМЕСТЕ, ЧТОБЫ БЫЛО СООТВЕТСТВИЕ НОМЕРОВ ЯЧЕЕК ВЕКТОРА ИМЕН СЕКЦИЙ С НОМЕРАМИ ЯЧЕЕК ВЕКТОРА ПЕРЕМЕННЫХ
				counter_for_sections = vector_of_sections.size() - 1;
			}
			s2 = "";
			continue;
		}


		/// ПРОДОЛЖЕНИЕ СЕКТОРА В ЧАСТИ ОБРАБОТКИ СТРОК ПЕРЕМЕННЫХ. ЭТО СТРОКИ, ГДЕ ЕСТЬ "=" ПОСЛЕ ВЫХОДА ИЗ ЦИКЛА ОСНОВНОГО ОБРАБОТЧИКА, ОНИ ПОМЕЧЕНЫ for_value = 1; ///
		// Отдельно продолжаем обрабатывать такую строку, чтобы небыло пересечений по условиям в первом цикле for, т.к. там ловим секции
		if (for_value == 1) //если сюда попадаем, то получаем уже обработанную строку s2,т.к. ранее не допускалось иных символов в файле кроме букв, цифр, и "_", ".", "=", " "
		{
			int flag_it_string = 0;
			int counter = 0;
			int tempp = -1;
			int temp = 0; //0 - запись открыта, 1 - запись закрыта, 2 - запись открыта для записи значения переменной
			s3 = ""; // строка для записи имён переменных и их значений
			for (int i = 0; i < s2.size(); i++)
			{
				if (s2[i] == ' ' && s3 == "" && temp != 2) //в начале пропускаем все пробелы если это не запись значения
					continue;
				if (s2[i] != ' ' && s2[i] != '=' && temp == 0) // открываем запись и записываем имя переменной
				{
					s3 += s2[i];
					continue;
				}
				if (s2[i] == ' ' && temp == 0) //закрываем запись в случае встречи с пробелом после того, как запись была открыта
				{
					temp = 1;
					continue;
				}
				if (s2[i] != ' ' && temp == 1 && s2[i] != '=') //недопускается запись любого символа кроме ' ' и "=" после закрытия
				{
					throw MyParserError(count_string);
				}
				if (s2[i] == ' ' && temp == 1) //пропускаем все пробелы после закрытия
					continue;


				if (s2[i] == '=' && i == s2.size() - 1) //если "=" последний в строке, но значения для переменной нет
				{
					if (s3 == "") //имя переменной не должно быть пустым
					{
						throw MyParserError(count_string);
					}
					else
					{
						for (int k = 0; k < vector_of_value.at(counter_for_sections).size(); k++) // проверяем, есть ли уже такая переменная в векторе переменных
						{
							if (vector_of_value.at(counter_for_sections).at(k).first == s3) // и, если есть, то удаляем старое значение на пустое
							{
								vector_of_value.at(counter_for_sections).at(k).second = "";
								tempp = 1;
								break;
							}
						}
						if (tempp == 1) //  и вышли из цикла, т.к. тут больше нечего искать (значение для переменной нет)
						{
							s3 = "";
							break;
						}
						else
						{
							vector_of_value.at(counter_for_sections).push_back(std::make_pair(s3, "")); // а если нет, то добавили имя новой переменной
							s3 = "";
							break; // и вышли из цикла, т.к. тут больше нечего искать (значение для переменной нет)
						}
					}
				}


				if (s2[i] == '=' && i != s2.size() - 1) //если "=" непоследний в строке, открываем для записи значения переменной. Для этого устанавливаем флаг "2", обнуляем для записи значения переменной
				{
					if (s3 == "") //имя переменной не должно быть пустым
					{
						throw MyParserError(count_string);
					}
					else
					{
						for (int k = 0; k < vector_of_value.at(counter_for_sections).size(); k++) // проверяем, есть ли уже такая переменная в векторе переменных
						{
							if (vector_of_value.at(counter_for_sections).at(k).first == s3) // и, если есть, то не записываем её заного, а лишь далее поменяем значение этой переменной
							{
								tempp = k;
								break;
							}
						}
						if (tempp != -1) // и, если есть, то не записываем её заного, а лишь далее поменяем значение этой переменной
						{
							s3 = "";
							temp = 2;
							continue;
						}
						else
						{
							vector_of_value.at(counter_for_sections).push_back(std::make_pair(s3, "")); // а если нет, то добавили пока что только имя новой переменной
							s3 = "";
							temp = 2;
							continue;
						}
					}
				}


				if (temp == 2 && i != s2.size() - 1) // Записываем значение. Если значение является строкой, то здесь разрешены ' '. Если это последний символ, то идем в if (temp == 2 && i == s2.size() - 1)
				{
					if (s2[i] == ' ' && s3 == "") //если пробел и строка значения s3 пустая, т.к. начальные пробелы нет смысла записывать, пропускаем запись
						continue;
					else
					{
						temp_int = static_cast<int>(s2[i]);
						if ((temp_int >= 0 && temp_int <= 31) || (temp_int >= 33 && temp_int <= 45) || temp_int == 47 || (temp_int >= 58 && temp_int <= 127))
							flag_it_string = 1; //если сюда попали, значит значение является строкой
						s3 += s2[i];
						continue;
					}
				}


				if (temp == 2 && i == s2.size() - 1)// В самом конце обработаем записанное значение переменной. 
				{
					if (s2[i] == ' ' && s3 == "") //если последний символ пробел, а строка значения s3 пустая, т.к. в начале стояли пробелы, то нет смысла записывать
					{
						if (tempp != -1) // заходим сюда, если переменная уже была
						{
							vector_of_value.at(counter_for_sections).at(tempp).second = s3; //запишем(обновим в данном условии) значение, которое является строкой
							break;
						}
						else // а если нет, то запишем значение новосозданной переменной
						{
							vector_of_value.at(counter_for_sections).at(vector_of_value.at(counter_for_sections).size() - 1).second = s3; //запишем значение, которое является строкой
							break;
						}
						break;
					}
					else if (s2[i] != ' ') //если все же s3 не пустая, то последний пробел не учитываем и, если есть последний символ (или число), то записываем
						s3 += s2[i];


					int size_s3 = s3.size();
					for (int m = size_s3 - 1; m >= 0; m--) // удалим в конце пробелы из записанной строки s3 
					{
						if (s3[m] == ' ')
							s3.erase(m, 1);
						else
							break; //как только встретили первый символ, уходим
					}



					if (flag_it_string == 1) //ТОГДА ЭТО СТРОКА
					{
						if (tempp != -1) // заходим сюда, если переменная уже была
						{
							vector_of_value.at(counter_for_sections).at(tempp).second = s3; //запишем(обновим в данном условии) значение, которое является строкой
							break;
						}
						else // а если нет, то запишем значение новосозданной переменной
						{
							vector_of_value.at(counter_for_sections).at(vector_of_value.at(counter_for_sections).size() - 1).second = s3; //запишем значение, которое является строкой
							break;
						}
					}

					///// ЕСЛИ ЭТО ЧИСЛО (т.е. flag_it_string = 0), ЗАПУСКАЕМ ЦИКЛ НИЖЕ ///////
					int flag_for_point = 0;
					for (int j = 0; j < s3.size(); j++) // идем по записанному в s3 значению
					{
						temp_int = static_cast<int>(s3[j]);
						if (temp_int >= 48 && temp_int <= 57 && counter != 3) //далее не допускается пробелов и более ОДНОГО символа "."
						{
							if (counter == 2)
							{
								flag_for_point = 0; // обнуляем флажок, если после точки есть какое-то число (т.к. мы внутри, то значит, что оно есть)
								continue;
							}
							counter = 1;
							continue;
						}
						if (counter == 1 && temp_int == 46) //читаем далее числа после точки. 46 - код символа точки
						{
							if (j == s3.size() - 1) //нельзя, чтобы точка была последним символом
							{
								throw MyParserError(count_string);
							}
							flag_for_point = 1; // флажок, что после точки обязано быть какое-то число
							counter = 2;
							continue;
						}
						if (s3[j] == ' ' && (counter == 1 || counter == 2)) // закрываем чтение для типа числа после первого пробела в числе (если это число, то counter == 1 или 2)
						{
							if (flag_for_point == 1 && j == s3.size() - 1) //нельзя, чтобы точка была последним символом
							{
								throw MyParserError(count_string);
							}
							counter = 3;
							continue;
						}
						if (counter == 2 && temp_int == 46) //не допускается более ОДНОГО символа "."
						{
							throw MyParserError(count_string);
						}
						if (counter == 3 && (temp_int >= 48 && temp_int <= 57)) // если есть число после закрытия, это ошибка
						{
							throw MyParserError(count_string);
						}
					}

					if (tempp != -1) // заходим сюда, если переменная уже была
					{
						vector_of_value.at(counter_for_sections).at(tempp).second = s3; //запишем(обновим в данном условии) значение, которое является строкой
						break;
					}
					else // а если нет, то запишем значение новосозданной переменной
					{
						vector_of_value.at(counter_for_sections).at(vector_of_value.at(counter_for_sections).size() - 1).second = s3; //запишем значение, которое является строкой
						break;
					}
					s3 = ""; //обнуляем для дальнейшей записи
				}
			}
		}
		for_value = 0;
		s2 = "";
	} //ВЫХОД ИЗ ЦИКЛА ЧТЕНИЯ ВСЕГО ФАЙЛА
	//if (e != -1) //фиксация нарушения и вылет из цикла с исключением
	//{
		//throw e;
	//}
	f.close();
}
