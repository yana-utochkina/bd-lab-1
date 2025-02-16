#include "../constants.h"

#ifndef VISIT_H
#define VISIT_H

#include <iostream>

struct Visit {
    int nextAddress;
    int id;
    char date[DATE_SIZE]; // DDMMYYYY
    char startTime[TIME_SIZE]; // HHMM
    char endTime[TIME_SIZE]; // HHMM

    Visit(int nextAddress, int id, const char* date, const char* startTime, const char* endTime);
    Visit(int id, const char* date, const char* startTime, const char* endTime);
    Visit(Visit& other) = delete;
    Visit(Visit&& other) = delete;
    Visit operator=(Visit& other) = delete;
    Visit& operator=(Visit&& other) = delete;
    friend std::ostream& operator<<(std::ostream& os, const Visit& v);
};



#endif //VISIT_H
