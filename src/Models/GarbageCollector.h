#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H
#include <vector>
#include <fstream>

struct GarbageCollector {
    std::vector<int> address;
    std::string fileName;

    GarbageCollector(const std::string& fileName);
    GarbageCollector(GarbageCollector& other) = delete;
    GarbageCollector(GarbageCollector&& other) = delete;
    GarbageCollector operator = (const GarbageCollector& other) = delete;
    GarbageCollector& operator = (const GarbageCollector&& other) = delete;
    ~GarbageCollector();

    void add(int address);
    int pop_first();
    int remove(int _address);

};



#endif //GARBAGECOLLECTOR_H
