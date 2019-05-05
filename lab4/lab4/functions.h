#pragma once
#include "map.h"
#include <string>

void reading_cities(map<string>*cities);
void reading_costs(map<string>*cities, int**matrix);
void searching(int**matrix, size_t to, size_t from, string*way, size_t matrixsize, size_t*cost);
void waycreating(map<string>*cities, string way, string*newway);
