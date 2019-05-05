#include "stdafx.h"
#include "CppUnitTest.h"
#include "../lab4/equal.h"
#include "../lab4/map.h"
#include "../lab4/functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(reading_file_cities)
		{
			map<string> mymap;
			reading_cities(&mymap);
			size_t*keys1 = new size_t[4];
			size_t i = 0;
			for (mapIterator<string> *tmp = mymap.createBfsIterator(); tmp->hasNext(); tmp->next())
				if (tmp->current_color() != 'n')
				{
					keys1[i] = tmp->current_key();
					i++;
				}
			size_t*keys2 = new size_t[4];
			keys2[0] = 1;
			keys2[1] = 0;
			keys2[2] = 2;
			keys2[3] = 3;
			string*cities1 = new string[4];
			i = 0;
			for (mapIterator<string> *tmp = mymap.createBfsIterator(); tmp->hasNext(); tmp->next())
				if (tmp->current_color() != 'n')
				{
					cities1[i] = tmp->current_data();
					i++;
				}
			string*cities2 = new string[4];
			cities2[0] = "moscow";
			cities2[1] = "peterburg";
			cities2[2] = "khabarovsk";
			cities2[3] = "vladivostok";
			Assert::IsTrue(equal_arrays(cities1, 4, cities2, 4) && equal_arrays(keys1, 4, keys2, 4));
		}
		TEST_METHOD(reading_file_costs)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix1 = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix1[i] = new int[mymap.size];
			reading_costs(&mymap, matrix1);
			int**matrix2 = new int*[4];
			for (size_t i = 0; i < 4; i++)
				matrix2[i] = new int[4];
			matrix2[0][0] = 0;
			matrix2[0][1] = 10;
			matrix2[0][2] = 14;
			matrix2[0][3] = 20;
			matrix2[1][0] = 20;
			matrix2[1][1] = 0;
			matrix2[1][2] = 40;
			matrix2[1][3] = 1000000000;
			matrix2[2][0] = 1000000000;
			matrix2[2][1] = 35;
			matrix2[2][2] = 0;
			matrix2[2][3] = 8;
			matrix2[3][0] = 1000000000;
			matrix2[3][1] = 1000000000;
			matrix2[3][2] = 13;
			matrix2[3][3] = 0;
			Assert::IsTrue(equal_matrixes(matrix1, 4, matrix2, 4));
		}
		TEST_METHOD(searching_way_0_0)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 0, 0, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"0");
			Assert::AreEqual(cost, (size_t)0);
			Assert::AreEqual(newway, (string)"->peterburg");
		}
		TEST_METHOD(searching_way_0_1)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 1, 0, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"0-1");
			Assert::AreEqual(cost, (size_t)10);
			Assert::AreEqual(newway, (string)"->peterburg->moscow");
		}
		TEST_METHOD(searching_way_0_2)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 2, 0, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"0-2");
			Assert::AreEqual(cost, (size_t)14);
			Assert::AreEqual(newway, (string)"->peterburg->khabarovsk");
		}
		TEST_METHOD(searching_way_0_3)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 3, 0, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"0-3");
			Assert::AreEqual(cost, (size_t)20);
			Assert::AreEqual(newway, (string)"->peterburg->vladivostok");
		}
		TEST_METHOD(searching_way_1_0)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 0, 1, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"1-0");
			Assert::AreEqual(cost, (size_t)20);
			Assert::AreEqual(newway, (string)"->moscow->peterburg");
		}
		TEST_METHOD(searching_way_1_1)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 1, 1, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"1");
			Assert::AreEqual(cost, (size_t)0);
			Assert::AreEqual(newway, (string)"->moscow");
		}
		TEST_METHOD(searching_way_1_2)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 2, 1, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"1-0-2");
			Assert::AreEqual(cost, (size_t)34);
			Assert::AreEqual(newway, (string)"->moscow->peterburg->khabarovsk");
		}
		TEST_METHOD(searching_way_1_3)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 3, 1, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"1-0-3");
			Assert::AreEqual(cost, (size_t)40);
			Assert::AreEqual(newway, (string)"->moscow->peterburg->vladivostok");
		}
		TEST_METHOD(searching_way_2_0)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 0, 2, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"2-1-0");
			Assert::AreEqual(cost, (size_t)55);
			Assert::AreEqual(newway, (string)"->khabarovsk->moscow->peterburg");
		}
		TEST_METHOD(searching_way_2_1)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 1, 2, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"2-1");
			Assert::AreEqual(cost, (size_t)35);
			Assert::AreEqual(newway, (string)"->khabarovsk->moscow");
		}
		TEST_METHOD(searching_way_2_2)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 2, 2, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"2");
			Assert::AreEqual(cost, (size_t)0);
			Assert::AreEqual(newway, (string)"->khabarovsk");
		}
		TEST_METHOD(searching_way_2_3)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 3, 2, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"2-3");
			Assert::AreEqual(cost, (size_t)8);
			Assert::AreEqual(newway, (string)"->khabarovsk->vladivostok");
		}
		TEST_METHOD(searching_way_3_0)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 0, 3, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"3-2-1-0");
			Assert::AreEqual(cost, (size_t)68);
			Assert::AreEqual(newway, (string)"->vladivostok->khabarovsk->moscow->peterburg");
		}
		TEST_METHOD(searching_way_3_1)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 1, 3, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"3-2-1");
			Assert::AreEqual(cost, (size_t)48);
			Assert::AreEqual(newway, (string)"->vladivostok->khabarovsk->moscow");
		}
		TEST_METHOD(searching_way_3_2)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 2, 3, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"3-2");
			Assert::AreEqual(cost, (size_t)13);
			Assert::AreEqual(newway, (string)"->vladivostok->khabarovsk");
		}
		TEST_METHOD(searching_way_3_3)
		{
			map<string> mymap;
			reading_cities(&mymap);
			int**matrix = new int*[mymap.size];
			for (size_t i = 0; i < mymap.size; i++)
				matrix[i] = new int[mymap.size];
			reading_costs(&mymap, matrix);
			string way, newway;
			size_t cost;
			searching(matrix, 3, 3, &way, mymap.size, &cost);
			waycreating(&mymap, way, &newway);
			Assert::AreEqual(way, (string)"3");
			Assert::AreEqual(cost, (size_t)0);
			Assert::AreEqual(newway, (string)"->vladivostok");
		}
	};
}