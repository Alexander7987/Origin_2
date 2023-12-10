// CPP дл€ реализации консруктора и метода дл€ класса исключени€ (здесь все в CPP файле т.к. нет шаблонов)
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <exception>
#include <MyParserError.h>


MyParserError::MyParserError(const int& count_string) : count_string(count_string)  //в конструкторе сразу преобразуем номер строки из числа в символы. Ёто нужно, т.к. номер строки может оказатьс€ большим числом (более чем однозначным), например 954673
{
    /*
    char w = 0;
    while (count_string != 0)
    {
        temp_string += count_string%10 + '0';
        count_string/10;
    }
    for (int i = 0; i < temp_string.size()/2; i++) //перевернем записанное значение
    {
        w = temp_string[i];
        temp_string[i] = temp_string[temp_string.size() - i - 1];
        temp_string[temp_string.size() - i - 1] = w;
    }
    */
    // »Ћ» ћќ∆Ќќ ¬ќ—ѕќЋ№«ќ¬ј“№—я std::to_string(...):
    error_message += std::to_string(count_string);
}



const char* MyParserError::what() const noexcept
{
    return error_message.c_str();
}
