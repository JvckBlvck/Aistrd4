#pragma once
#include "pch.h"

template <class T>
bool equal_arrays(T*array1, size_t size1, T*array2, size_t size2)
{
	if (size1 != size2)
		return false;
	for (size_t i = 0; i < size1; i++)
		if (array1[i] != array2[i])
			return false;
	return true;
}

template <class T>
bool equal_matrixes(T**array1, size_t size1, T**array2, size_t size2)
{
	if (size1 != size2)
		return false;
	for (size_t i = 0; i < size1; i++)
		for (size_t j = 0; j < size1; j++)
			if (array1[i][j] != array2[i][j])
				return false;
	return true;
}