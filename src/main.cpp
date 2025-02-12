#include <iostream>
#include <cstring>
#include "constants.h"
#include "Visit.h"
#include "User.h"

int INT_SIZE = sizeof(int);
int CHAR_SIZE = sizeof(char);

int main() {
    std::string d = "12022025";
    char date[8];

    Visit v1 = Visit(1, strcpy(date, d.c_str()), "1200", "1400");
    std::cout << v1;

    User u1 = User(1, "0123456789", "Utochkina Yana", "12032006");
    std::cout << u1;

    std::cout << INT_SIZE << CHAR_SIZE << std::endl;
}