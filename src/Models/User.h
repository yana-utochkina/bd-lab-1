#include "../constants.h"

#ifndef USER_H
#define USER_H

#include <iostream>

struct User {
    int id;
    char phone[PHONE_SIZE]; // 0123456789
    char fullName[FULLNAME_SIZE];
    char birthDay[DATE_SIZE]; // DDMMYYYY

    User(int id, char* phone, char* fullName, char* birthDay);
    User(User& user) = delete;
    User(User&& user) = delete;
    User operator=(User& user) = delete;
    User& operator=(User&& user) = delete;

    friend std::ostream& operator<<(std::ostream& os, const User& user);
};



#endif //USER_H
