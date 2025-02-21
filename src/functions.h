#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

#include "Models/IndexTable.h"
#include "Models/GarbageCollector.h"
#include "Models/User.h"
#include "Models/Visit.h"

std::string dateToString(const char* date);
std::string timeToString(const char* time);
std::string phoneNumberToString(const char* phone);

int get_m(User* user, IndexTable* indexTable, int key);
int get_s(Visit* visit, IndexTable* indexTable, int m_key, int s_id);

void update_m(User* user, IndexTable* indexTable, int key);
void update_s(Visit* visit, IndexTable* indexTable, int m_key, int s_id);

void insert_m(IndexTable* indexTable, GarbageCollector* users_gc, User* user);
void insert_s(IndexTable* indexTable, GarbageCollector* visits_gc, Visit* visit, int key);

void del_m(GarbageCollector* user_gc, GarbageCollector* visit_gc, IndexTable* indexTable, int key);
void del_s(GarbageCollector* visit_gc, IndexTable* indexTable, int m_key, int s_key);

int calc_m(IndexTable* indexTable);
int calc_s(IndexTable* indexTable, int key);

std::ostream& ut_m(std::ostream& os);
std::ostream& ut_s(std::ostream& os);

#endif //FUNCTIONS_H
