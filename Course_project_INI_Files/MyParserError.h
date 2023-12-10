// хедер my_exception.h для класса исключения
#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <exception>


class MyParserError : public std::exception //свой класс для исключений
{
private:
    int count_string = 0;
    std::string error_message = "Error in line  ";
    std::string temp_string = "";

public:
    MyParserError(const int& count_string);

    const char* what() const noexcept override;
};