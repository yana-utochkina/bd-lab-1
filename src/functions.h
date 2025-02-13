#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Models/IndexTable.h"
#include <string>

std::string dateToString(const char* date);
std::string timeToString(const char* time);
std::string phoneNumberToString(const char* phone);

std::string get_m(IndexTable* indexTable, int key);
std::string get_s(IndexTable* indexTable, int m_key, int s_id);

#endif //FUNCTIONS_H
