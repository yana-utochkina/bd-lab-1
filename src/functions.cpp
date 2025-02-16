#include "functions.h"
#include "constants.h"
#include <fstream>
#include <sstream>

std::string dateToString(const char* d) {
  std::ostringstream oss;
  oss << d[0] << d[1] << '.' << d[2] << d[3] << '.' << d[4] << d[5] << d[6] << d[7];
  return oss.str();
}

std::string timeToString(const char* t) {
  char result[TIME_SIZE + 1] = { t[0], t[1], ':', t[2], t[3] };
  return result;
}

std::string phoneNumberToString(const char* p) {
  char result[PHONE_SIZE + 3] = { p[0], p[1], p[2], '-', p[3], p[4], p[5], '-', p[6], p[7], '-', p[8], p[9] };
  return result;
}

User* get_m(User* user, IndexTable* indexTable, int key) {
  std::fstream file;
  file.open(USERS_FL_PATH, std::ios::in | std::ios::binary);

  if (!file.is_open()) {
    throw std::runtime_error("Could not open file " + USERS_FL_PATH);
  }

  int row = indexTable->get_address(key);
  int address = INT_SIZE + USERS_ROW_SIZE * row;
  file.seekg(address + 1, std::ios::beg);

  user->Load(file);
  file.close();

  return user;
}
std::string get_s(IndexTable* indexTable, int m_key, int s_id) {
  return "";
}

void insert_m(IndexTable* indexTable, GarbageCollector* users_gc, User* user) {
  std::fstream file;
  bool empty = isEmptyFile(USERS_FL_PATH);
  file.open(USERS_FL_PATH, std::ios::out | std::ios::binary | std::ios::in);

  if (!file.is_open()) {
    throw std::runtime_error("Could not open file " + USERS_FL_PATH);
  }

  int address = 0;
  if (empty) {
    file.write(reinterpret_cast<char*>(&address), sizeof(int));
    file.seekg(0, std::ios::beg);
  }

  file.read(reinterpret_cast<char*>(&address), sizeof(int));
  if (users_gc->isEmpty()) {
    file.seekp(0, std::ios::beg);
    address++;
    file.write(reinterpret_cast<char*>(&address), sizeof(int));
    file.seekp(0, std::ios::end);
  }
  else {
    address = users_gc->pop_first();
    file.seekp(INT_SIZE + address * USERS_ROW_SIZE, std::ios::beg);
  }
  char o = '0';
  file.write(&o, sizeof(bool));
  user->Save(file);
  file.close();

  indexTable->add(user->id, address);
}

std::ostream& ut_m(std::ostream& os) {
  std::fstream file;
  file.open(USERS_FL_PATH, std::ios::in | std::ios::binary);
  int size;
  file.read(reinterpret_cast<char*>(&size), sizeof(int));
  os << "Index of next after end record: " << size << std::endl;
  os << "______________________________________" << std::endl;
  User* user = new User();
  char isExist;

  for (int i = 0; i < size; i++) {
    file.read(&isExist, sizeof(char));
    os << "Exist: " << isExist << std::endl;
    user->Load(file);
    os << "Index of first Visit in Visits.fl: " << user->firstVisitAdress << std::endl;
    os << "Size of Visits records: " << user->sizeOfVisits << std::endl;
    os << *user;
    os << "________________________________________" << std::endl;
  }

  delete user;
  return os;
}