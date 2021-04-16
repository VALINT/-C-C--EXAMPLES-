// Haffman_dec.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#include <iostream>
#include <string>
#include <map>

int main() {
	int let, sym;
	std::map<std::string, char> decodingTable;
	std::string input;
	std::string coded;
	std::cin >> let >> sym;

	for (int i = 0; i <= let; i++)
	{
		char temp;
		std::string tempStr;
		std::getline(std::cin, input);
		temp = input[0];
		for (int it = 3; it < input.size(); it++)
		{ 
			    tempStr.push_back(input[it]);
		}
		decodingTable[tempStr] = temp;
	}

	std::getline(std::cin, coded);

	std::string tempDecoder;

	for (int it = 0; it < coded.size(); it++)
	{
		tempDecoder.push_back(coded[it]);
		if (decodingTable.count(tempDecoder) > 0)
		{
			std::cout << decodingTable[tempDecoder];
			tempDecoder.clear();
		}
	}
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
