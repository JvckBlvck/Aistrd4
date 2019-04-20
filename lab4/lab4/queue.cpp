#include "pch.h"
#include "Queue.h"

using namespace std;

Queue::~Queue() {
	clear();
}

void Queue::pushBack(void* data) {
	if (isEmpty()) {
		head = new Node(data);
		tail = head;
	}
	else {
		tail->next = new Node(data);
		(tail->next)->prev = tail;
		tail = tail->next;
	}
	++size;
}

void Queue::pushFront(void* data) {
	if (isEmpty()) {
		head = new Node(data);
		tail = head;
	}
	else {
		head = new Node(data, head);
		(head->next)->prev = head;
	}
	++size;
}

void Queue::popBack() {
	if (!isEmpty()) {
		if (size == 1)
			head = tail = nullptr;
		else {
			Node *tmp = tail->prev;
			delete tail;
			tail = tmp;
			tail->next = nullptr;
		}
		--size;
	}
}

void Queue::popFront() {
	if (!isEmpty()) {
		if (size == 1)
			head = tail = nullptr;
		else {
			Node *tmp = head->next;
			delete head;
			head = tmp;
			head->prev = nullptr;
		}
		--size;
	}
}

size_t Queue::getSize() {
	return size;
}

void Queue::clear() {
	while (size != 0) popFront();
}

bool Queue::isEmpty() {
	return size == 0;
}

void* Queue::front() {
	return head->data;
}

void* Queue::back() {
	return tail->data;
}