#include "GarbageCollector.h"

#include <algorithm>
#include <iostream>

#include "../files.h"

GarbageCollector::GarbageCollector(const std::string& fileName)
{
    this->fileName = fileName;

    if (!isEmptyFile(fileName))
    {
        std::fstream file;
        openFile(file, this->fileName);

        int size;
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        int temp;
        for (int i = 0; i < size; i++)
        {
            file.read(reinterpret_cast<char*>(&temp), sizeof(int));
            this->address.push_back(temp);
        }
        file.close();
    }
}

GarbageCollector::~GarbageCollector()
{
    std::fstream file;
    openFile(file, this->fileName);

    int size = this->address.size();
    file.write(reinterpret_cast<char*>(&size), sizeof(int));

    for (int i = 0; i < size; i++)
    {
        file.write(reinterpret_cast<char*>(&this->address.at(i)), sizeof(int));
    }
    file.close();
}

void GarbageCollector::add(int address)
{
    this->address.push_back(address);
}

int comp(int a, int b)
{
    return a > b;
}

int GarbageCollector::pop_first()
{
    std::sort(this->address.begin(), this->address.end(), comp);
    int result = this->address.back();
    this->address.pop_back();
    return result;
}

int GarbageCollector::remove(int _address)
{
    auto it = std::find(this->address.begin(), this->address.end(), _address);
    if (it != this->address.end())
    {
        this->address.erase(it);
    }
    return _address;
}

bool GarbageCollector::isEmpty()
{
    return this->address.empty();
}