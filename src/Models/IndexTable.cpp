#include "IndexTable.h"
#include <fstream>

#include "../constants.h"
#include "../files.h"

IndexTable::IndexTable(std::string fileName) {
  this->fileName = fileName;

  if (!isEmptyFile(fileName)) {
    std::fstream file;
    file.open(fileName, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
      throw std::runtime_error("Could not open file " + fileName);
    }

    int t_key, t_address;
    while (file) {
      file.read(reinterpret_cast<char*>(&t_key), sizeof(int));
      file.read(reinterpret_cast<char*>(&t_address), sizeof(int));
      std::cout << t_key << " " << t_address << std::endl;
      this->indexMap.insert(std::make_pair(t_key, t_address));
    }
    file.close();
  }
}

IndexTable::~IndexTable() {
  std::fstream file;
  file.open(this->fileName, std::ios::out | std::ios::binary);

  if (!file.is_open()) {
    throw std::runtime_error("Could not open file " + this->fileName);
  }

  for (auto& [key, address] : this->indexMap) {
    int t_key = key;
    int t_address = address;
    file.write(reinterpret_cast<char*>(&t_key), INT_SIZE);
    file.write(reinterpret_cast<char*>(&t_address), INT_SIZE);
  }

  this->indexMap.clear();
  file.close();
}

void IndexTable::add(int key, int address) {
  if (this->indexMap.contains(key)) {
    throw std::runtime_error("Key already exists");
  }
  if (this->indexMap.size() < MAX_IND_RECORDS) {
    this->indexMap.insert(std::make_pair(key, address));
  }
  else {
    throw std::runtime_error("Index table is full");
  }
}

int IndexTable::get_address(int key) {
  if (!this->indexMap.contains(key)) {
    throw std::runtime_error("Key not found");
  }
  return this->indexMap[key];
}

void IndexTable::remove(int key) {
  if (!this->indexMap.contains(key)) {
    throw std::runtime_error("Key not found");
  }
  this->indexMap.erase(key);
}
