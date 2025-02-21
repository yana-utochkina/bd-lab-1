#include "files.h"
#include <filesystem>
#include "constants.h"

bool isEmptyFile(std::string filePath)
{
    return std::filesystem::is_empty(filePath);
}

void openFile(std::fstream &file, const std::string& filePath)
{
  	if (file.is_open())
	{
		file.close();
	}
	file.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
  	if (!file.is_open())
    {
    	throw std::runtime_error("Could not open file " + filePath);
  	}
}

void seekToUsersRow(std::fstream &file, int row, int start)
{
	int address = INT_SIZE + USERS_ROW_SIZE * row + start;
  	file.seekg(address, std::ios::beg);
}

void seekToVisitsRow(std::fstream &file, int row, int start)
{
  	int address = INT_SIZE + VISITS_ROW_SIZE * row + start;
  	file.seekg(address, std::ios::beg);
}

void markAsAdded(std::fstream &file)
{
	char mark = '0';
	file.write(&mark, sizeof(char));
}

void markAsDeleted(std::fstream &file)
{
    char mark = '1';
	file.write(&mark, sizeof(char));
}

