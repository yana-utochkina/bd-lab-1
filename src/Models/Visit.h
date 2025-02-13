#include "../constants.h"

#ifndef VISIT_H
#define VISIT_H

#include <iostream>

struct Visit {
    int id;
    char date[DATE_SIZE]; // DDMMYYYY
    char startTime[TIME_SIZE]; // HHMM
    char endTime[TIME_SIZE]; // HHMM

    Visit(int id, char* date, char* startTime, char* endTime);
    Visit(Visit& other) = delete;
    Visit(Visit&& other) = delete;
    Visit operator=(Visit& other) = delete;
    Visit& operator=(Visit&& other) = delete;
    friend std::ostream& operator<<(std::ostream& os, const Visit& v);
};



#endif //VISIT_H
