#include "IndexTable.h"

#include <fstream>

#include "../constants.h"
#include "../files.h"

IndexTable::IndexTable(std::string fileName)
{
    this->fileName = fileName;

    if (!isEmptyFile(fileName))
    {
        std::fstream file;
        openFile(file, this->fileName);

        int size;
        file.read(reinterpret_cast<char*>(&size), sizeof(size));

        int t_key, t_address;
        for (int i = 0; i < size; i++)
        {
            file.read(reinterpret_cast<char*>(&t_key), sizeof(int));
            file.read(reinterpret_cast<char*>(&t_address), sizeof(int));
            this->indexMap.insert(std::make_pair(t_key, t_address));
        }
        file.close();
    }
}

IndexTable::~IndexTable()
{
    std::fstream file;
    openFile(file, this->fileName);

    int size = this->indexMap.size();
    file.write(reinterpret_cast<char*>(&size), sizeof(int));

    for (auto& [key, address] : this->indexMap)
    {
        int t_key = key;
        int t_address = address;
        file.write(reinterpret_cast<char*>(&t_key), INT_SIZE);
        file.write(reinterpret_cast<char*>(&t_address), INT_SIZE);
    }

    this->indexMap.clear();
    file.close();
}

void IndexTable::add(int key, int address)
{
    if (this->indexMap.contains(key))
    {
        throw std::runtime_error("This User id already exists");
    }
    if (this->indexMap.size() < MAX_IND_RECORDS)
    {
        this->indexMap.insert(std::make_pair(key, address));
    }
    else
    {
        throw std::runtime_error("Index table is full");
    }
}

int IndexTable::get_address(int key)
{
    if (!this->indexMap.contains(key))
    {
        throw std::invalid_argument("Wrong User id");
    }
    return this->indexMap[key];
}

void IndexTable::remove(int key)
{
    if (!this->indexMap.contains(key))
    {
        throw std::runtime_error("Wrong User id");
    }
    this->indexMap.erase(key);
}
