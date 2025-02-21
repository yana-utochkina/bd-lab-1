#ifndef FILES_H
#define FILES_H
#include <string>
#include <fstream>

constexpr int MAX_IND_RECORDS = 20;

const std::string USERS_FL_PATH = "../../files/Users.fl";
const std::string USERS_IND_PATH = "../../files/Users.ind";
const std::string VISITS_FL_PATH = "../../files/Visits.fl";

const std::string USERS_GC_PATH = "../../files/Users.gc";
const std::string VISITS_GC_PATH = "../../files/Visits.gc";

bool isEmptyFile(std::string filePath);

void openFile(std::fstream &file, const std::string& filePath);

void seekToUsersRow(std::fstream &file, int row, int start = 0);
void seekToVisitsRow(std::fstream &file, int row, int start = 0);

void markAsAdded(std::fstream &file);
void markAsDeleted(std::fstream &file);

#endif //FILES_H
