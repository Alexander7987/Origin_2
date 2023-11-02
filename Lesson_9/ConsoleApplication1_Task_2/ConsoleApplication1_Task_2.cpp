#include <iostream>


class big_integer
{
private:
	std::string a;
	std::string string_for_return = "";
	std::string string_for_count = "";
	int max_size = 0;
public:
	big_integer(const std::string& a) :a(a) {}

	big_integer(big_integer&& other)noexcept
	{
		a = std::move(other.a);
		string_for_count = std::move(other.string_for_count);
		string_for_return = std::move(other.string_for_return);
	}

	void operator = (big_integer&& other)noexcept
	{
		a = std::move(other.a);
		string_for_count = std::move(other.string_for_count);
		string_for_return = std::move(other.string_for_return);
	}

	std::string& operator + (big_integer& other)
	{
		int i = 0;
		int c = 0; //может принимать либо 0, либо 1
		char temp; // для сортировки в конце
		int b;
		int size_a = std::size(a) - 1;
		int size_v = std::size(other.a) - 1;

		if (size_a >= size_v)
			max_size = size_a;
		else
			max_size = size_v;

		for (i = max_size; i >= 0; i--)
		{
			if (size_a > -1 && size_v > -1)
				b = (a[size_a--] - '0') + (other.a[size_v--] - '0'); //если работать с символьной арифметикой, то, если результат записывать в int, то получится целочисленное значение. 
			// В данном случае отнимаем от символьного числа (которое записано в string, а в строках единичный символ является char) символ '0'. 
			// В результате получаем это же число, но в типе, который занесен в переменную b.
			else if (size_a > -1)
				b = a[size_a--] - '0';
			else if (size_v > -1)
				b = other.a[size_v--] - '0';
			b += c;
			c = 0;
			if (b / 10 == 0)
			{
				string_for_return += b % 10 + '0'; //если прибавить к однозначному числу "'0'" то можно получить его десятичное значение из ASCII, следовательно, 
				//если полученное десятичное значение прибавлять в string, то оно по ASCII будет преобразовано в символ.
			}
			else
			{
				if (i == 0)
				{
					string_for_return += b % 10 + '0';
					string_for_return += b / 10 + '0';
				}
				else
				{
					string_for_return += b % 10 + '0';
					c = 1;
				}
			}
		}
		for (i = 0; i < std::size(string_for_return) / 2; i++)
		{
			temp = string_for_return[i];
			string_for_return[i] = string_for_return[std::size(string_for_return) - 1 - i];
			string_for_return[std::size(string_for_return) - 1 - i] = temp;
		}


		return string_for_return;
	}

	std::string& operator * (const int& other)
	{
		int i = 0, j = 0;
		int c = 0; //может принимать либо 0, либо 1
		char temp;
		string_for_count = a;
		int size_a = std::size(a) - 1; //переменная для корректной работы условного оператора внутри цикла
		//int v = 44444;
		int b = 0;
		for (i = other - 1; i > 0; i--)
		{
			for (j = std::size(string_for_count) - 1; j >= 0; j--)
			{
				if (size_a > -1)
					b = (static_cast<int>(string_for_count[j]) - static_cast<int>('0')) + (static_cast<int>(a[size_a--]) - static_cast<int>('0'));
				else
					b = (static_cast<int>(string_for_count[j]) - static_cast<int>('0'));
				b += c;
				c = 0;
				if (b / 10 == 0)
				{
					string_for_return += b % 10 + '0'; //если прибавить к однозначному числу "'0'" то можно получить его десятичное значение из ASCII, следовательно, 
					//если полученное десятичное значение прибавлять в string, то оно по ASCII будет преобразовано в символ.
				}
				else
				{
					if (j == 0)
					{
						string_for_return += b % 10 + '0';
						string_for_return += b / 10 + '0';
					}
					else
					{
						string_for_return += b % 10 + '0';
						c = 1;
					}
				}
			}
			for (int q = 0; q < std::size(string_for_return) / 2; q++)
			{
				temp = string_for_return[q];
				string_for_return[q] = string_for_return[std::size(string_for_return) - 1 - q];
				string_for_return[std::size(string_for_return) - 1 - q] = temp;
			}

			string_for_count = string_for_return;
			string_for_return = "";
			size_a = std::size(a) - 1;
		}
		return string_for_count;
	}
};


int main()
{
	auto number1 = big_integer("267432001205496");
	auto number2 = big_integer("5486002");
	auto result = number1 + number2;
	std::cout << result << std::endl; // 267432006691498
	result = number2 * 5;
	std::cout << result << std::endl;
	return 0;
}