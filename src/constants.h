#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int BOOL_SIZE = 1;
constexpr int INT_SIZE = 4;

constexpr int FULLNAME_SIZE = 255;
constexpr int PHONE_SIZE = 10;
constexpr int DATE_SIZE = 8;
constexpr int TIME_SIZE = 4;

constexpr int USERS_ROW_SIZE = BOOL_SIZE + INT_SIZE * 3 + PHONE_SIZE + FULLNAME_SIZE + DATE_SIZE;
constexpr int VISITS_ROW_SIZE = BOOL_SIZE + INT_SIZE * 3 + DATE_SIZE + TIME_SIZE * 2;

#endif //CONSTANTS_H
