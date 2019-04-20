#pragma once
#include <iostream>
#include <iomanip>
#include "mapiterator.h"
#include "queue.h"
#include "maplist.h"

using namespace std;

template <class T>
class map{
private:
	class node {
	public:
		char color;
		size_t key;
		T data;
		node*left;
		node*right;
		node*prev;
		node(char key, T data);
		~node();
	};
	node*root;
	void rotate_left(node*cur);
	void rotate_right(node*cur);
	void insert_case_cur_is_root(node*cur);
	void insert_case_prev_is_black(node*cur);
	void insert_case_prev_and_uncle_are_red(node*cur);
	void insert_case_prev_is_red_and_uncle_is_black_and_if_prev_is_left_then_cur_is_right_else_conversely(node*cur);
	void insert_case_prev_is_red_and_uncle_is_black_and_if_prev_is_left_then_cur_is_left_else_conversely(node*cur);
	void remove_case_cur_is_root(node*cur);
	void remove_case_brother_is_red(node*cur);
	void remove_case_prev_and_brother_and_brothers_children_are_black(node*cur);
	void remove_case_prev_is_red_and_brother_and_brothres_children_are_black(node*cur);
	void remove_case_brother_is_black_and_cur_is_left_and_brothers_right_is_black_and_brothers_left_is_black_or_cur_is_right_and_brothers_left_is_black_and_brothers_right_is_red(node*cur);
	void remove_case_cur_is_left_and_brother_is_black_and_brothers_right_is_red_or_cur_is_right_and_brother_is_black_and_brothers_left_is_red(node*cur);
	void replace_node(node*cur, node*child);
	bool contains(size_t key);
	void remove_one_child(node*cur);
public:
	size_t size;
	map();
	~map();
	class BfsIterator : public mapIterator<T> {
	private:
		Queue *currentNodes;
	public:
		BfsIterator(node *root) {
			currentNodes = new Queue();
			if (root) currentNodes->pushBack(static_cast<void*>(root));
		}
		void next();
		size_t current_key();
		T current_data();
		char current_color();
		bool hasNext();
	};
	mapIterator<T> *createBfsIterator();
	void insert(size_t ket, T data);
	void find(int*check, T*finded, size_t key);
	void finddata(T data, size_t*key, int*check);
	void remove(size_t key);
	void clear();
	maplist<size_t> get_keys();
	maplist<T> get_values();
};

template<class T>
mapIterator<T> * map<T>::createBfsIterator() {
	return new BfsIterator(root);
}

template<class T>
void  map<T>::BfsIterator::next() {
	node* current = static_cast<node*>(currentNodes->front());
	currentNodes->popFront();
	if (current->left) currentNodes->pushBack(static_cast<void*>(current->left));
	if (current->right) currentNodes->pushBack(static_cast<void*>(current->right));
}

template<class T>
size_t map<T>::BfsIterator::current_key() {
	return (static_cast<node*>(currentNodes->front()))->key;
}

template<class T>
T map<T>::BfsIterator::current_data() {
	return (static_cast<node*>(currentNodes->front()))->data;
}


template<class T>
char map<T>::BfsIterator::current_color() {
	return (static_cast<node*>(currentNodes->front()))->color;
}

template<class T>
bool  map<T>::BfsIterator::hasNext() {
	return !currentNodes->isEmpty();
}

template<class T>
inline map<T>::node::node(char key, T data)
{
	this->key = key;
	this->data = data;
	color = 'r';
	left = NULL;
	right = NULL;
	prev = NULL;
}

template<class T>
inline map<T>::node::~node()
{
}

template<class T>
inline void map<T>::rotate_left(node * cur)
{
	node *pivot = cur->right;
	pivot->prev = cur->prev;
	if (cur->prev != NULL) 
	{
		if (cur->prev->left == cur)
			cur->prev->left = pivot;
		else
			cur->prev->right = pivot;
	}
	cur->right = pivot->left;
	if (pivot->left != NULL)
		pivot->left->prev = cur;
	cur->prev = pivot;
	pivot->left = cur;
	if (root == cur)
		root = pivot;
}

template<class T>
inline void map<T>::rotate_right(node * cur)
{
	node *pivot = cur->left;
	pivot->prev = cur->prev;
	if (cur->prev != NULL) {
		if (cur->prev->left == cur)
			cur->prev->left = pivot;
		else
			cur->prev->right = pivot;
	}
	cur->left = pivot->right;
	if (pivot->right != NULL)
		pivot->right->prev = cur;
	cur->prev = pivot;
	pivot->right = cur;
	if (root == cur)
		root = pivot;
}

template<class T>
inline map<T>::map()
{
	size = 0;
	root = NULL;
}

template<class T>
inline map<T>::~map()
{
	clear();
}

template<class T>
inline void map<T>::insert_case_cur_is_root(node*cur)
{
	if (cur->prev == NULL)
		cur->color = 'b';
	else
		insert_case_prev_is_black(cur);
}

template<class T>
inline void map<T>::insert_case_prev_is_black(node*cur)
{
	if (cur->prev->color == 'r')
		insert_case_prev_and_uncle_are_red(cur);
}

template<class T>
inline void map<T>::insert_case_prev_and_uncle_are_red(node*cur)
{
	node*parent = cur->prev;
	node*granny = NULL;
	if (parent != NULL)
		granny = parent->prev;
	node*uncle = NULL;
	if (granny != NULL)
		if (granny->left == parent)
			uncle = granny->right;
		else
			uncle = granny->left;
	if ((uncle != NULL) && (uncle->color == 'r'))
	{
		cur->prev->color = 'b';
		uncle->color = 'b';
		granny->color = 'r';
		insert_case_cur_is_root(granny);
	}
	else
		insert_case_prev_is_red_and_uncle_is_black_and_if_prev_is_left_then_cur_is_right_else_conversely(cur);
}

template<class T>
inline void map<T>::insert_case_prev_is_red_and_uncle_is_black_and_if_prev_is_left_then_cur_is_right_else_conversely(node*cur)
{
	node*parent =cur->prev;
	node*granny = NULL;
	if (parent != NULL)
		granny = parent->prev;
	if ((cur == cur->prev->right) && (cur->prev == granny->left))
	{
		rotate_left(parent);
		cur = cur->left;
	}
	else if ((cur == cur->prev->left) && (cur->prev == granny->right))
	{
		rotate_right(parent);
		cur = cur->right;
	}
	insert_case_prev_is_red_and_uncle_is_black_and_if_prev_is_left_then_cur_is_left_else_conversely(cur);
}

template<class T>
inline void map<T>::insert_case_prev_is_red_and_uncle_is_black_and_if_prev_is_left_then_cur_is_left_else_conversely(node*cur)
{
	node*parent = cur->prev;
	node*granny = NULL;
	if (parent != NULL)
		granny = parent->prev;
	cur->prev->color = 'b';
	granny->color = 'r';
	if ((cur == cur->prev->left) && (cur->prev == granny->left))
		rotate_right(granny);
	else
		rotate_left(granny);
}

template<class T>
inline void map<T>::insert(size_t key, T data)
{
	node*cur;
	if (root == NULL)
	{
		root = new node(key, data);
		cur = root;
		cur->left = new node(key, data);
		cur->left->color = 'n';
		cur->left->prev = cur;
		cur->left->left == NULL;
		cur->left->right = NULL;
		cur->right = new node(key, data);
		cur->right->color = 'n';
		cur->right->prev = cur;
		cur->right->left = NULL;
		cur->right->right = NULL;
	}
	else
	{
		cur = root;
		node*prev = NULL;
		while (cur->color != 'n')
		{
			prev = cur;
			if (key < (cur->key))
				cur = cur->left;
			else
				cur = cur->right;
		}
		if (key < (prev->key))
		{
			prev->left->key = key;
			prev->left->data = data;
			prev->left->color = 'r';
			prev->left->left = new node(key, data);
			prev->left->left->color = 'n';
			prev->left->left->prev = prev->left;
			prev->left->left->left = NULL;
			prev->left->left->right = NULL;
			prev->left->right = new node(key, data);
			prev->left->right->color = 'n';
			prev->left->right->prev = prev->left;
			prev->left->right->left = NULL;
			prev->left->right->right = NULL;
			(prev->left)->prev = prev;
			cur = prev->left;
		}
		else
		{
			prev->right->key = key;
			prev->right->data = data;
			prev->right->color = 'r';
			prev->right = new node(key, data);
			prev->right->left = new node(key, data);
			prev->right->left->color = 'n';
			prev->right->left->prev = prev->right;
			prev->right->left->left = NULL;
			prev->right->left->right = NULL;
			prev->right->right = new node(key, data);
			prev->right->right->color = 'n';
			prev->right->right->prev = prev->right;
			prev->right->right->left = NULL;
			prev->right->right->right = NULL;
			(prev->right)->prev = prev;
			cur = prev->right;
		}
	}
	insert_case_cur_is_root(cur);
	size++;
}

template<class T>
inline void map<T>::find(int * check, T * finded, size_t key)
{
	node*cur = root;
	while ((cur != NULL) && (cur->key != key))
	{
		if (key < (cur->key))
			cur = cur->left;
		else
			cur = cur->right;
	}
	if (cur != NULL)
		*finded = cur->data;
	if ((cur != NULL) && (cur->color != 'n'))
		*check = 1;
	else
	{
		*check = -1;
		throw exception("key isn't contained");
	}
}

template<class T>
inline void map<T>::finddata(T data, size_t*key, int*check)
{
	*check = -1;
	for (mapIterator<T> *tmp = createBfsIterator(); tmp->hasNext(); tmp->next())
		if ((data == tmp->current_data()) && (tmp->current_color() != 'n'))
		{
			*key = tmp->current_key();
			*check = 1;
		}
			
}

template<class T>
inline bool map<T>::contains(size_t key)
{
	int check;
	T finded;
	try
	{
		find(&check, &finded, key);
	}
	catch (exception &ex)
	{
		return false;
	}
	return true;
}

template<class T>
inline void map<T>::remove_one_child(node * cur)
{
	node*child;
	if (cur->left->color != 'n')
		child = cur->left;
	else
		child = cur->right;
	replace_node(cur, child);
	if ((cur->color == 'b') || (cur->color == 'n'))
	{
		if (child->color == 'r')
			child->color = 'b';
		else
			remove_case_cur_is_root(child);
	}
}

template<class T>
inline void map<T>::remove_case_cur_is_root(node * cur)
{
	if (cur->prev != NULL)
		remove_case_brother_is_red(cur);
}

template<class T>
inline void map<T>::remove_case_brother_is_red(node * cur)
{
	node*parent = cur->prev;
	node*brother = NULL;
	if (parent != NULL)
		if (cur == parent->left)
			brother = parent->right;
		else
			brother = parent->left;
	if (brother!=NULL)
		if (brother->color == 'r')
		{
			parent->color = 'r';
			brother->color = 'b';
			if (cur == parent->left)
				rotate_left(parent);
			else
				rotate_right(parent);
		}
	remove_case_prev_and_brother_and_brothers_children_are_black(cur);
}

template<class T>
inline void map<T>::remove_case_prev_and_brother_and_brothers_children_are_black(node * cur)
{
	node*parent = cur->prev;
	node*brother = NULL;
	if (parent != NULL)
		if (cur == parent->left)
			brother = parent->right;
		else
			brother = parent->left;
	if ((parent != NULL) && (brother != NULL) && (brother->left != NULL) && (brother->right != NULL))
		if ((parent->color == 'b') && (brother->color == 'b') && ((brother->left->color == 'b') || (brother->left->color == 'n')) && ((brother->right->color == 'b') || (brother->right->color == 'n')))
		{
			brother->color = 'r';
			remove_case_cur_is_root(parent);
		}
		else
			remove_case_prev_is_red_and_brother_and_brothres_children_are_black(cur);
}

template<class T>
inline void map<T>::remove_case_prev_is_red_and_brother_and_brothres_children_are_black(node * cur)
{
	node*parent = cur->prev;
	node*brother = NULL;
	if (parent != NULL)
		if (cur == parent->left)
			brother = parent->right;
		else
			brother = parent->left;
	if ((parent != NULL) && (brother != NULL) && (brother->left != NULL) && (brother->right != NULL))
		if ((parent->color == 'r') && (brother->color == 'b') && ((brother->left->color == 'b') || (brother->left->color == 'n')) && ((brother->right->color == 'b') || (brother->right->color == 'n')))
		{
			brother->color = 'r';
			parent->color = 'b';
		}
		else
			remove_case_brother_is_black_and_cur_is_left_and_brothers_right_is_black_and_brothers_left_is_black_or_cur_is_right_and_brothers_left_is_black_and_brothers_right_is_red(cur);
}

template<class T>
inline void map<T>::remove_case_brother_is_black_and_cur_is_left_and_brothers_right_is_black_and_brothers_left_is_black_or_cur_is_right_and_brothers_left_is_black_and_brothers_right_is_red(node * cur)
{
	node*parent = cur->prev;
	node*brother = NULL;
	if (parent != NULL)
		if (cur == parent->left)
			brother = parent->right;
		else
			brother = parent->left;
	if (brother!=NULL)
		if (brother->color == 'b')
		{
			if ((cur == parent->left) && (brother->right->color == 'b') && (brother->left->color == 'r')) 
			{ 
				brother->color = 'r';
				brother->left->color = 'b';
				rotate_right(brother);
			}
			else if ((cur == parent->right) && (brother->left->color == 'b') && (brother->right->color == 'r'))
			{
				brother->color = 'r';
				brother->right->color = 'b';
				rotate_left(brother);
			}
		}
	remove_case_cur_is_left_and_brother_is_black_and_brothers_right_is_red_or_cur_is_right_and_brother_is_black_and_brothers_left_is_red(cur);
}

template<class T>
inline void map<T>::remove_case_cur_is_left_and_brother_is_black_and_brothers_right_is_red_or_cur_is_right_and_brother_is_black_and_brothers_left_is_red(node * cur)
{
	node*parent = cur->prev;
	node*brother = NULL;
	if (parent != NULL)
		if (cur == parent->left)
			brother = parent->right;
		else
			brother = parent->left;
	brother->color = parent->color;
	parent->color = 'b';
	if (cur == parent->left) 
	{
		brother->right->color = 'b';
		rotate_left(parent);
	}
	else
	{
		brother->left->color = 'b';
		rotate_right(parent);
	}
}

template<class T>
inline void map<T>::replace_node(node*cur, node*child)
{
	child->prev = cur->prev;
	if (cur->prev != NULL)
		if (cur->prev->left == cur)
			cur->prev->left = child;
		else
			cur->prev->right = child;
	child->prev = cur->prev;
	if (cur == root)
		root = child;
	delete cur;
	size--;
}

template<class T>
inline void map<T>::clear()
{
	while (size > 0)
		remove(root->key);
}

template<class T>
inline maplist<size_t> map<T>::get_keys()
{
	maplist<size_t> list_keys;
	for (mapIterator<T> *tmp = createBfsIterator(); tmp->hasNext(); tmp->next())
	{
		if (tmp->current_color() != 'n')
			list_keys.push_back(tmp->current_key());
	}
	return list_keys;
}

template<class T>
inline maplist<T> map<T>::get_values()
{
	maplist<T> list_data;
	for (mapIterator<T> *tmp = createBfsIterator(); tmp->hasNext(); tmp->next())
	{
		if (tmp->current_color() != 'n')
			list_data.push_back(tmp->current_data());
	}
	return list_data;
}


template<class T>
inline void map<T>::remove(size_t key)
{
	node*cur;
	node*child;
	node*copy_cur;
	node*copy_prev;
	if (contains(key) == false)
		throw exception("key isn't contained");
	while (contains(key) == true)
	{
		cur = root;
		while (cur->key != key)
			if (cur->key > key)
				cur = cur->left;
			else
				cur = cur->right;
		copy_prev = cur;
		copy_cur = cur->left;
		while (copy_cur->color != 'n')
		{
			copy_prev = copy_cur;
			copy_cur = copy_cur->right;
		}
		cur->key = copy_prev->key;
		cur->data = copy_prev->data;
		remove_one_child(copy_prev);
	}
}