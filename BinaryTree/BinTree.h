#ifndef _BIN_TREE_
#define _BIN_TREE_

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
#endif // !_BIN_TREE_