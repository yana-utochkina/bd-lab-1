#include "User.h"
#include "constants.h"
#include "functions.h"

User::User(int id, char phone[], char fullName[], char birthDay[]) {
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