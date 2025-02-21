#ifndef USER_H
#define USER_H

#include <iostream>

#include "../constants.h"

struct User {
    int firstVisitAdress;
    int sizeOfVisits;
    int id;
    char phone[PHONE_SIZE]{}; // 0123456789
    char fullName[FULLNAME_SIZE]{};
    char birthDay[DATE_SIZE]{}; // DDMMYYYY

    User() {};
    User(int firstVisitAddress, int sizeOfVisits, int id, const char* phone, const char* fullName, const char* birthDay);
    User(int id,const char* phone, const char* fullName, const char* birthDay);
    User(User& user) = delete;
    User(User&& user) = delete;
    User operator=(User& user) = delete;
    User& operator=(User&& user) = delete;

    friend std::ostream& operator<<(std::ostream& os, const User& user);
    void Save(std::fstream& file);
    void Load(std::fstream& file);
};

#endif //USER_H
