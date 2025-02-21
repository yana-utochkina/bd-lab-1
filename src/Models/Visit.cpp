#include "Visit.h"
#include "../functions.h"

Visit::Visit(int prevAddress, int nextAddress, int id, const char* date, const char* startTime, const char* endTime) {
    this->prevAddress = prevAddress;
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

void Visit::Save(std::fstream& file)
{
    file.write(reinterpret_cast<char*>(&this->prevAddress), sizeof(this->prevAddress));
    file.write(reinterpret_cast<char*>(&this->nextAddress), sizeof(this->nextAddress));
    file.write(reinterpret_cast<char*>(&this->id), sizeof(this->id));
    file.write(reinterpret_cast<char*>(&this->date), DATE_SIZE);
    file.write(reinterpret_cast<char*>(&this->startTime), TIME_SIZE);
    file.write(reinterpret_cast<char*>(&this->endTime), TIME_SIZE);
}

void Visit::Load(std::fstream& file) {
    file.read(reinterpret_cast<char*>(&this->prevAddress), sizeof(this->prevAddress));
    file.read(reinterpret_cast<char*>(&this->nextAddress), sizeof(this->nextAddress));
    file.read(reinterpret_cast<char*>(&this->id), sizeof(this->id));
    file.read(reinterpret_cast<char*>(&this->date), DATE_SIZE);
    file.read(reinterpret_cast<char*>(&this->startTime), TIME_SIZE);
    file.read(reinterpret_cast<char*>(&this->endTime), TIME_SIZE);
}