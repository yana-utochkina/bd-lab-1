#ifndef INDEXTABLE_H
#define INDEXTABLE_H

#include <map>
#include "../files.h"

struct IndexTable {
    std::map<int, int> indexMap;
    std::string fileName;

    IndexTable(std::string fileName);
    IndexTable(IndexTable& indexTable) = delete;
    IndexTable(IndexTable&& indexTable) = delete;
    IndexTable operator=(IndexTable& indexTable) = delete;
    IndexTable& operator=(IndexTable&& indexTable) = delete;

    ~IndexTable();

    void add(int key, int address);
    int get_address(int key);
    void remove(int key);
};

#endif //INDEXTABLE_H
