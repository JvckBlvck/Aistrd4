// lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "map.h"
#include <string>
#include "functions.h"

using namespace std;

int main()
{
	cout << "Hello World!\n";
	map<string> cities;
	reading_cities(&cities);
	int**matrix = new int*[cities.size];
	for (size_t i = 0; i < cities.size; i++)
		matrix[i] = new int[cities.size];
	reading_costs(&cities, matrix);
	int check;
	string city;
	size_t from, to;
	for (size_t i = 0; i < cities.size; i++)
	{
		cities.find(&check, &city, i);
		cout << i << "." << city << "\n";
	}
	cout << "What city are you from?\n";
	cin >> from;
	cout << "What city do you fly to?\n";
	cin >> to;
	string way, newway;
	size_t length;
	searching(matrix, to, from, &way, cities.size, &length);
	waycreating(&cities, way, &newway);
	if (length < 1000000000)
	{
		cout << "Your way is " << newway << "\n";
		cout << "Your way`s length is " << length << "\n";
	}
	else
		cout << "There are not any way\n";
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
