#pragma once

class Queue {
private:
	class Node {
	public:
		void *data;
		Node *next;
		Node *prev;
		Node(void * data = nullptr, Node *next = nullptr, Node *prev = nullptr) : data(data), next(next), prev(prev) {};
		~Node() {
			next = nullptr;
			delete next;
			prev = nullptr;
			delete prev;
		};
	};
	Node *head;
	Node *tail;
	size_t size;
public:
	Queue(Node *head = nullptr, Node *tail = nullptr, size_t size = 0) {
		this->head = head;
		this->tail = (tail) ? tail : head;
		this->size = size;
	};
	~Queue();
	void pushBack(void * data/*BinaryTree*/); // добавление в конец списка
	void pushFront(void * data/*BinaryTree*/); // добавление в начало списка
	void popBack(); // удаление последнего элемента
	void popFront(); // удаление первого элемента
	size_t getSize(); // получение размера списка
	void clear(); // удаление всех элементов списка
	bool isEmpty(); // проверка на пустоту списка
	void* front();
	void* back();
};