#ifndef __PRIOR_QUEUE_H__
#define __PRIOR_QUEUE_H__

template <typename T>
class Node
{
public:
	T data;
	Node<T> *lSon;
	Node<T> *rSon;
	int lDescendans;
	int rDescendans;

	Node(T);
	~Node();
};

template <typename T>
class PriorQueue
{
public:
	Node<T> *root;

	PriorQueue();
	~PriorQueue();
	void insert(T data, Node<T> *node = nullptr);
	T extractMax();
	void sort_tree(Node<T> *node = nullptr);
};

template<typename T>
Node<T>::Node(T data)
{
	this->data = data;
	this->lSon = nullptr;
	this->rSon = nullptr;
	this->lDescendans = 0;
	this->rDescendans = 0;
}

template<typename T>
Node<T>::~Node()
{
	//delete Node;
}

template<typename T>
PriorQueue<T>::PriorQueue()
{
	root = nullptr;
}

template <typename T>
PriorQueue<T>::~PriorQueue()
{
	//delete PriorQueue;
}

template<typename T>
void PriorQueue<T>::insert(T data, Node<T> *node)
{
	if (root == nullptr && node == nullptr)
		root = new Node<T>(data);

	else if(node == nullptr)
	{
		if (root->lDescendans <= root->rDescendans)
		{
			if (root->lSon == nullptr)
			{
				if (data > root->data)
				{
					root->lSon = new Node<T>(root->data);
					root->data = data;
					root->lDescendans++;
				}
				else
				{
					root->lSon = new Node<T>(data);
					root->lDescendans++;
				}
			}
			else
			{
				if (data > root->data)
				{
					insert(root->data, root->lSon);
					root->data = data;
					root->lDescendans++;
				}
				else
				{
					insert(data, root->lSon);
					root->lDescendans++;
				}
			}
		}
		else
		{
			if (root->rSon == nullptr)
			{
				if (data > root->data)
				{
					root->rSon = new Node<T>(root->data);
					root->data = data;
					root->rDescendans++;
				}
				else
				{
					root->rSon = new Node<T>(data);
					root->rDescendans++;
				}
			}
			else
			{
				if (data > root->data)
				{
					insert(root->data, root->rSon);
					root->data = data;
					root->rDescendans++;
				}
				else
				{
					insert(data, root->rSon);
					root->rDescendans++;
				}
			}
		}
	}
	else
	{
		if (node->lDescendans <= node->rDescendans)
		{
			if (node->lSon == nullptr)
			{
				if (data > node->data)
				{
					node->lSon = new Node<T>(node->data);
					node->data = data;
					node->lDescendans++;
				}
				else
				{
					node->lSon = new Node<T>(data);
					node->lDescendans++;
				}
			}
			else
			{
				if (data > node->data)
				{
					insert(node->data, node->lSon);
					node->data = data;
					node->lDescendans++;
				}
				else
				{
					insert(data, node->lSon);
					node->lDescendans++;
				}
			}
		}
		else
		{
			if (node->rSon == nullptr)
			{
				if (data > node->data)
				{
					node->rSon = new Node<T>(node->data);
					node->data = data;
					node->rDescendans++;
				}
				else
				{
					node->rSon = new Node<T>(data);
					node->rDescendans++;
				}
			}
			else
			{
				if (data > node->data)
				{
					insert(root->data, node->rSon);
					node->data = data;
					node->rDescendans++;
				}
				else
				{
					insert(data, node->rSon);
					node->rDescendans++;
				}
			}
		}
	}
}

template<typename T>
inline T PriorQueue<T>::extractMax()
{
	T tempMax = root->data;
	root->data= -root->data;
	sort_tree();
	return T(tempMax);
}

template<typename T>
inline void PriorQueue<T>::sort_tree(Node<T> *node)
{
	if (node == nullptr)
		node = root;
	
	if (node->lSon != nullptr && node->rSon != nullptr)
	{
		if (node->lSon->data > node->rSon->data)
		{
			if (node->data < node->lSon->data)
			{
				T temp = node->data;
				node->data = node->lSon->data;
				node->lSon->data = temp;
				sort_tree(node->lSon);
			}
		}
		else
		{
			if (node->data < node->rSon->data)
			{
				T temp = node->data;
				node->data = node->rSon->data;
				node->rSon->data = temp;
				sort_tree(node->rSon);
			}
		}
	}
	else if (node->lSon != nullptr)
	{
		if (node->data < node->lSon->data)
		{
			T temp = node->data;
			node->data = node->lSon->data;
			node->lSon->data = temp;
			sort_tree(node->lSon);
		}
	}
	else if (node->rSon != nullptr)
	{
		if (node->data < node->rSon->data)
		{
			T temp = node->data;
			node->data = node->rSon->data;
			node->rSon->data = temp;
			sort_tree(node->rSon);
		}
	}
}


#endif

