#include <iostream>
#include "factorial.h"

int main()
{
	int a;
	std::cout << "Enter a number: ";
	std::cin >> a;
	std::cout << std::endl << "Answer: ";
	std::cout << factorial(a);
	return 0;
}