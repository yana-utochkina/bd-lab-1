#include "User.h"
#include "../constants.h"
#include "../functions.h"

User::User(const int firstVisitAddress, const int sizeOfVisits, const int id, const char* phone, const char* fullName, const char* birthDay) {
  this->firstVisitAdress = firstVisitAddress;
  this->sizeOfVisits = sizeOfVisits;
  this->id = id;
  for (int i = 0; i < PHONE_SIZE; i++) {
    this->phone[i] = phone[i];
  }
  for (int i = 0; i < FULLNAME_SIZE; i++) {
    this->fullName[i] = fullName[i];
  }
  for (int i = 0; i < DATE_SIZE; i++) {
    this->birthDay[i] = birthDay[i];
  }
}

User::User(const int id,const char* phone,const char* fullName,const char* birthDay) {
  this->id = id;
  for (int i = 0; i < PHONE_SIZE; i++) {
    this->phone[i] = phone[i];
  }
  for (int i = 0; i < FULLNAME_SIZE; i++) {
    this->fullName[i] = fullName[i];
  }
  for (int i = 0; i < DATE_SIZE; i++) {
    this->birthDay[i] = birthDay[i];
  }
}

std::ostream& operator<<(std::ostream& os, const User& user) {
  os << "id: " << user.id << '\n';
  os << "phone: " << phoneNumberToString(user.phone) << '\n';
  os << "fullName: " << user.fullName << '\n';
  os << "birthDay: " << dateToString(user.birthDay) << '\n';
  return os;
}

void User::Save(std::fstream& file) {
  file.write(reinterpret_cast<char*>(&this->firstVisitAdress), sizeof(this->firstVisitAdress));
  file.write(reinterpret_cast<char*>(&this->sizeOfVisits), sizeof(this->sizeOfVisits));
  file.write(reinterpret_cast<char*>(&this->id), sizeof(this->id));
  file.write(reinterpret_cast<char*>(&this->phone), PHONE_SIZE);
  file.write(reinterpret_cast<char*>(&this->fullName), FULLNAME_SIZE);
  file.write(reinterpret_cast<char*>(&this->birthDay), DATE_SIZE);
}

void User::Load(std::fstream& file) {
  file.read(reinterpret_cast<char*>(&this->firstVisitAdress), sizeof(this->firstVisitAdress));
  file.read(reinterpret_cast<char*>(&this->sizeOfVisits), sizeof(this->sizeOfVisits));
  file.read(reinterpret_cast<char*>(&this->id), sizeof(this->id));
  file.read(reinterpret_cast<char*>(&this->phone), PHONE_SIZE);
  file.read(reinterpret_cast<char*>(&this->fullName), FULLNAME_SIZE);
  file.read(reinterpret_cast<char*>(&this->birthDay), DATE_SIZE);
}