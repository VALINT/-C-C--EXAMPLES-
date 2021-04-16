// Haffman_codes_study.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
	string inStr;
	map<char, int> lettersList;
	vector<pair<char, int>> sortedLetterList;
	map<char, string> codingTable;
	int totalSize = 0;

	getline(cin, inStr);
	//inStr = "abcdabcbcaadbcdabcabccaabdba";

	for (auto i = 0; i < inStr.size(); i++)
	{
		lettersList[inStr[i]]++;
	}

	copy(lettersList.begin(), lettersList.end(), back_inserter<vector<pair<char, int> > >(sortedLetterList));
	sort(sortedLetterList.begin(), sortedLetterList.end(), [=](pair<char, int>& a, pair<char, int>& b ) 
	{
		return a.second > b.second;
	});

	for (int it = 0; it < sortedLetterList.size(); it++)
	{
		string temp;
		for (int i = 0; i < it; i++)
		{
			temp.push_back('1');
		}
		if(it < sortedLetterList.size()-1 || it==0)
			codingTable[sortedLetterList[it].first] = temp + "0";
		else
			codingTable[sortedLetterList[it].first] = temp;
	}

	for (auto i = 0; i < inStr.size(); i++)
	{
		totalSize += codingTable[inStr[i]].size();
	}

	cout << codingTable.size() << " " << totalSize << endl;

	for (auto i = 0; i < inStr.size(); i++)
	{
		cout << codingTable[inStr[i]];
	}
	cout << endl;

	for (auto it = sortedLetterList.begin(); it != sortedLetterList.end(); it++)
	{
		cout << it->first << " - " << it->second << endl;
	}

	cout << "Ct _ len - " << codingTable.size() << endl;

	for (auto im = codingTable.begin(); im != codingTable.end(); im++)
	{
		cout << im->first << " - " << im->second << endl;
	}
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
