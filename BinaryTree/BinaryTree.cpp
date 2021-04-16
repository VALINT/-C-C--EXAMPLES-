// BinaryTree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
//#include "BinTree.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

namespace TREE {

	template<typename bt>
	class Node
	{
	public:
		Node *LChild;
		Node *RChild;
		bt data;

		Node(bt data, Node *LChild = nullptr, Node *RChild = nullptr)
		{
			this->data = data;
			this->LChild = LChild;
			this->RChild = RChild;
		}
	};

	template<typename bt>
	class BinTree
	{
	public:
		BinTree();
		void push_begin(bt data);
		void set_root(bt data, Node<bt> *LChild = nullptr, Node<bt> *RChild = nullptr);
		Node <bt>* get_root();
		Node <bt>* make_leaf(bt data, Node<bt> *LChild = nullptr, Node<bt> *RChild = nullptr)
		{
			return new Node<bt>(data, LChild, RChild);
		}
	private:
		int Size;
		Node<bt> *Root;
	};

	template<typename bt>
	BinTree<bt>::BinTree()
	{
		Size = 0;
		Root = nullptr;
	}

	template<typename bt>
	void BinTree<bt>::push_begin(bt data)
	{
		if (Root == nullptr)
		{
			Root = new Node<bt>(data);
			Size++;
		}
	}
	template<typename bt>
	void BinTree<bt>::set_root(bt data, Node<bt>* LChild, Node<bt>* RChild)
	{
		Root = new Node<bt>(data, LChild, RChild);
	}
	template<typename bt>
	Node<bt>* BinTree<bt>::get_root()
	{
		return Root;
	}
}



std::map<char, std::string> coddingTable;
std::string code;

void getCoddingTable(TREE::Node<std::pair<int, char>> *root);

int main()
{
	int totalSize = 0;
	std::string s;
	std::map<char, int> letters;
	TREE::Node<std::pair<int, char>> *p;
	std::vector<TREE::Node<std::pair<int, char>>*> leaves;
	TREE::BinTree<std::pair<int, char>> tree;

	std::getline(std::cin, s);

	for (auto i = 0; i < s.size(); i++)
	{
		letters[s[i]]++;
	}

	for (auto i = letters.begin(); i != letters.end(); i++)
	{
		p = tree.make_leaf(std::pair<int, char>(i->second, i->first));
		leaves.push_back(p);
	}

	while (leaves.size())
	{
		int tempNumber = 0;
		TREE::Node<std::pair<int, char>> *LSon = nullptr, *RSon = nullptr;
		
		sort(leaves.begin(), leaves.end(), [=](TREE::Node<std::pair<int, char>> *a, TREE::Node<std::pair<int, char>> *b)
		{
			return a->data.first > b->data.first;
		});

		if (leaves.size() == 1)
		{
			tree.set_root(std::pair<int, char>(leaves[0]->data.first, leaves[0]->data.second), nullptr, nullptr);
			break;
		}
		else if (leaves.size() > 2)
		{
			tempNumber += leaves[leaves.size() - 1]->data.first;
			tempNumber += leaves[leaves.size() - 2]->data.first;

			LSon = leaves[leaves.size() - 1];
			RSon = leaves[leaves.size() - 2];

			leaves.pop_back();
			leaves.pop_back();
			leaves.push_back(tree.make_leaf(std::pair<int, char>(tempNumber, NULL), LSon, RSon));
		}
		else if(leaves.size() == 2)
		{
			tempNumber += leaves[leaves.size() - 1]->data.first;
			tempNumber += leaves[leaves.size() - 2]->data.first;

			LSon = leaves[leaves.size() - 1];
			RSon = leaves[leaves.size() - 2];

			leaves.pop_back();
			leaves.pop_back();

			tree.set_root(std::pair<int, char>(tempNumber, NULL), LSon, RSon);
			break;
		}
		else
		{
			tree.set_root(std::pair<int, char>(tempNumber, NULL), LSon, RSon);
			break;
		}
	}
	getCoddingTable(tree.get_root());
	if (coddingTable.size() == 1)
	{
		auto t = coddingTable.begin();
		coddingTable[t->first] = "0";
	}

	for (auto i = 0; i < s.size(); i++)
		totalSize += coddingTable[s[i]].size();

	std::cout << coddingTable.size() << " " << totalSize << '\n';

	for (auto i = coddingTable.begin(); i != coddingTable.end(); i++)
	{
		std::cout << (i->first) << ": " << i->second << '\n';
	}

	for (auto i = 0; i < s.size(); i++)
	{
		std::cout << coddingTable[s[i]];
	}

	return 0;
}

void getCoddingTable(TREE::Node<std::pair<int, char>> *root)
{
	if (root->LChild != nullptr)
	{
		code.push_back('1');
		getCoddingTable(root->LChild);
	}

	if (root->RChild != nullptr)
	{
		code.push_back('0');
		getCoddingTable(root->RChild);
	}

	if (root->data.second) coddingTable[(root->data.second)] = code;
	
	if(code.size() > 0)
		code.pop_back();
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
