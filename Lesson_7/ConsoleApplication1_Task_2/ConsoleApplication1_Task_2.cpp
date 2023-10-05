#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <algorithm>

template<typename T>
void foo(T& my_case)
{
	std::for_each (my_case.begin(), my_case.end(), [](const auto& temp) {
		std::cout << temp << " ";
		}); //для ассоциативных упорядоченных контейнеров будет использоваться константный итератор. Для последовательных контейнеров можно обычный
	std::cout << std::endl;
}



int main()
{
	std::set<std::string> test_set = { "one","two","three","four" };
	std::list<std::string> test_list = { "one","two","three","four" };
	std::vector<std::string> test_vector = { "one","two","three","four" };
	foo(test_set);
	foo(test_list);
	foo(test_vector);
	return 0;
}
