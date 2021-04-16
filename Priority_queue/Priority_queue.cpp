// Priority_queue.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#include <iostream>
#include <string>
#include "prior_queue.h"

int main()
{
	PriorQueue<int> queue;
	int comands = 0;
	std::string comand;
	int priority = 0;

	std::cin >> comands;

	for (int i = 0; i < comands; i++)
	{
		std::cin >> comand;
		if (comand == "Insert")
		{
			std::cin >> priority;
			queue.insert(priority);
		}
		else if (comand == "ExtractMax")
			std::cout << queue.extractMax() << std::endl;
	}


	return 0;
}


