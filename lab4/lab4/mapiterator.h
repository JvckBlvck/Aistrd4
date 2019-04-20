#pragma once

template<class T>
class mapIterator {
public:
	virtual void next() = 0;
	virtual bool hasNext() = 0;
	virtual size_t current_key() = 0;
	virtual T current_data() = 0;
	virtual char current_color() = 0;
};