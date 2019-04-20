#include "pch.h"
#include "functions.h"
#include <fstream>

using namespace std;

void reading_cities(map<string>*cities)
{
	fstream in;
	in.open("in.txt", ios::in);
	in.unsetf(ios::skipws);
	string newcity;
	char c;
	size_t countstring;
	size_t key = 0;
	maplist<string> citieslist;
	maplist<string>::node*cur;
	while (!in.eof())
	{
		countstring = 0;
		while ((!in.eof()) && (countstring < 2))
		{
			c = 'a';
			newcity.clear();
			while ((!in.eof()) && (c != ';'))
			{
				in >> c;
				if (c != ';')
					newcity += c;
			}
			if (!in.eof())
			{
				cur = citieslist.head;
				while ((cur != NULL) && (cur->data != newcity))
					cur = cur->next;
				if (cur == NULL)
				{
					cities->insert(key, newcity);
					key++;
					citieslist = cities->get_values();
				}
				countstring++;
			}
		}
		if (countstring == 2)
			while ((!in.eof()) && (c != '\n'))
				in >> c;
	}
	in.close();
}

void reading_costs(map<string>*cities, int ** matrix)
{
	fstream in;
	in.open("in.txt", ios::in);
	in.unsetf(ios::skipws);
	maplist<string> citieslist = cities->get_values();
	maplist<size_t> keyslist = cities->get_keys();
	string city1, city2;
	char c;
	size_t countstring;
	maplist<string>::node*cur1;
	maplist<size_t>::node*cur2;
	size_t key1, key2;
	for (size_t i = 0; i < cities->size; i++)
		for (size_t j = 0; j < cities->size; j++)
			matrix[i][j] = 1000000000;
	while (!in.eof())
	{
		countstring = 0;
		while ((!in.eof()) && (countstring < 2))
		{
			c = 'a';
			city1.clear();
			city2.clear();
			while ((!in.eof()) && (c != ';'))
			{
				in >> c;
				if (c != ';')
					if (countstring == 0)
						city1 += c;
					else
						city2 += c;
			}
			if (!in.eof())
			{
				if (countstring == 0)
				{
					key1 = 0;
					cur1 = citieslist.head;
					cur2 = keyslist.head;
					while (cur1->data != city1)
					{
						cur1 = cur1->next;
						cur2 = cur2->next;
					}
					key1 = cur2->data;
				}
				else
				{
					key2 = 0;
					cur1 = citieslist.head;
					cur2 = keyslist.head;
					while (cur1->data != city2)
					{
						cur1 = cur1->next;
						cur2 = cur2->next;
					}
					key2 = cur2->data;
				}
				countstring++;
			}
		}
		if (countstring == 2)
		{
			in >> c;
			in.unget();
			if (c == 'n')
			{
				matrix[key1][key2] = 1000000000;
				in >> c;
				in >> c;
				in >> c;
				in >> c;
			}
			else
			{
				in >> matrix[key1][key2];
				in >> c;
			}
			in >> c;
			in.unget();
			if (c == 'n')
			{
				matrix[key2][key1] = 1000000000;
				in >> c;
				in >> c;
				in >> c;
				in >> c;
			}
			else
			{
				in >> matrix[key2][key1];
				in >> c;
			}
			while ((!in.eof()) && (c != '\n'))
				in >> c;
		}
	}
	in.close();
	for (size_t i = 0; i < citieslist.size; i++)
		matrix[i][i] = 0;
}

void searching(int ** matrix, size_t to, size_t from, string*way, size_t matrixsize, size_t*length)
{
	way->clear();
	*way += to_string(from);
	int*wayscosts = new int[matrixsize];
	string*ways = new string[matrixsize];
	for (size_t i = 0; i < matrixsize; i++)
		wayscosts[i] = 1000000000;
	wayscosts[from] = 0;
	for (size_t k = 1; k < matrixsize; k++)
		for (size_t i = 0; i < matrixsize; i++)
			for (size_t j = 0; j < matrixsize; j++)
				if (wayscosts[i] + matrix[i][j] < wayscosts[j])
				{
					wayscosts[j] = wayscosts[i] + matrix[i][j];
					ways[j] = ways[i] + '-' + to_string(j);
				}
	*length = wayscosts[to];
	*way += ways[to];
}

void waycreating(map<string>*cities, string way, string * newway)
{
	size_t i = 0;
	newway->clear();
	string finding, finded;
	char c;
	size_t j;
	int check;
	while (i < way.length())
	{
		finding.clear();
		c = way[i];
		while ((c != '-') && (i < way.length()))
		{
			finding += c;
			i++;
			c = way[i];
		}
		j = 0;
		while (finding != to_string(j))
			j++;
		cities->find(&check, &finded, j);
		*newway += "->";
		*newway += finded;
		i++;
	}
}
