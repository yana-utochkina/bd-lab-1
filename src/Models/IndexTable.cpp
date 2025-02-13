#include "IndexTable.h"
#include <fstream>


IndexTable::IndexTable(std::string fileName) {
  this->fileName = fileName;
  std::fstream file;
  file.open(fileName, std::ios::in | std::ios::binary);
  // Error if isn't opened
  int t_key, t_address;
  while (file) {
    file.read(reinterpret_cast<char*>(&t_key), sizeof(int));
    file.read(reinterpret_cast<char*>(&t_address), sizeof(int));
    this->indexMap.insert(std::make_pair(t_key, t_address));
  }

  file.close();
}

IndexTable::~IndexTable() {
  std::fstream file;
  file.open(this->fileName, std::ios::out | std::ios::binary);
  // Error if isn't opened
  int size = this->indexMap.size();
  for (int i = 0; i < size; i++) {
    file.write(reinterpret_cast<char*>(&this->indexMap[i]), sizeof(int));
  }

  this->indexMap.clear();
  file.close();
}

void IndexTable::add(int key, int address) {
  // Error if key exist
  if (this->indexMap.size() < MAX_IND_RECORDS) {
    this->indexMap.insert(std::make_pair(key, address));
  }
}

int IndexTable::get_address(int key) {
  // Error if key isn't exist
  return this->indexMap[key];
}

void IndexTable::remove(int key) {
  // Error if key isn't exist
  this->indexMap.erase(key);
}
