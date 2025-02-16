#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Models/IndexTable.h"
#include <string>

#include "Models/GarbageCollector.h"
#include "Models/User.h"

std::string dateToString(const char* date);
std::string timeToString(const char* time);
std::string phoneNumberToString(const char* phone);

User* get_m(User* user, IndexTable* indexTable, int key);
std::string get_s(IndexTable* indexTable, int m_key, int s_id);

void insert_m(IndexTable* indexTable, GarbageCollector* users_gc, User* user);
std::ostream& ut_m(std::ostream& os);
#endif //FUNCTIONS_H
