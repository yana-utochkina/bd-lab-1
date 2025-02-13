#include "functions.h"
#include "constants.h"
#include <fstream>

std::string dateToString(const char* d) {
  char result[DATE_SIZE + 2] = { d[0], d[1], '.', d[2], d[3], '.', d[4], d[5], d[6], d[7]};
  return result;
}

std::string timeToString(const char* t) {
  char result[TIME_SIZE + 1] = { t[0], t[1], ':', t[2], t[3] };
  return result;
}

std::string phoneNumberToString(const char* p) {
  char result[PHONE_SIZE + 3] = { p[0], p[1], p[2], '-', p[3], p[4], p[5], '-', p[6], p[7], '-', p[8], p[9] };
  return result;
}

std::string get_m(IndexTable* indexTable, int key) {
  indexTable->IndexTable::get_address(key);
  std::fstream file;
  file.open(USERS_FL_PATH, std::ios::in | std::ios::binary);
  // read file on specific address
  return "";
}
std::string get_s(IndexTable* indexTable, int m_key, int s_id);