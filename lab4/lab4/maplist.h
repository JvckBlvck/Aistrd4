#pragma once
#include <iostream>

using namespace std;

template<class T>
class maplist
{
public:
	class node
	{
	public:
		T data;
		node*next;
		node(T data);
		~node();
	};
	node*head;
	node*tail;
	size_t size;
	maplist();
	~maplist();
	void push_back(T data);
	void print();
	size_t get_size();
	T at(size_t index);
};

template<class T>
inline maplist<T>::node::node(T data)
{
	this->data = data;
	next = NULL;
}

template<class T>
inline maplist<T>::node::~node() {}

template <class T>
inline maplist<T>::maplist()
{
	head = NULL;
	tail = NULL;
	size = 0;
}

template<class T>
inline maplist<T>::~maplist()
{
	//node*cur = head;
	//while (cur != NULL)
	//{
		//cur = cur->next;
		//delete head;
		//head = cur;
//	}
}

template <class T>
void maplist<T>::push_back(T data)
{
	if (head == NULL)
	{
		head = new node(data);
		tail = head;
	}
	else
	{
		tail->next = new node(data);
		tail = tail->next;
	}
	size++;
}

template <class T>
void maplist<T>::print()
{
	node*cur = head;
	while (cur != NULL)
	{
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << "\n";
}

template<class T>
inline size_t maplist<T>::get_size()
{
	return size;
}

template<class T>
inline T maplist<T>::at(size_t index)
{
	size_t current = 0;
	node*cur = head;
	while (current < index)
	{
		cur = cur->next;
		current++;
	}
	return cur->data;
}
