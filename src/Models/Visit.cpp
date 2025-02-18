#include "Visit.h"
#include "../functions.h"

Visit::Visit(int nextAddress, int id, const char* date, const char* startTime, const char* endTime) {
    this->nextAddress = nextAddress;
    this->id = id;
    for (int i = 0; i < DATE_SIZE; i++) {
        this->date[i] = date[i];
    }
    for (int i = 0; i < TIME_SIZE; i++) {
        this->startTime[i] = startTime[i];
        this->endTime[i] = endTime[i];
    }
}

Visit::Visit(const int id,const char* date, const char* startTime, const char* endTime) {
    this->id = id;
    for (int i = 0; i < DATE_SIZE; i++) {
        this->date[i] = date[i];
    }
    for (int i = 0; i < TIME_SIZE; i++) {
        this->startTime[i] = startTime[i];
        this->endTime[i] = endTime[i];
    }
}

std::ostream& operator<<(std::ostream& os, const Visit& v) {
    os << "id: " << v.id << '\n';
    os << "date: " << dateToString(v.date) << '\n';
    os << "startTime: " << timeToString(v.startTime) << '\n';
    os << "endTime: " << timeToString(v.endTime) << '\n';
    return os;
}